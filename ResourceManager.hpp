#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "gui_t.hpp"
#include "SharedPtr.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

// Asynchronous operations are handled by the ResourceManager. Not the PackageReader.
class ResourceManager {
    public:
        // Synchronous load methods.
        static SharedPtr<Texture> loadTexture(gui_t gui);
        static SharedPtr<Mesh> loadMesh(gui_t gui);

        // Asynchronous load methods.
        struct AsyncHandle {
            // Return true if ready, else false. Will wait (block) for specified duration.
            bool wait(size_t milliseconds);
        };
        // Something like this... Poll the handle to check availability.
        static AsyncHandle aloadTexture(gui_t gui);
        static AsyncHandle aloadMesh(gui_t gui);

        template<typename T>
        using Callback = void (*)(SharedPtr<T>);
        using TextureCallback = Callback<Texture>;
        using MeshCallback = Callback<Mesh>;

        // Something like this... The callback is invoked when operation completes.
        static aloadTexture(gui_t gui, TextureCallback callback);
        static aloadMesh(gui_t gui, MeshCallback callback);


};



#endif // __RESOURCE_MANAGER__
