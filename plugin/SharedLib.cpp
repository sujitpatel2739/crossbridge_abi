#include "SharedLib.hpp"

#if defined(_WIN32)
#include <windows.h>
using LibHandle = HMODULE;
using procAddr = FARPROC;
#else
#include <dlfcn.h>
using LibHandle = void *;
using procAddr = void *;
#endif

namespace sharedlib
{

    SharedLib::SharedLib() noexcept
    {
        handle = nullptr;
    }

    SharedLib::SharedLib(SharedLib &&other) noexcept
    {
        handle = other.handle;
        other.handle = nullptr;
    }

    SharedLib &SharedLib::operator=(SharedLib &&other) noexcept
    {
        if (this != &other)
        {
            close();
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    bool SharedLib::open(const char *path)
    {
        if (handle != nullptr)
            return false;

#if defined(_WIN32)
        handle = LoadLibraryA(path);
#else
        handle = dlopen(path, RTLD_NOW);
#endif
        return (handle != nullptr);
    }

    void *SharedLib::symbol(const char *name)
    {
        if (handle == nullptr)
            return nullptr;

        procAddr ptr = nullptr;
#if defined(_WIN32)
        ptr = GetProcAddress(static_cast<LibHandle>(handle), name);
#else
        ptr = dlsym(handle, name);
#endif
        return ptr;
    }

    SharedLib::~SharedLib() noexcept
    {
        close();
    }

    void SharedLib::close()
    {
        if (handle != nullptr)
        {
#if defined(_WIN32)
            FreeLibrary(static_cast<LibHandle>(handle));
#else
            dlclose(handle);
#endif
        }
        handle = nullptr;
    }
} // namespace sharedlib