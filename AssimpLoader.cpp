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
		std::cout << "Unable to open file: " << file << std::endl;
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

	// done
	return true;
}

bool AssimpLoader::importFromMemory(const void* buffer, size_t lenght)
{
	// buffer = pointer to file data, lenght = lenght of buffer in bytes

	// read file from memory and do post processing using one of the assimp presets
	// aiProcessPreset_TargetRealtime_Quality
	m_scene = m_importer.ReadFileFromMemory(buffer, lenght, aiProcessPreset_TargetRealtime_Quality);

	// check for errors
	if (!m_scene)
	{
		logInfo(m_importer.GetErrorString());
		return false;
	}

	// access file content
	logInfo("Imported scene from memory without errors.");

	// done
	return true;
}

Mesh* AssimpLoader::loadMeshFromFile(const std::string& file)
{
	Mesh* mesh;

	return mesh;
}

Mesh* AssimpLoader::loadMeshFromMemory(const void* buffer, size_t lenght)
{
	Mesh* mesh;



	return mesh;
}

template <typename T>
T AssimpLoader::loadModel(const std::string& file)
{
	return true;
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