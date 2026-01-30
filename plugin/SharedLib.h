struct SharedLibrary {
    void* handle;

    bool open(const char* path);
    void* symbol(const char* name);
    void close();
};