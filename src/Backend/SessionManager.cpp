/*============================================================================*/
#include "SessionManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

ImageManager& YAGE::IMAGE_MANAGER() {
    return SessionManager::Session().image_manager;
}

ToolManager& YAGE::TOOL_MANAGER() {
    return SessionManager::Session().tool_manager;
}

LayerManager& YAGE::LAYER_MANAGER() {
    return IMAGE_MANAGER().layerManager();
}

/*----------------------------------------------------------------------------*/

bool SessionManager::initSession() {

    SessionPtr() = new SessionManagers();

    Session().tool_manager.addTool<Tools::Pencil>();
    Session().tool_manager.addTool<Tools::Pencil>();
    Session().tool_manager.addTool<Tools::Eraser>();
    Session().tool_manager.addTool<Tools::Rectangle>();
    Session().tool_manager.addTool<Tools::Dropper>();

    Session().tool_manager.active_tool =
        *Session().tool_manager.tools.begin();

    if (!PluginManager::initPlugins()) {
        return false;
    }

    //IMAGE_MANAGER().loadImage("./TEST_IMAGE.png");

    Session().image_manager.createImage({1200, 800});

    return true;
}

bool SessionManager::finalizeSession() {

    PluginManager::finalizePlugins();
    delete SessionPtr();

    return true;

}

/*============================================================================*/