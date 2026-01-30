#ifndef SHARED_LIBRARY_H
#define SHARED_LIBRARY_H

namespace sharedlib
{
    class SharedLib
    {
    public:
        explicit SharedLib() noexcept = default;

        SharedLib(const SharedLib &) = delete;
        SharedLib &operator=(const SharedLib &) = delete;
        SharedLib(SharedLib &&) noexcept;
        SharedLib &operator=(SharedLib &&) noexcept;

        bool open(const char *path);
        void *symbol(const char *name);
        void close();

        ~SharedLib() noexcept;

    private:
        void *handle = nullptr;
    };

#endif SHARED_LIBRARY_H
}