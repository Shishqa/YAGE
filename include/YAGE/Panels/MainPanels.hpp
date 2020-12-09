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
#include "ImageManager.hpp"
#include <climits>
/*============================================================================*/
namespace YAGE::MainPanels {

    class ImageCreator : public Sh::Clickable {
    public:

        explicit ImageCreator(Sh::UIWindow* target);

        void reactOnRelease(Sh::MouseButtonEvent& event) override;

    };

    class ImageOpener : public Sh::Clickable {
    public:

        explicit ImageOpener(Sh::UIWindow* target);

        void reactOnRelease(Sh::MouseButtonEvent& event) override;

    };

    class ImageSaver : public Sh::Clickable {
    public:

        explicit ImageSaver(Sh::UIWindow* target);

        void reactOnRelease(Sh::MouseButtonEvent&) override;

    };

    /*------------------------------------------------------------------------*/

    class MainMenu : public Sh::UIWindow {
    public:

        explicit MainMenu(const Sh::Frame& frame);

    };

    /*========================================================================*/

    class CanvasFrame : public Sh::UIFrame {
    public:

        explicit CanvasFrame(const Sh::Frame& frame);

    };

    class AsidePanel : public Sh::UIWindow {
    public:

        explicit AsidePanel(const Sh::Frame& frame);

    };

}
/*============================================================================*/
#endif //YAGE_MAIN_PANELS_HPP
/*============================================================================*/
