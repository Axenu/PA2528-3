#include "ImporterManager.h"



ImporterManager::ImporterManager()
{
	
}


ImporterManager::~ImporterManager()
{
	if(m_loaderAssimp)
		delete m_loaderAssimp;
}

void ImporterManager::initLoader(int importer)
{
	switch (importer)
	{
	case loader_assimp:
		m_loaderAssimp = new AssimpLoader();
		break;

	case loader_stb_image:
		break;

	default:
		break;
	}
}

void ImporterManager::destroyLoader(int importer)
{
	if (m_loaderAssimp)
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

//bool ImporterManager::importUsingAssimp(std::string file)
//{
//	bool result;
//
//	result = m_loaderAssimp->importFile(file);
//
//	return result;
//}
