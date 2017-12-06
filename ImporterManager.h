#ifndef __IMPORTERMANAGER__
#define __IMPORTERMANAGER__

#include "AssimpLoader.h"
#include "ImageLoader.h"

class ImporterManager
{
private:
	enum Importers {
		loader_assimp = 1,
		loader_stb_image = 2
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
	template <typename T>
	T importTexture(int importer, std::string file);
	// add filetype as parameter or return pointer

private:
	bool importUsingAssimp(std::string file);
	// importUsing2ndLibrary ...

	AssimpLoader* m_loaderAssimp;
};

#endif