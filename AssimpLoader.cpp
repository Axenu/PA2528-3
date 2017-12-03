#include "AssimpLoader.h"



AssimpLoader::AssimpLoader()
{
}


AssimpLoader::~AssimpLoader()
{
}

bool AssimpLoader::importFile(const std::string& file)
{
	Assimp::Importer importer;

	// read file and do post processing
	// more requests = slower
	const aiScene* scene = importer.ReadFile(file,
		aiProcess_CalcTangentSpace		| // does nothing if the mesh have no normals
		aiProcess_Triangulate			| // triangulate all faces of all meshes
		aiProcess_JoinIdenticalVertices | // identifies and joins identical vertex data sets within all imported meshes
		aiProcess_SortByPType);			  // split meshes with more than one primitive type into homogeneous sub-meshes

	// check for errors
	if (!scene)
	{
		errorLogging(importer.GetErrorString());
		return false;
	}

	// access the file's contents
	sceneProcessing( scene);

	// done
	return true;
}

bool AssimpLoader::loadMesh(const std::string& file)
{
	return true;
}

bool AssimpLoader::loadModel(const std::string& file)
{
	return true;
}

bool AssimpLoader::loadTexture(const std::string& file)
{
	return true;
}

void AssimpLoader::errorLogging(const std::string& error)
{
	// create logger
	Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);

	// do error logging
	Assimp::DefaultLogger::get()->info(error);

	// done
	Assimp::DefaultLogger::kill();
}

void AssimpLoader::sceneProcessing(const aiScene* scene)
{
	
}