#include "ImporterManager.h"



ImporterManager::ImporterManager()
{
	m_loaderAssimp = new AssimpLoader();
}


ImporterManager::~ImporterManager()
{
	delete m_loaderAssimp;
}

void ImporterManager::importMesh(int importer, std::string file)
{

}

void ImporterManager::importModel(int importer, std::string file)
{

}

void ImporterManager::importTexture(int importer, std::string file)
{

}

bool ImporterManager::importUsingAssimp(std::string file)
{
	bool result;

	result = m_loaderAssimp->importFile(file);

	return result;
}
