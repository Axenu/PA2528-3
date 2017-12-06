#include "PackageReader.hpp"

#include "Texture.hpp"
#include "Mesh.hpp"


std::string PackageReader::packagePath;
Array<PackageReader::MetaData> PackageReader::metaData;
size_t PackageReader::numResourcesInPackage = 0;
void* PackageReader::rawFile = nullptr;
std::ifstream PackageReader::file;
size_t PackageReader::baseOffset = 0;


// Return true if package is found and valid. Else false.
bool PackageReader::setPackage(const char* path) {
	// Clear current package, if any.
	clearPackage();

	packagePath = path;

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

		// Find extension
		const char* dot = strrchr(temp, '.');
		
		// If there is no extension, the package file is invalid.
		if (!dot) {
			closeFile();
			delete[] temp;
			return false;
		}

		// Set appropriate resource type.
		if (strcmp(dot, ".obj") == 0) {
			metaData.data[i].type = PackageReader::MetaData::Type::MESH;
		}
		else if (strcmp(dot, ".png") == 0) {
			metaData.data[i].type = PackageReader::MetaData::Type::TEXTURE;
		}
		// TODO: add more file types?

		// Read gui
		file.getline(temp, maxStringLength, ':');

		// Convert to bit representation and store in metadata array
		// TODO: fix me pls
		metaData.data[i].gui = strtoll(temp, NULL, 16);

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
	void* mem = loadFile(gui);
    
	if (!mem)
		return nullptr;

	// Read memory into new texture

	free(mem);

	return nullptr;	// return texture
}

// Return pointer to mesh resource with specified GUI. Return nullptr if not found.
Mesh* PackageReader::loadMesh(gui_t gui) {
	void* mem = loadFile(gui);

	if (!mem)
		return nullptr;

	// Read memory into new mesh

	free(mem);

	return nullptr;	// return mesh
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
void* PackageReader::loadFile(gui_t gui)
{
	for (size_t i = 0; i < numResourcesInPackage; ++i) {
		if (metaData.data[i].gui == gui) {
			openFile();

			file.seekg(metaData.data[i].offset + baseOffset);

			// Allocate memory for the file
			char* mem = static_cast<char*>(malloc(metaData.data[i].size));

			// Read the file into memory
			file.read(mem, metaData.data[i].size);

			closeFile();

			return mem;
		}
	}

	return nullptr;
}
