#include <Windows.h>

#include "PackageReader.hpp"

#include "Texture.hpp"
#include "Mesh.hpp"


std::wstring PackageReader::packagePath;
Array<PackageReader::MetaData> PackageReader::metaData;
size_t PackageReader::numResourcesInPackage = 0;
void* PackageReader::rawFile = nullptr;
std::ifstream PackageReader::file;
size_t PackageReader::baseOffset = 0;
long PackageReader::sectorSize = 0;
HANDLE PackageReader::fileHandle;


// Return true if package is found and valid. Else false.
bool PackageReader::setPackage(const char* path) {
	// Clear current package, if any.
	clearPackage();

	// Convert path to wchar
	const size_t cSize = strlen(path) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t outSize;
	mbstowcs_s(&outSize, wc, cSize, path, cSize-1);
	packagePath = wc;
	delete wc;

	// Open file
	openFile();

	file >> numResourcesInPackage;
	file.get(); // Removes newline
	
	metaData.data = new PackageReader::MetaData[numResourcesInPackage];
	metaData.size = numResourcesInPackage;

	const int maxStringLength = 300;
	char* temp = new char[maxStringLength];
	for (size_t i = 0; i < numResourcesInPackage; ++i) {
		// Read filename
		file.getline(temp, maxStringLength, ':');

		// Read GUI
		file.getline(temp, maxStringLength, ':');

		// Convert to bit representation and store in metadata array
		metaData.data[i].gui = strtoll(temp, NULL, 10);

		// Read file type
		file.getline(temp, maxStringLength, ':');
		// Currently unused

		// Read resource type
		file.getline(temp, maxStringLength, ':');

		// Set appropriate resource type.
		if (strcmp(temp, "M") == 0) {
			metaData.data[i].type = PackageReader::MetaData::Type::MESH;
		}
		else if (strcmp(temp, "T") == 0) {
			metaData.data[i].type = PackageReader::MetaData::Type::TEXTURE;
		}
		else {
			metaData.data[i].type = PackageReader::MetaData::Type::INVALID;
		}
		
		// Read size
		file.getline(temp, maxStringLength, ':');
		metaData.data[i].size = strtol(temp, NULL, 10);

		// Read offset
		file.getline(temp, maxStringLength);
		metaData.data[i].offset = strtol(temp, NULL, 10);
	}
	// Set base offset to the next position (the start of the first file)
	baseOffset = static_cast<size_t>(file.tellg());

	closeFile();
	delete[] temp;

	if (!sectorSize)
		findSectorSize();

	return true;
}

// Clears the current package. Used when exiting application or switching package.
void PackageReader::clearPackage() {
	delete rawFile;
	rawFile = nullptr;

	delete[] metaData.data;
	metaData.data = nullptr;
	metaData.size = 0;
}

// Return pointer to texture resource with specified GUI. Return nullptr if not found.
Texture* PackageReader::loadTexture(gui_t gui) {
	size_t index = 0;
	OffsetPointer<void> mem = loadFile(gui, index);
    
	if (!mem.getPointer())
		return nullptr;

	// Read memory data into new texture (stb_image)
	ImporterManager* importer = new ImporterManager();
	Texture* texture = new Texture();	
	
	texture = importer->loadTextureFromMemory(mem.getPointer(), metaData.data[index].size);

	delete importer;

	return texture;	// return texture
}

// Return pointer to mesh resource with specified GUI. Return nullptr if not found.
Mesh* PackageReader::loadMesh(gui_t gui) {
	size_t index = 0;
	OffsetPointer<void> mem = loadFile(gui, index);

	if (!mem.getPointer())
		return nullptr;

	// Read memory data into new mesh (assimp)
	Mesh* mesh = new Mesh();
	ImporterManager* importer = new ImporterManager();

	mesh = importer->loadMeshFromMemory(mem.getPointer(), metaData.data[index].size);

	delete importer;

	return mesh;	// return mesh
}

