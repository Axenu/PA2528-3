#ifndef __PACKAGE_READER__
#define __PACKAGE_READER__

#include <string>

class Texture;
class Mesh;

// The PackageReader does not handle asynchronous loading.
// Its job is only to read a resource from a set package
// using a specified GUI.
// Note that the unbuffered I/O functionality belongs to
// the person responsible for developing the PackageReader.
class PackageReader {
    public:
        // Return true if package is found and valid. Else false.
        static bool setPackage(const char* path);

        // Return pointer to texture resource with specified GUI. Return nullptr if not found.
        static Texture* loadTexture(gui_t gui);

        // Return pointer to mesh resource with specified GUI. Return nullptr if not found.
        static Mesh* loadMesh(gui_t gui);

};

#endif // __PACKAGE_READER__

