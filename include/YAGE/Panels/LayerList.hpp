/*============================================================================*/
#ifndef YAGE_LAYERLIST_HPP
#define YAGE_LAYERLIST_HPP
/*============================================================================*/
#include "GUI.hpp"
#include "Styles.hpp"
#include "Behaviors.hpp"
#include "SessionManager.hpp"
/*============================================================================*/
namespace YAGE {

    class LayerList : public Sh::UISelectList {
    public:

        static constexpr double BUTTON_HEIGHT = 30;
        static constexpr double SB_WIDTH = 10;

        explicit LayerList(const Sh::Frame& frame);

        bool onEvent(Sh::Event& event) override;

        void update() override;

        void onSelect(int option) override;

    private:

        size_t n_layers;

    };

    /*------------------------------------------------------------------------*/

    class LayerAdder : public Sh::Clickable {
    public:

        explicit LayerAdder(Sh::UIWindow* target)
                : Sh::Clickable(target)
                { }

        void reactOnRelease(Sh::MouseButtonEvent&) override {
            LAYER_MANAGER().addLayer();
        }
    };

    class LayerDeleter : public Sh::Clickable {
    public:

        explicit LayerDeleter(Sh::UIWindow* target)
                : Sh::Clickable(target)
                { }

        void reactOnRelease(Sh::MouseButtonEvent&) override {
            LAYER_MANAGER().removeLayer();
        }
    };


    class LayerPanel : public Sh::UIWindow {
    public:

        explicit LayerPanel(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            auto adder = attach<Sh::UIButton<LayerAdder>>(
                Sh::Frame{ {10, 10}, {(frame.size.x - 30) / 2, 30} }
                );
            adder->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{ Sh::Color(70, 140, 70) },
                Sh::Label("+", Sh::Color::BLACK, 20, Sh::Text::Align::CENTER)
                );

            auto deleter = attach<Sh::UIButton<LayerDeleter>>(
                Sh::Frame{ {(frame.size.x - 30) / 2 + 20, 10}, {(frame.size.x - 30) / 2, 30} }
            );
            deleter->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{ Sh::Color(140, 70, 70) },
                Sh::Label("-", Sh::Color::BLACK, 20, Sh::Text::Align::CENTER)
            );

            auto list = attach<LayerList>(Sh::Frame{
                {10, 50}, {frame.size.x - 20, 100}
            });
            list->update();
        }

    };

}
/*============================================================================*/
#endif //YAGE_LAYERLIST_HPP
/*============================================================================*/
