/*============================================================================*/

#include <dlfcn.h>
#include <cstdio>

#include "PluginManager.hpp"
#include <json.hpp>
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

bool PluginManager::initPlugins() {

    FILE* plug_list_file = fopen("plug_list.json", "r");
    auto plug_list = nlohmann::json::parse(plug_list_file);

    for (auto& plug : plug_list) {

        PluginAPI::Plugin* (*get)() = nullptr;

        void* handle = dlopen(plug["path"].get<std::string_view>().data(), RTLD_NOW);
        if (!handle) {
            printf("%s\n", dlerror());
            return false;
        }

        get = reinterpret_cast<PluginAPI::Plugin* (*)()>(dlsym(handle, "get_plugin"));
        if (!get) {
            printf("%s\n", dlerror());
        }

        PluginAPI::Plugin* new_plugin = get();

        new_plugin->init();

        Plugins()[handle] = PluginToken{ new_plugin, plug["icon path"] };

    }

    return true;
}

bool PluginManager::deinitPlugins() {

    for (auto& plugin : Plugins()) {

        plugin.second.impl->deinit();
        dlclose(plugin.first);

    }

    Plugins().clear();

    return true;
}

/*============================================================================*/