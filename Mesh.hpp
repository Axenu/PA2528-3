#ifndef __MESH__
#define __MESH__

#include "assimp\mesh.h"

class Mesh { // or struct - doesn't matter
public:
	aiFace* faces;
	unsigned int numFaces;

	aiVector3D* vertices;
	unsigned int numVertices;

	aiVector3D** textureCoords;
	unsigned int numTextureCoords;
	bool hasTextureCoords;

	unsigned int size, memAllocated;
};
#endif // __MESH__