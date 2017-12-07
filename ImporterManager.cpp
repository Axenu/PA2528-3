#include "ImporterManager.h"



ImporterManager::ImporterManager()
{
	m_loaderAssimp = NULL;
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

bool ImporterManager::importFromFile(int importer, std::string file)
{
	bool result;

	switch (importer)
	{
	case loader_assimp:
		result = m_loaderAssimp->importFromFile(file);
		break;

	case loader_stb_image:
		break;

	default:
		break;
	}

	return result;
}

bool ImporterManager::importFromMemory(int importer, const void* buffer, size_t lenght)
{
	bool result;

	switch (importer)
	{
	case loader_assimp:
		result = m_loaderAssimp->importFromMemory(buffer, lenght);
		break;

	case loader_stb_image:
		break;

	default:
		break;
	}

	return result;
}

template <typename T>
T ImporterManager::importMesh(int importer, std::string file)
{

}

template <typename T>
T ImporterManager::importModel(int importer, std::string file)
{
	
}

unsigned char* ImporterManager::importTexture(std::string file, int* width, int* height)
{
	return ImageLoader::loadFromFile(file.c_str(), width, height);
}

void ImporterManager::freeTexture(unsigned char* image)
{
	ImageLoader::freeImage(image);
}

//bool ImporterManager::importUsingAssimp(std::string file)
//{
//	bool result;
//
//	result = m_loaderAssimp->importFile(file);
//
//	return result;
//}
