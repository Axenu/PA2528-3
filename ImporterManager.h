#ifndef __IMPORTERMANAGER__
#define __IMPORTERMANAGER__

#include "AssimpLoader.h"

class ImporterManager
{
private:
	enum Importer {
		assimp = 1,
		placeholder = 2
	};

public:
	ImporterManager();
	~ImporterManager();

	void importMesh(int importer, std::string file);
	void importModel(int importer, std::string file);
	void importTexture(int importer, std::string file);
	// add filetype as parameter or return pointer

private:
	bool importUsingAssimp(std::string file);
	// importUsing2ndLibrary ...

	AssimpLoader* m_loaderAssimp;

};

#endif