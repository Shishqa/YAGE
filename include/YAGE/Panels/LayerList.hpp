/*============================================================================*/
#ifndef YAGE_LAYERLIST_HPP
#define YAGE_LAYERLIST_HPP
/*============================================================================*/
#include "ImageManager.hpp"
#include "GUI.hpp"
#include "Styles.hpp"
#include "Behaviors.hpp"
/*============================================================================*/
namespace YAGE {

    class LayerSelectEvent : public Sh::Event {
    public:

        explicit LayerSelectEvent(size_t layer)
                : selected_layer(layer)
                { }

        [[nodiscard]]
        size_t layer() const {
            return selected_layer;
        }

        Sh::EventMask mask() override {
            return Sh::Event::getMask<LayerSelectEvent>();
        }

        bool happen(Sh::Listener* listener) override {
            return listener->onEvent(*this);
        }

    private:

        size_t selected_layer;
    };

    /*------------------------------------------------------------------------*/

    class LayerSelector : public Sh::Clickable {
    public:

        explicit LayerSelector(Sh::UIWindow* target, size_t layer);

        void reactOnRelease(Sh::MouseButtonEvent& event) override;

        bool onEvent(Sh::Event& event) override;

    private:

        size_t to_set;
    };

    /*------------------------------------------------------------------------*/

    class LayerList : public Sh::UIFrame {
    public:

        static constexpr double BUTTON_HEIGHT = 30;
        static constexpr double SB_WIDTH = 10;

        explicit LayerList(const Sh::Frame& frame);

        bool onEvent(Sh::Event& event) override;

        void onRender() override;

        void update();

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
            ImageManager::addLayer();
        }
    };

    class LayerDeleter : public Sh::Clickable {
    public:

        explicit LayerDeleter(Sh::UIWindow* target)
                : Sh::Clickable(target)
                { }

        void reactOnRelease(Sh::MouseButtonEvent&) override {
            ImageManager::removeLayer();
        }

    };


    class LayerPanel : public Sh::UIWindow {
    public:

        explicit LayerPanel(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            auto adder = attach<Sh::UILabelButton<LayerAdder>>(
                Sh::Frame{ {10, 10}, {(frame.size.x - 30) / 2, 30} },
                "+", Sh::IPlatform::Align::CENTER
                );
            adder->label->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{ Sh::Color::BLACK }
                );
            adder->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{ Sh::Color(70, 140, 70) }
                );

            auto deleter = attach<Sh::UILabelButton<LayerDeleter>>(
                Sh::Frame{ {(frame.size.x - 30) / 2 + 20, 10}, {(frame.size.x - 30) / 2, 30} },
                "-", Sh::IPlatform::Align::CENTER
            );
            deleter->label->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{ Sh::Color::BLACK }
            );
            deleter->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{ Sh::Color(140, 70, 70) }
            );

            attach<LayerList>(Sh::Frame{
                {10, 50}, {frame.size.x - 20, 100}
            });

        }


    };

}
/*============================================================================*/
#endif //YAGE_LAYERLIST_HPP
/*============================================================================*/
