#ifndef __ImporterTester__
#define __ImporterTester__

#include "ImporterManager.h"

// Simple tests to check if the Importer Manager are able to load a specific file.
// Can load from a file "path/file" or memory "memory buffer, length of buffer"

class ImporterTester
{
public:
	static void importerTest()
	{
		ImporterManager* importer = new ImporterManager();

		std::cout << "Initializing Assimp using the import manager." << std::endl;
		importer->initLoader(ImporterManager::Importers::loader_assimp);
		
		std::cout << "Deinitializing Assimp using the import manager." << std::endl;
		importer->destroyLoader(ImporterManager::Importers::loader_assimp);

		delete importer;
	}

	static void imageFileTest(std::string imagefile)
	{
		Texture* texture = new Texture();

		ImporterManager* importer = new ImporterManager();

		std::cout << "Loading " << imagefile << " using stb_image." << std::endl;
		texture = importer->loadTextureFromFile(imagefile);

		std::cout << "Unloading " << imagefile << " using stb_image." << std::endl;
		importer->freeTexture(texture);

		delete importer;
	}

	static void imageMemoryTest(void* buffer, int length)
	{
		Texture* texture = new Texture();

		ImporterManager* importer = new ImporterManager();

		std::cout << "Loading image from memory using stb_image." << std::endl;
		texture = importer->loadTextureFromMemory(buffer, length);

		std::cout << "Unloading image from memory using stb_image." << std::endl;
		importer->freeTexture(texture);

		delete importer;
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
	}

	static Mesh* meshFileTest(std::string modelfile)
	{
		std::cout << "Assimp Loading mesh from: " << modelfile << std::endl;
		AssimpLoader* loader = new AssimpLoader();
		Mesh* mesh = loader->loadMeshFromFile(modelfile);

		if (mesh)
		{
			std::cout << "Successfully Loaded mesh: " << modelfile << std::endl;
		}
		else
		{
			std::cout << "Failed to load mesh: " << modelfile << std::endl;
		}

		delete loader;

		return mesh;
	}

	static Mesh* meshMemoryTest(const void* buffer, size_t length)
	{
		std::cout << "Assimp Loading mesh from memory." << std::endl;
		AssimpLoader* loader = new AssimpLoader();
		Mesh* mesh = loader->loadMeshFromMemory(buffer, length);

		if (mesh)
		{
			std::cout << "Successfully Loaded mesh from memory!" << std::endl;
		}
		else
		{
			std::cout << "Failed to load mesh from memory!" << std::endl;
		}

		delete loader;

		return mesh;
	}
};

#endif
