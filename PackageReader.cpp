#include "PackageReader.hpp"

// Return true if package is found and valid. Else false.
bool PackageReader::setPackage(const char* path) {
    return false;
}

// Return pointer to texture resource with specified GUI. Return nullptr if not found.
Texture* PackageReader::loadTexture(gui_t gui) {
    return nullptr;
}

// Return pointer to mesh resource with specified GUI. Return nullptr if not found.
Mesh* PackageReader::loadMesh(gui_t gui) {
    return nullptr;
}

// Return array of all GUIs in the package.
Array<gui_t> PackageReader::getGuis() {
    return Array<gui_t>();
}
