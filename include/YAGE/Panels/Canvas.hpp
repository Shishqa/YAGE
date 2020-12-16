/*============================================================================*/
#ifndef SHISHGL_CANVAS_HPP
#define SHISHGL_CANVAS_HPP
/*============================================================================*/
#include "Clickable.hpp"
#include "Image.hpp"
#include "RenderSystem.hpp"
#include "ToolManager.hpp"
#include "Pencil.hpp"
#include "UICanvas.hpp"
/*============================================================================*/
namespace YAGE {

    class Canvas : public Sh::UICanvas {
    public:

        explicit Canvas(const Sh::Frame& viewport);

        friend class ToolSusceptible;
    };

    /*------------------------------------------------------------------------*/

    class ToolSusceptible : public Sh::Clickable {
    public:

        explicit ToolSusceptible(Sh::UIWindow* target);

        bool onMouseButton(Sh::MouseButtonEvent& event) override;

        bool onMouseMove(Sh::MouseEvent& event) override;

    private:

        void updateTarget();

        bool applying_tool;

    };

}
/*============================================================================*/
#endif //SHISHGL_CANVAS_HPP
/*============================================================================*/
