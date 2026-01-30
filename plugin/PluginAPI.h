#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#include <stdint.h>

#define PLUGIN_API_VERSION_1

typedef struct PluginAPI
{
    uint32_t abi_version;
    uint32_t struct_size;

    void *(*create)(void);
    void (*destroy)(void);

    void *(*process)(void *, int);
} PluginAPI;

#ifdef __cplusplus
extern "C"
{
#endif
    typedef const PluginAPI *(plugin_init_fn)(uint32_t host_abi_version);
#ifdef __cplusplus
}
#endif
#endif