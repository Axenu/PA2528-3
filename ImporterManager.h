#ifndef __IMPORTERMANAGER__
#define __IMPORTERMANAGER__

#include "AssimpLoader.h"
#include "ImageLoader.h"

class ImporterManager
{
public:
	enum Importers { // not neeeded?
		loader_assimp = 0,
		loader_stb_image = 1
	};

public:
	ImporterManager();
	~ImporterManager();

	void initLoader(int importer);
	void destroyLoader(int importer);

	bool importFromFile(int importer, std::string file);
	bool importFromMemory(int importer, const void* buffer, size_t lenght);

	// assimp
	template <typename T>
	T importMesh(int importer, std::string file);
	template <typename T>
	T  importModel(int importer, std::string file);
	
	// stb_image
	unsigned char* loadTextureFromFile(std::string file, int width, int height);
	unsigned char* loadTextureFromMemory(void* buffer, int length, int width, int height);
	
	void freeTexture(unsigned char* image);

private:
	//bool importUsingAssimp(std::string file);
	// importUsing2ndLibrary ...

	AssimpLoader* m_loaderAssimp;
};

#endif