#include "SharedLib.h"
#include "PluginAPI.h"

struct LoadedPlugin
{
    SharedLib lib;
    PluginApi api;
    void *instance;
};