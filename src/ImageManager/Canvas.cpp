/*============================================================================*/
#include "Canvas.hpp"
#include "ImageManager.hpp"
#include "Pencil.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

Canvas::Canvas(const Sh::Frame& frame)
        : UICanvas(frame)
        , need_update(true) {
    setBehavior<CanvasBehavior>();
}

/*----------------------------------------------------------------------------*/

void Canvas::onRender() {
    if (need_update) {
        ImageManager::displayTo(canvas);
        need_update = false;
    }
    UICanvas::onRender();
}

/*============================================================================*/

CanvasBehavior::CanvasBehavior(Sh::UIWindow* target)
        : Clickable(target)
        , applying_tool(false) {
    ToolManager::set<Tools::Pencil>();
}

/*----------------------------------------------------------------------------*/

bool CanvasBehavior::onMouseButton(Sh::MouseButtonEvent& event) {

    if (!Clickable::onMouseButton(event)) {
        return false;
    }

    if (event.state() == Sh::Mouse::DOWN &&
        event.button() == Sh::Mouse::LEFT) {

        applying_tool = true;
        ToolManager::activeTool().startApplying(
                ImageManager::getActiveLayer(),
                static_cast<Sh::Vector2<int64_t>>(event.where() - target<Sh::Window>()->getPos())
                );

    } else if (event.state() == Sh::Mouse::UP &&
               event.button() == Sh::Mouse::LEFT) {
        applying_tool = false;
        ToolManager::activeTool().stopApplying(
                ImageManager::getActiveLayer(),
                static_cast<Sh::Vector2<int64_t>>(event.where() - target<Sh::Window>()->getPos())
                );
    }

    target<Canvas>()->setUpdate();
    return true;
}

/*----------------------------------------------------------------------------*/

bool CanvasBehavior::onMouseMove(Sh::MouseEvent& event) {

     if (applying_tool) {
         ToolManager::activeTool().update(
                 ImageManager::getActiveLayer(),
                 static_cast<Sh::Vector2<int64_t>>(event.where() - target<Sh::Window>()->getPos())
                 );

         target<Canvas>()->setUpdate();
         return true;
     }

     return false;
}

/*============================================================================*/
