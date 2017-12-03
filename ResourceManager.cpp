#include "ResourceManager.hpp"
#include "PackageReader.hpp"

HashMap<gui_t, ResourceManager::Entry<Texture>*> ResourceManager::mTextures;
HashMap<gui_t, ResourceManager::Entry<Mesh>*> ResourceManager::mMeshes;

void ResourceManager::initialize() {
    Array<PackageReader::MetaData> metaData = PackageReader::getMetaData();
    metaData.data = new PackageReader::MetaData();
    metaData.data->type = PackageReader::MetaData::Type::TEXTURE;
    metaData.data->gui = 0;
    metaData.size = 1;
    for(size_t i = 0; i < metaData.size; i++) {
        const PackageReader::MetaData& d = metaData.data[i];
        using T = PackageReader::MetaData::Type;
        switch(d.type) {
            case T::TEXTURE:    mTextures.insert(d.gui, new Entry<Texture>()); break;
            case T::MESH:       mMeshes.insert(d.gui, new Entry<Mesh>()); break;
            default:            break;
        }
    }
    delete metaData.data;
}

SharedPtr<Texture> ResourceManager::loadTexture(gui_t gui) {
    Entry<Texture>** entryPtr = mTextures.find(gui);
    if(!entryPtr) {
        // No such resource exists. Return default error texture. TODO
        return nullptr;
    }
    Entry<Texture>& entry = **entryPtr;

    entry.lock.lock();
    SharedPtr<Texture> texture = entry.data;
    entry.lock.unlock();

    if(texture != nullptr) {
        return texture;
    }

    texture = PackageReader::loadTexture(gui);
    if(texture == nullptr) {
        // No such resource exists. Return default error texture. TODO
        return nullptr;
    }

    entry.lock.lock();
    if(entry.data == nullptr) {
        entry.data = texture;
    }
    else {
        texture = entry.data;
    }
    entry.lock.unlock();

    return texture;
}

SharedPtr<Mesh> ResourceManager::loadMesh(gui_t gui) {
    return SharedPtr<Mesh>();
}


void ResourceManager::garbageCollectTextures() {
    for(Entry<Texture>* entry : mTextures) {
        entry->lock.lock();
        if(entry->data.getReferenceCount() == 1) {
            entry->data = nullptr;
        }
        entry->lock.unlock();
    }
}
