#ifndef __PACKAGE_READER__
#define __PACKAGE_READER__

#include <string>
#include <fstream>
#include "Array.hpp"
#include "gui_t.hpp"

#include "ImporterManager.h"

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
			size_t offset;	// Number of bytes from the first file in the package to the start of this file.
			size_t size;	// Size of the file.
        };

    public:
        // Return true if package is found and valid. Else false.
        static bool setPackage(const char* path);

		// Clears the current package. Used when exiting application or switching package.
		static void clearPackage();

        // Return pointer to texture resource with specified GUI. Return nullptr if not found.
        static Texture* loadTexture(gui_t gui);

        // Return pointer to mesh resource with specified GUI. Return nullptr if not found.
        static Mesh* loadMesh(gui_t gui);

        // Return metadata of every resource in the package. Caller is responsible for the memory of returned array.
        static Array<MetaData> getMetaData();

	private:
		// Opens and closes the package file.
		static bool openFile();
		static void closeFile();

		// Searches for and loads a file from the package into memory. Caller is responsible for the returned memory.
		// metaDataPos will contain index of the file in the metaData array.
		static void* loadFile(gui_t gui, size_t& metaDataPos);

		static std::string packagePath;
		static Array<MetaData> metaData;
		static size_t numResourcesInPackage;
		static std::ifstream file;

		// The location of the beginning of the first file.
		static size_t baseOffset;

		// Contains a resource file copied from disk to be converted into a mesh/image.
		static void* rawFile;
};

#endif // __PACKAGE_READER__

