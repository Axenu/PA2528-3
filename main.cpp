#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <chrono>
#include <Windows.h>

#include "ImporterTester.h"

#include "PackageReader.hpp"
#include "ResourceManager.hpp"
#include "ThreadPool.hpp"

void testUnbuffered(bool unbuffered) {
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

	// Start test
	const long iterations = 20000;
	std::cout << "Testing " << (unbuffered ? "un" : "") << "buffered input\n";

	// Write
	HANDLE file = CreateFile(L"buftest", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_NO_BUFFERING, NULL);

	void* rawMem = malloc(alignment.BytesPerPhysicalSector * 2);

	uintptr_t misalignedBytes = reinterpret_cast<uintptr_t>(rawMem) & (alignment.BytesPerPhysicalSector - 1);
	long* alignedMem = reinterpret_cast<long*>(reinterpret_cast<uintptr_t>(rawMem) + (alignment.BytesPerPhysicalSector - misalignedBytes));

	LPDWORD bytesWritten = new DWORD;
	for (long i = 0; i < iterations; ++i) {
		*alignedMem = i;
		WriteFile(file, alignedMem, alignment.BytesPerPhysicalSector, bytesWritten, NULL);
		SetFilePointer(file, alignment.BytesPerPhysicalSector, NULL, FILE_CURRENT);
	}
	CloseHandle(file);
	delete bytesWritten;

	// Read
	if (unbuffered)
		file = CreateFile(L"buftest", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
	else
		file = CreateFile(L"buftest", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	SetFilePointer(file, 0, NULL, FILE_BEGIN);

	// Start timer
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	LPDWORD bytesRead = new DWORD;
	for (long i = 0; i < iterations; ++i) {
		ReadFile(file, alignedMem, alignment.BytesPerPhysicalSector, bytesRead, NULL);
		HRESULT err = HRESULT_FROM_WIN32(GetLastError());
		SetFilePointer(file, alignment.BytesPerPhysicalSector, NULL, FILE_CURRENT);
	}
	CloseHandle(file);
	delete bytesRead;

	// End timer
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	std::cout << duration << " microseconds\n";

	free(rawMem);
}

void testUnbuffered() {
	testUnbuffered(false);
	testUnbuffered(true);
	std::cout << "Press any key to continue...";
	getchar();
}

void ImporterTests()
{
	/*// Importer init test
	ImporterTester::importerTest();
	std::cout << std::endl;

	// PNG
	ImporterTester::imageFileTest("test_files/textures/test.png");
	std::cout << std::endl;

	// TGA
	ImporterTester::imageFileTest("test_files/textures/test.tga");
	std::cout << std::endl;

	// OBJ
	ImporterTester::modelFileTest("package tool/example/Bookcase_Empty.obj");
	std::cout << std::endl;
	ImporterTester::modelFileTest("package tool/example/Cow.obj");
	std::cout << std::endl;
	/*ImporterTester::modelFileTest("package tool/example/Predator_OBJ.OBJ");
	std::cout << std::endl;

	// PLY
	ImporterTester::modelFileTest("test_files/models/cube.ply");
	std::cout << std::endl;
	ImporterTester::modelFileTest("test_files/models/Wuson.ply");
	std::cout << std::endl;
	//ImporterTester::modelFileTest("test_files/models/pond.0.ply");
	//std::cout << std::endl;*/

	// load mesh using assimp
	// OBJ
	Mesh* meshObj = ImporterTester::meshFileTest("package tool/example/Bookcase_Empty.obj");
	std::cout << std::endl;
	meshObj = ImporterTester::meshFileTest("package tool/example/Cow.obj");
	std::cout << std::endl;
	meshObj = ImporterTester::meshFileTest("package tool/example/Predator_OBJ.OBJ");
	std::cout << std::endl;
	delete meshObj;

	//// PLY
	//Mesh* meshPly = ImporterTester::meshFileTest("test_files/models/Wuson.ply");
	//delete meshPly;

	std::getchar();
}

int main()
{
	// simple importer tests
	//ImporterTests();

	// package reader
	PackageReader::setPackage("package tool/res");

	ThreadPool::initialize();
	ResourceManager::initialize();

	std::cout << "Loading level..." << std::endl;

	std::cout << "loading 6042386530102251393 " << std::endl;
	//Promise<SharedPtr<Mesh>> mp1 = ResourceManager::aloadMesh(6042386530102251393);
	Promise<SharedPtr<Texture>> mp2= ResourceManager::aloadTexture(9181609965336431992);
	Promise<SharedPtr<Mesh>> mp3 = ResourceManager::aloadMesh(6042386530102251393);
	Promise<SharedPtr<Mesh>> mp5 = ResourceManager::aloadMesh(6722305721597800034);
	//Promise<SharedPtr<Texture>> mp5 = ResourceManager::aloadTexture(9181609965336431992);

	int count = 0;
	while (true) {
		if (mp5.isReady()) {
			std::cout << "resource loaded" << std::endl;
			break;
		}
		count += 1;
	}
	std::cout << "Loading resources took " << count << " loops, which proves that it's asynchronous" << std::endl;

	Promise<SharedPtr<Mesh>> mp6 = ResourceManager::aloadMesh(6722305721597800034);
	count = 0;
	while (true) {
		if (mp6.isReady()) {
			std::cout << "resource loaded" << std::endl;
			break;
		}
		count += 1;
	}
	std::cout << "Loading resources took " << count << " loops the second time, much faster!" << std::endl;

	mp5.get() = (Mesh*)nullptr;
	mp6.get() = (Mesh*)nullptr;

	ResourceManager::garbageCollectMeshes();

	Promise<SharedPtr<Mesh>> mp7 = ResourceManager::aloadMesh(6042386530102251393);
	count = 0;
	while (true) {
		if (mp7.isReady()) {
			std::cout << "resource loaded" << std::endl;
			break;
		}
		count += 1;
	}
	std::cout << "Loading resources took " << count << " loops. This time loaded from disk again, since previous instances where garbage collected" << std::endl;

	/*for (int i = 0; i < 1000; i++) {
		ResourceManager::aloadMesh(6042386530102251393);
		ResourceManager::aloadMesh(9181609965336431992);
	}*/

	std::cout << "Loading a lot of rescources took " << count << " loops." << std::endl;


	PackageReader::clearPackage();

	int i;
	std::cin >> i;

	// Test buffered versus unbuffered IO
	//testUnbuffered();

    return 0;
}
