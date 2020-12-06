/*============================================================================*/
#ifndef YAGE_PLUGIN_MANAGER_HPP
#define YAGE_PLUGIN_MANAGER_HPP
/*============================================================================*/

#include <memory>
#include <unordered_set>

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <json.hpp>
#include "api.hpp"

/*============================================================================*/
namespace YAGE {

    class PluginManager {
    public:

        static bool initPlugins();

        static bool deinitPlugins();

    private:

        using PluginToken = PluginAPI::Plugin*;
        using PluginPool  = std::unordered_map<void*, PluginToken>;

        static PluginPool& Plugins() {
            static PluginPool POOL;
            return POOL;
        }

    };


}
/*============================================================================*/
#endif //YAGE_PLUGIN_MANAGER_HPP
/*============================================================================*/