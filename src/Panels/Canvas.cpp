/*============================================================================*/
#include "Canvas.hpp"
#include "SessionManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

Canvas::Canvas(const Sh::Frame& frame)
        : UICanvas(frame) {
    setBehavior<ToolSusceptible>();
    LAYER_MANAGER().displayTo(canvas);
}

/*============================================================================*/

ToolSusceptible::ToolSusceptible(Sh::UIWindow *target)
        : Clickable(target)
        , applying_tool(false)
        { }

/*----------------------------------------------------------------------------*/

void ToolSusceptible::updateTarget() {
    auto target_canvas = target<Canvas>();
    if (target_canvas) {
        //target_canvas->canvas.fill(static_cast<Sh::Color>(GlobalColorManager::SecondaryColor()));
        target_canvas->canvas.fill(Sh::Color::NONE);
        LAYER_MANAGER().displayTo(target_canvas->canvas);
    }
}

/*----------------------------------------------------------------------------*/

bool ToolSusceptible::onMouseButton(Sh::MouseButtonEvent& event) {

    if (!Clickable::onMouseButton(event)) {
        return false;
    }

    if (event.state() == Sh::Mouse::DOWN &&
        event.button() == Sh::Mouse::LEFT) {

        if (TOOL_MANAGER().activeTool().needLayer()) {
            LAYER_MANAGER().addLayer();
        }

        applying_tool = true;
        TOOL_MANAGER().activeTool().startApplying(
            LAYER_MANAGER().getActiveLayer(),
            static_cast<Sh::Vector2<int64_t>>(event.where() - target<Sh::Window>()->getPos())
            );

    } else if (event.state() == Sh::Mouse::UP &&
               event.button() == Sh::Mouse::LEFT &&
               applying_tool) {

        applying_tool = false;
        TOOL_MANAGER().activeTool().stopApplying(
            LAYER_MANAGER().getActiveLayer(),
            static_cast<Sh::Vector2<int64_t>>(event.where() - target<Sh::Window>()->getPos())
            );
    }

    updateTarget();
    return true;
}

/*----------------------------------------------------------------------------*/

bool ToolSusceptible::onMouseMove(Sh::MouseEvent& event) {

     if (applying_tool) {

         TOOL_MANAGER().activeTool().update(
             LAYER_MANAGER().getActiveLayer(),
             static_cast<Sh::Vector2<int64_t>>(event.where() - target<Sh::Window>()->getPos())
         );

         updateTarget();
         return true;
     }

     return false;
}

/*============================================================================*/
