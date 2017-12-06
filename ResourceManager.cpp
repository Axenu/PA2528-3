#include "ResourceManager.hpp"
#include "PackageReader.hpp"
#include "ThreadPool.hpp"

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
    Entry<Mesh>** entryPtr = mMeshes.find(gui);
    if(!entryPtr) {
        // No such resource exists. Return default error mesh. TODO
        return nullptr;
    }
    Entry<Mesh>& entry = **entryPtr;

    entry.lock.lock();
    SharedPtr<Mesh> mesh = entry.data;
    entry.lock.unlock();

    if(mesh != nullptr) {
        return mesh;
    }

    mesh = PackageReader::loadMesh(gui);
    if(mesh == nullptr) {
        // No such resource exists. Return default error mesh. TODO
        return nullptr;
    }

    entry.lock.lock();
    if(entry.data == nullptr) {
        entry.data = mesh;
    }
    else {
        mesh = entry.data;
    }
    entry.lock.unlock();

    return mesh;
}

Promise<SharedPtr<Texture>> ResourceManager::aloadTexture(gui_t gui) {
    return ThreadPool::promise<SharedPtr<Texture>>([gui](){return loadTexture(gui);});
}

Promise<SharedPtr<Mesh>> ResourceManager::aloadMesh(gui_t gui) {
    return ThreadPool::promise<SharedPtr<Mesh>>([gui](){return loadMesh(gui);});
}


void ResourceManager::aloadTexture(gui_t gui, Function<void(SharedPtr<Texture>)> callback) {
    ThreadPool::launch([gui, callback](){callback(loadTexture(gui));});
}

void ResourceManager::aloadMesh(gui_t gui, Function<void(SharedPtr<Mesh>)> callback) {
    ThreadPool::launch([gui, callback](){callback(loadMesh(gui));});
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

void ResourceManager::garbageCollectMeshes() {
    for(Entry<Mesh>* entry : mMeshes) {
        entry->lock.lock();
        if(entry->data.getReferenceCount() == 1) {
            entry->data = nullptr;
        }
        entry->lock.unlock();
    }
}

void ResourceManager::garbageCollect() {
    garbageCollectTextures();
    garbageCollectMeshes();
}
