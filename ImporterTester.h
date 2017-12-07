#ifndef __ImporterTester__
#define __ImporterTester__

#include "ImporterManager.h"

class ImporterTester
{
public:
	static void assimpTest()
	{
		ImporterManager* importer = new ImporterManager();

		std::cout << "Initializing Assimp using the import manager." << std::endl;
		importer->initLoader(ImporterManager::Importers::loader_assimp);

		std::cout << "Deinitializing Assimp using the import manager." << std::endl;
		importer->destroyLoader(ImporterManager::Importers::loader_assimp);

		delete importer;

		std::getchar();
	}

	static void imageFileTest(std::string imagefile)
	{
		unsigned char* image;
		int width, height;

		ImporterManager* importer = new ImporterManager();

		std::cout << "Loading " << imagefile << " using stb_image." << std::endl;
		image = importer->importTexture(imagefile, &width, &height);

		std::cout << "Unloading " << imagefile << " using stb_image." << std::endl;
		importer->freeTexture(image);

		delete importer;

		std::getchar();
	}

	static void imageMemoryTest()
	{

	}
};

#endif