// Return array of all GUIs in the package. Caller is responsible for the memory of returned array.
Array<PackageReader::MetaData> PackageReader::getMetaData() {
	Array<MetaData> newArr;
	newArr.size = metaData.size;
	newArr.data = new PackageReader::MetaData[metaData.size];

	memcpy(newArr.data, metaData.data, sizeof(PackageReader::MetaData) * metaData.size);

    return newArr;
}

bool PackageReader::openFile()
{
	// Remove buffer
	file.rdbuf()->pubsetbuf(0, 0);

	file.open(packagePath);

	// Return the file's open status
	return file.is_open();
}

void PackageReader::closeFile()
{
	if (file.is_open())
		file.close();
}

// Searches for and loads a file from the package into memory. Caller is responsible for the returned memory.
// metaDataPos will contain index of the file in the metaData array.
OffsetPointer<void> PackageReader::loadFile(gui_t gui, size_t& metaDataPos)
{
	for (size_t i = 0; i < numResourcesInPackage; ++i) {
		if (metaData.data[i].gui == gui) {
			if (metaData.data[i].type == PackageReader::MetaData::Type::INVALID) {
				return OffsetPointer<void>();
			}

			// Return index in the metaData array
			metaDataPos = i;

			// Add sectorSize * 3, one for alignment in memory, one for alignment in the file, one for additional space read at the end of a sector
			void* rawMem = malloc(sectorSize * 3 + metaData.data[i].size);

			uintptr_t misalignedBytes = reinterpret_cast<uintptr_t>(rawMem) & (sectorSize - 1);
			unsigned int adjustment = sectorSize - misalignedBytes;

			long* alignedMem = reinterpret_cast<long*>(reinterpret_cast<uintptr_t>(rawMem) + adjustment);


			fileHandle = CreateFile(packagePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
			HRESULT err = HRESULT_FROM_WIN32(GetLastError());

			LONG signedOffset = static_cast<long>(metaData.data[i].offset + baseOffset);
			// Find the closest previous sector in the file
			long offsetFromFileSector = signedOffset % sectorSize;

			SetFilePointer(fileHandle, signedOffset - offsetFromFileSector, NULL, FILE_BEGIN);
			err = HRESULT_FROM_WIN32(GetLastError());

			DWORD size = static_cast<unsigned long>(metaData.data[i].size);
			// Add enough space to read an even number of sectors
			size += sectorSize - (size % sectorSize);
			LPDWORD bytesRead = new DWORD;
			ReadFile(fileHandle, alignedMem, size, bytesRead, NULL);
			err = HRESULT_FROM_WIN32(GetLastError());
			CloseHandle(fileHandle);

			if (*bytesRead != size) {
				std::cerr << "Error loading file!";
				return OffsetPointer<void>();
			}

			delete bytesRead;

			return OffsetPointer<void>(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(alignedMem) + offsetFromFileSector), adjustment + offsetFromFileSector);
		}
	}

	return OffsetPointer<void>();
}

void PackageReader::findSectorSize()
{
	// Get disk sector size
	STORAGE_ACCESS_ALIGNMENT_DESCRIPTOR alignment = { 0 };
	WCHAR disk[] = L"\\\\.\\C:";


	DWORD Bytes = 0;
	STORAGE_PROPERTY_QUERY Query;

	ZeroMemory(&Query, sizeof(Query));

	HANDLE device = CreateFileW(disk, STANDARD_RIGHTS_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	Query.QueryType = PropertyStandardQuery;
	Query.PropertyId = StorageAccessAlignmentProperty;

	DeviceIoControl(device, IOCTL_STORAGE_QUERY_PROPERTY, &Query, sizeof(STORAGE_PROPERTY_QUERY), &alignment,
		sizeof(STORAGE_ACCESS_ALIGNMENT_DESCRIPTOR), &Bytes, NULL);

	CloseHandle(device);

	sectorSize = alignment.BytesPerPhysicalSector;
}
