#ifndef __ImporterTester__
#define __ImporterTester__

#include "ImporterManager.h"

// Simple tests to check if the Importer Manager are able to load a specific file.
// Can load from a file "path/file" or memory "memory buffer, length of buffer"

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
		int width = 0, height = 0;

		ImporterManager* importer = new ImporterManager();

		std::cout << "Loading " << imagefile << " using stb_image." << std::endl;
		image = importer->loadTextureFromFile(imagefile, width, height);

		std::cout << "Unloading " << imagefile << " using stb_image." << std::endl;
		importer->freeTexture(image);

		delete importer;

		std::getchar();
	}

	static void imageMemoryTest(void* buffer, int length)
	{
		unsigned char* image;
		int width = 0, height = 0;

		ImporterManager* importer = new ImporterManager();

		std::cout << "Loading image from memory using stb_image." << std::endl;
		image = importer->loadTextureFromMemory(buffer, length, width, height);

		std::cout << "Unloading image from memory using stb_image." << std::endl;
		importer->freeTexture(image);

		delete importer;

		std::getchar();
	}

	static void modelFileTest(std::string modelfile)
	{
		bool result;
		std::cout << "Assimp Loading: " << modelfile << std::endl;
		AssimpLoader* loader = new AssimpLoader();
		result = loader->importFromFile(modelfile);

		if (result)
		{
			std::cout << "Finished Loading: " << modelfile << std::endl;
		}
		else
		{
			std::cout << "Failed Loading: " << modelfile << std::endl;
		}

		delete loader;

		std::getchar();
	}
};

#endif
