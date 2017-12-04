#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include <atomic>

#include "gui_t.hpp"
#include "SharedPtr.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "HashMap.hpp"
#include "SpinLock.hpp"
#include "Future.hpp"

// Asynchronous operations are handled by the ResourceManager. Not the PackageReader.
class ResourceManager {
    public:
        static void initialize();

        // Synchronous load methods.
        static SharedPtr<Texture> loadTexture(gui_t gui);
        static SharedPtr<Mesh> loadMesh(gui_t gui);

        // Asynchronous load methods.
        // Something like this... Poll the handle to check availability.
        static Future<SharedPtr<Texture>> aloadTexture(gui_t gui);
        static Future<SharedPtr<Mesh>> aloadMesh(gui_t gui);

        // Something like this... The callback is invoked when operation completes.
        // The SharedPtr parameter of the callback contains the loaded resource.
        static void aloadTexture(gui_t gui, Function<void(SharedPtr<Texture>)> callback);
        static void aloadMesh(gui_t gui, Function<void(SharedPtr<Mesh>)> callback);

        static void garbageCollectTextures();
        static void garbageCollectMeshes();
        static void garbageCollect();

    private:
        template<typename T>
        struct Entry {
            SpinLock lock;
            SharedPtr<T> data;
        };
        static HashMap<gui_t, Entry<Texture>*> mTextures;
        static HashMap<gui_t, Entry<Mesh>*> mMeshes;

};



#endif // __RESOURCE_MANAGER__
