#ifndef __MESH__
#define __MESH__

#include "assimp\mesh.h"

class Mesh { // or struct - doesn't matter
public:
	aiMesh* aiMesh[2];
	int numMeshes;
};
#endif // __MESH__


