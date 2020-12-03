/*============================================================================*/
#include "Canvas.hpp"
#include "ImageManager.hpp"
#include "Pencil.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

Canvas::Canvas(const Sh::Frame& frame)
        : UICanvas(frame) {
    addBehavior<CanvasBehavior>();
}

/*----------------------------------------------------------------------------*/

void Canvas::onRender() {

    //canvas.fill(Sh::Color::WHITE);
    ImageManager::displayTo(canvas);

    UICanvas::onRender();
}

/*============================================================================*/

CanvasBehavior::CanvasBehavior(Sh::UIWindow* target)
        : Clickable(target)
        , applying_tool(false) {
    ToolManager::set<Pencil>();
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

    return true;
}

/*----------------------------------------------------------------------------*/

bool CanvasBehavior::onMouseMove(Sh::MouseEvent& event) {
     if (applying_tool) {
         ToolManager::activeTool().update(
                 ImageManager::getActiveLayer(),
                 static_cast<Sh::Vector2<int64_t>>(event.where() - target<Sh::Window>()->getPos())
                 );
         return true;
     }

     return false;
}

/*============================================================================*/
