/*============================================================================*/
#ifndef YAGE_SESSIONMANAGER_HPP
#define YAGE_SESSIONMANAGER_HPP
/*============================================================================*/
#include "ImageManager.hpp"
#include "ToolManager.hpp"
#include "PluginManager.hpp"
#include "Tools.hpp"
/*============================================================================*/
namespace YAGE {

    class SessionManager {
    public:

        SessionManager() = delete;

        static bool initSession();

        static bool finalizeSession() {
            PluginManager::finalizePlugins();
            return true;
        }

        struct SessionManagers {

            ImageManager image_manager;
            ToolManager tool_manager;

        };

        static SessionManagers& Session() {
            static SessionManagers SESSION;
            return SESSION;
        }

    };

    ToolManager& TOOL_MANAGER();

    ImageManager& IMAGE_MANAGER();

    LayerManager& LAYER_MANAGER();

}
/*============================================================================*/
#endif //YAGE_SESSIONMANAGER_HPP
/*============================================================================*/