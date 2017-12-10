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
	std::cout << std::endl;*/

	// PLY
	ImporterTester::modelFileTest("test_files/models/cube.ply");
	std::cout << std::endl;
	ImporterTester::modelFileTest("test_files/models/Wuson.ply");
	std::cout << std::endl;
	//ImporterTester::modelFileTest("test_files/models/pond.0.ply");
	//std::cout << std::endl;

	// load mesh using assimp
	// OBJ
	Mesh* meshObj = ImporterTester::meshFileTest("package tool/example/Cow.obj");
	std::cout << std::endl;
	delete meshObj;

	// PLY
	Mesh* meshPly = ImporterTester::meshFileTest("test_files/models/Wuson.ply");
	delete meshPly;

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

    mp2.wait();
    mp3.wait();
    mp4.wait();
    mp5.wait();
	PackageReader::clearPackage();

	int i;
	std::cin >> i;

    return 0;
}
