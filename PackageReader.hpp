#ifndef __PACKAGE_READER__
#define __PACKAGE_READER__

#include <string>
#include "Array.hpp"
#include "gui_t.hpp"

class Texture;
class Mesh;

// The PackageReader does not handle asynchronous loading.
// Its job is only to read a resource from a set package
// using a specified GUI.
// Note that the unbuffered I/O functionality belongs to
// the person responsible for developing the PackageReader.
class PackageReader {
    public:
        struct MetaData {
            enum class Type : char {
                TEXTURE,
                MESH,
                INVALID,
            };

            Type type = Type::INVALID;
            gui_t gui = 0;
        };

    public:
        // Return true if package is found and valid. Else false.
        static bool setPackage(const char* path);

        // Return pointer to texture resource with specified GUI. Return nullptr if not found.
        static Texture* loadTexture(gui_t gui);

        // Return pointer to mesh resource with specified GUI. Return nullptr if not found.
        static Mesh* loadMesh(gui_t gui);

        // Return metadata of every resource in the package.
        static Array<MetaData> getMetaData();

};

#endif // __PACKAGE_READER__

