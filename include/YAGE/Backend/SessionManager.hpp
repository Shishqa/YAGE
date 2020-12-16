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

        static bool finalizeSession();

        struct SessionManagers {

            ImageManager image_manager;
            ToolManager tool_manager;

        };

        static SessionManagers& Session() {
            return *SessionPtr();
        }

    private:

        static SessionManagers*& SessionPtr() {
            static SessionManagers* SESSION_PTR;
            return SESSION_PTR;
        }

    };

    ToolManager& TOOL_MANAGER();

    ImageManager& IMAGE_MANAGER();

    LayerManager& LAYER_MANAGER();

}
/*============================================================================*/
#endif //YAGE_SESSIONMANAGER_HPP
/*============================================================================*/