#ifndef __ASSIMPLOADER__
#define __ASSIMPLOADER__

#include "assimp\DefaultLogger.hpp"
#include "assimp\Importer.hpp"	// C++ importer interface
#include "assimp\scene.h"		// output data struct
#include "assimp\postprocess.h"	// post processing flags

class AssimpLoader
{

public:
	AssimpLoader();
	~AssimpLoader();

	bool importFile(const std::string& file); // const std::string ?
	bool loadMesh(const std::string& file);
	bool loadModel(const std::string& file);
	bool loadTexture(const std::string& file);

private:
	void errorLogging(const std::string& error); // const std::string ?
	void sceneProcessing(const aiScene* scene); // const aiScene ?

};

#endif