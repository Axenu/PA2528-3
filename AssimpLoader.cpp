#include "AssimpLoader.h"



AssimpLoader::AssimpLoader()
{
}


AssimpLoader::~AssimpLoader()
{
	delete scene;
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
		logInfo(importer.GetErrorString());
		return false;
	}

	// read file and do post processing using one of the assimp presets
	// aiProcessPreset_TargetRealtime_Quality
	scene = importer.ReadFile(file, aiProcessPreset_TargetRealtime_Quality);

	// check for errors
	if (!scene)
	{
		logInfo(importer.GetErrorString());
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
	scene = importer.ReadFileFromMemory(buffer, lenght, aiProcessPreset_TargetRealtime_Quality);

	// check for errors
	// check for errors
	if (!scene)
	{
		logInfo(importer.GetErrorString());
		return false;
	}

	// access file content
	logInfo("Imported scene from memory without errors.");

	// done
	return true;
}

template <typename T>
T AssimpLoader::loadMesh(const std::string& file)
{
	return true;
}

template <typename T>
T AssimpLoader::loadModel(const std::string& file)
{
	return true;
}

template <typename T>
T AssimpLoader::loadTexture(const std::string& file)
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