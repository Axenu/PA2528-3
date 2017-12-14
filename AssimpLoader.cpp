#include "AssimpLoader.h"



AssimpLoader::AssimpLoader()
{
}


AssimpLoader::~AssimpLoader()
{

}

bool AssimpLoader::importFromFile(const std::string& file)
{
	// make sure the file exists
	std::ifstream fin(file.c_str());
	if (!fin.fail())
	{
		fin.close();
	}
	else
	{
		std::cerr << "Unable to open file: " << file << std::endl;
		logInfo(m_importer.GetErrorString());
		return false;
	}

	// read file and do post processing using one of the assimp presets
	// aiProcessPreset_TargetRealtime_Quality
	m_scene = m_importer.ReadFile(file, aiProcessPreset_TargetRealtime_Quality);

	// check for errors
	if (!m_scene)
	{
		logInfo(m_importer.GetErrorString());
		return false;
	}

	// access file content
	logInfo("Imported scene " + file + " without errors.");

	// code used for debugging purposes.
	// comment out or delete for better performance
	std::cerr << "Assimp imported " << file << std::endl;
	std::cerr << "Animations_| " << m_scene->mNumAnimations << std::endl;
	std::cerr << "Cameras____| " << m_scene->mNumCameras << std::endl;
	std::cerr << "Lights_____| " << m_scene->mNumLights << std::endl;
	std::cerr << "Materials__| " << m_scene->mNumMaterials << std::endl;
	std::cerr << "Meshes_____| " << m_scene->mNumMeshes << std::endl;
	std::cerr << "Textures___| " << m_scene->mNumTextures << std::endl;

	// done
	return true;
}

bool AssimpLoader::importFromMemory(const void* buffer, size_t length)
{
	// buffer = pointer to file data, length = length of buffer in bytes

	// read file from memory and do post processing using one of the assimp presets
	// aiProcessPreset_TargetRealtime_Quality
	m_scene = m_importer.ReadFileFromMemory(buffer, length, aiProcessPreset_TargetRealtime_Quality);

	// check for errors
	if (!m_scene)
	{
		logInfo(m_importer.GetErrorString());
		return false;
	}

	// access file content
	logInfo("Imported scene from memory without errors.");

	// code used for debugging purposes.
	// comment out or delete for better performance
	std::cerr << "Assimp imported from memory: " << buffer << std::endl;
	std::cerr << "Animations_| " << m_scene->mNumAnimations << std::endl;
	std::cerr << "Cameras____| " << m_scene->mNumCameras << std::endl;
	std::cerr << "Lights_____| " << m_scene->mNumLights << std::endl;
	std::cerr << "Materials__| " << m_scene->mNumMaterials << std::endl;
	std::cerr << "Meshes_____| " << m_scene->mNumMeshes << std::endl;
	std::cerr << "Textures___| " << m_scene->mNumTextures << std::endl;

	// done
	return true;
}

Mesh* AssimpLoader::loadMeshFromFile(const std::string& objFile)
{
	Mesh* mesh = new Mesh();

	m_scene = m_importer.ReadFile(objFile, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	// check for errors
	if (!m_scene)
	{
		logInfo(m_importer.GetErrorString());
		return nullptr;
	}

	// access file content
	logInfo("Imported scene " + objFile + " without errors.");

	// code used for debugging purposes.
	// comment out or delete for better performance
	std::cerr << "Assimp imported obj from : " << objFile << std::endl;
	std::cerr << "Meshes: " << m_scene->mNumMeshes << std::endl;
	for (int i = 0; i < m_scene->mNumMeshes; ++i)
	{
		std::cerr << "Mesh" << i << std::endl;
		std::cerr << "Vertices_| " << m_scene->mMeshes[i]->mNumVertices << std::endl;
		std::cerr << "Faces____| " << m_scene->mMeshes[i]->mNumFaces << std::endl;
	}

	// code for extracting the mesh from scene into the mesh class here
	mesh->numMeshes = m_scene->mNumMeshes;
	
	for (int i = 0; i < m_scene->mNumMeshes; ++i)
	{
		mesh->aiMesh[i] = m_scene->mMeshes[i];
	}

	return mesh;
}

Mesh* AssimpLoader::loadMeshFromMemory(const void* buffer, size_t length)
{
	Mesh* mesh = new Mesh();

	/*pHint	An additional hint to the library.
	If this is a non empty string, the library looks for a loader to support the file extension specified by pHint and passes the file to the first matching loader.
	If this loader is unable to completely the request, the library continues and tries to determine the file format on its own,
	a task that may or may not be successful.Check the return value, and you'll know ...*/
	m_scene = m_importer.ReadFileFromMemory(buffer, length, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	// check for errors
	if (!m_scene)
	{
		logInfo(m_importer.GetErrorString());
		return nullptr;
	}

	// access file content
	logInfo("Imported scene from memory without errors.");

	// code used for debugging purposes.
	// comment out or delete for better performance
	std::cerr << "Assimp imported obj from memory: " << buffer << std::endl;
	std::cerr << "Meshes: " << m_scene->mNumMeshes << std::endl;
	for (int i = 0; i < m_scene->mNumMeshes; ++i)
	{
		std::cerr << "Mesh" << i << std::endl;
		std::cerr << "Vertices_| " << m_scene->mMeshes[i]->mNumVertices << std::endl;
		std::cerr << "Faces____| " << m_scene->mMeshes[i]->mNumFaces << std::endl;
	}

	// code for extracting the mesh from scene into the mesh class here
	mesh->numMeshes = m_scene->mNumMeshes;

	for (int i = 0; i < m_scene->mNumMeshes; ++i)
	{
		mesh->aiMesh[i] = m_scene->mMeshes[i];
	}

	return mesh;
}

void AssimpLoader::createLogger()
{
	// use assimp:Logger::NORMAL if you do not want to analyze the import process
	Assimp::Logger::LogSeverity severity = Assimp::Logger::VERBOSE;

	// create logger for console output
	Assimp::DefaultLogger::create("", severity,aiDefaultLogStream_STDOUT);

	// create logger for text file output
	Assimp::DefaultLogger::create("assimp_log.txt", severity, aiDefaultLogStream_FILE);

	// logger is ready
	Assimp::DefaultLogger::get()->info("this is my info-call");
}

void AssimpLoader::destroyLogger()
{
	Assimp::DefaultLogger::kill();
}

void AssimpLoader::renderScene(const aiScene* scene)
{
	logInfo("rendering objects");
	
	// render code
}