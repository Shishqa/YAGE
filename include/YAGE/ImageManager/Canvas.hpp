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

    class CanvasBehavior;

    class Canvas : public Sh::UICanvas {
    public:

        explicit Canvas(const Sh::Frame& viewport);

    protected:

        void onRender() override;

    private:

        friend class CanvasBehaviour;

    };

    /*------------------------------------------------------------------------*/

    class CanvasBehavior : public Sh::Clickable {
    public:

        explicit CanvasBehavior(Sh::UIWindow* target);

        bool onMouseButton(Sh::MouseButtonEvent& event) override;

        bool onMouseMove(Sh::MouseEvent& event) override;

    private:

        bool applying_tool;

    };

}
/*============================================================================*/
#endif //SHISHGL_CANVAS_HPP
/*============================================================================*/
