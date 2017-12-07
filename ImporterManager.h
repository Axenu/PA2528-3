#ifndef IMPORTERMANAGER_H
#define IMPORTERMANAGER_H

#include "AssimpLoader.h"
#include "ImageLoader.h"

class ImporterManager
{
public:
	static enum Importers {
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

	template <typename T>
	T importMesh(int importer, std::string file);
	template <typename T>
	T  importModel(int importer, std::string file);
	
	unsigned char* importTexture(std::string file, int* width, int* height);
	// add filetype as parameter or return pointer
	
	void freeTexture(unsigned char* image);

private:
	//bool importUsingAssimp(std::string file);
	// importUsing2ndLibrary ...

	AssimpLoader* m_loaderAssimp;
};

#endif