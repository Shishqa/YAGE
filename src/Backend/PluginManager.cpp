/*============================================================================*/
#include <dlfcn.h>
#include <fstream>

#include "PluginManager.hpp"
#include "SessionManager.hpp"
#include <json.hpp>
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

bool PluginManager::initPlugins() {

    std::ifstream f_plug_list("plug_list.json");
    auto plug_list = nlohmann::json::parse(f_plug_list);
    f_plug_list.close();

    for (auto& plug : plug_list) {

        Plugin* (*get)() = nullptr;

        PluginHandle handle = dlopen(plug["path"].get<std::string_view>().data(), RTLD_NOW);
        if (!handle) {
            printf("%s\n", dlerror());
            return false;
        }

        get = reinterpret_cast<Plugin* (*)()>(dlsym(handle, "get_plugin"));
        if (!get) {
            printf("%s\n", dlerror());
        }

        Plugin* new_plugin = get();

        new_plugin->init();

        Plugins()[handle] = new PluginToken{ new_plugin, plug["icon path"].get<std::string>() };

        std::cout << "adding " << plug["path"] << "\n";

        TOOL_MANAGER().addTool<PluginTool>(Plugins()[handle]);
    }

    return true;
}

bool PluginManager::finalizePlugins() {

    for (auto& plugin : Plugins()) {

        plugin.second->impl->deinit();
        dlclose(plugin.first);

        delete plugin.second;
    }

    Plugins().clear();

    return true;
}

/*============================================================================*/

/*============================================================================*/