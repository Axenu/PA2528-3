#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "gui_t.hpp"
#include "SharedPtr.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

// Asynchronous operations are handled by the ResourceManager. Not the PackageReader.
class ResourceManager {
    public:
        static void initialize();

        // Synchronous load methods.
        static SharedPtr<Texture> loadTexture(gui_t gui);
        static SharedPtr<Mesh> loadMesh(gui_t gui);

        // Asynchronous load methods.
        template<typename T>
        struct AsyncHandle {
            // Return pointer of resource if ready, else nullptr. Will wait (block) for specified duration.
            SharedPtr<T> wait(size_t milliseconds);
        };
        // Something like this... Poll the handle to check availability.
        static AsyncHandle<Texture> aloadTexture(gui_t gui);
        static AsyncHandle<Mesh> aloadMesh(gui_t gui);

        template<typename T>
        using Callback = void (*)(SharedPtr<T>);
        // Something like this... The callback is invoked when operation completes.
        // The SharedPtr parameter of the callback contains the loaded resource.
        static aloadTexture(gui_t gui, Callback<Texture> callback);
        static aloadMesh(gui_t gui, Callback<Mesh> callback);



};



#endif // __RESOURCE_MANAGER__
