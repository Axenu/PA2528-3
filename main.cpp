#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <chrono>

#include "ImporterManager.h"
#include "ImporterTester.h"


#include "PackageReader.hpp"
#include "ResourceManager.hpp"
#include "ThreadPool.hpp"


void ImporterTests()
{
	// Importer init test
	ImporterTester::importerTest();
	std::getchar();

	// PNG
	ImporterTester::imageFileTest("test_files/test.png");
	std::getchar();
	
	// TGA
	ImporterTester::imageFileTest("test_files/test.tga");
	std::getchar();

	// OBJ
	ImporterTester::modelFileTest("package tool/example/Cow.obj");
	std::getchar();

	// PLY

	// load mesh using assimp
	Mesh* mesh = ImporterTester::meshFileTest("package tool/example/Cow.obj");
	std::getchar();
}

int main()
{
	// simple importer tests
	ImporterTests();

	// package reader
	PackageReader::setPackage("..\\..\\PA2528-3\\package tool\\res");

	ThreadPool::initialize();
	ResourceManager::initialize();

	std::cout << "Loading level..." << std::endl;

	std::cout << "loading 6042386530102251393" << std::endl;
	Promise<SharedPtr<Mesh>> mp1 = ResourceManager::aloadMesh(6042386530102251393);
	Promise<SharedPtr<Mesh>> mp2= ResourceManager::aloadMesh(6042386530102251393);
	Promise<SharedPtr<Mesh>> mp3 = ResourceManager::aloadMesh(6042386530102251393);
	Promise<SharedPtr<Mesh>> mp4 = ResourceManager::aloadMesh(6042386530102251393);
	Promise<SharedPtr<Mesh>> mp5 = ResourceManager::aloadMesh(8310561434802922618);

	int count = 0;
	while (true) {
		if (mp1.isReady()) {
			std::cout << "resource loaded" << std::endl;
			break;
		}
		count += 1;
		//_sleep(1);
	}
	std::cout << "Loading resources took " << count << " waits";


	PackageReader::clearPackage();

	int i;
	std::cin >> i;

    return 0;
}
