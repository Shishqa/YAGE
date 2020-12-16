/*============================================================================*/
#ifndef YAGE_MAIN_PANELS_HPP
#define YAGE_MAIN_PANELS_HPP
/*============================================================================*/
#include "Behaviors.hpp"
#include "Styles.hpp"
#include "GUI.hpp"
#include "Canvas.hpp"
#include "ColorPicker.hpp"
#include "LayerList.hpp"
#include <climits>
/*============================================================================*/
namespace YAGE::MainPanels {

    class ImageOpener : public Sh::Clickable {
    public:

        explicit ImageOpener(Sh::UIWindow* target);

        void reactOnRelease(Sh::MouseButtonEvent& event) override;

        bool onEvent(Sh::Event& event) override;

    };

    class ImageSaver : public Sh::Clickable {
    public:

        explicit ImageSaver(Sh::UIWindow* target);

        void reactOnRelease(Sh::MouseButtonEvent&) override;

        bool onEvent(Sh::Event& event) override;
    };

    /*------------------------------------------------------------------------*/

    class UpperMenu : public Sh::UIWindow {
    public:

        explicit UpperMenu(const Sh::Frame& frame);

    };

    /*========================================================================*/

    class CanvasFrame : public Sh::UIFrame {
    public:

        explicit CanvasFrame(const Sh::Frame& frame);

        void update();

        bool onEvent(Sh::Event& event) override;

    };

    /*========================================================================*/

    class AsidePanel : public Sh::UIWindow {
    public:

        explicit AsidePanel(const Sh::Frame& frame);

    };

}
/*============================================================================*/
#endif //YAGE_MAIN_PANELS_HPP
/*============================================================================*/
