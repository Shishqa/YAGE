/*============================================================================*/
#include "ColorPicker.hpp"
#include "Convert.hpp"
#include "UISlider.hpp"
#include "ColorFill.hpp"
#include "Stroke.hpp"
#include "Bordered.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

HueSlider::HueSlider(Sh::UIWindow* target,
                     const Sh::Frame& frame,
                     ColorProp* to_track)
        : PropSlider(target, frame, to_track)
        { }

/*----------------------------------------------------------------------------*/

void HueSlider::modifyProp(const Sh::Vector2<double> &pos) {

    getProp<ColorProp>()->h = pos.x;
    Sh::EventSystem::sendEvent<PropUpdateEvent>(getProp<ColorProp>(), getProp<ColorProp>());

}

/*----------------------------------------------------------------------------*/

void HueSlider::onPropUpdate() {
    set({getProp<ColorProp>()->h, 0});
}

/*============================================================================*/

YAGE::HuePicker::HuePicker(const Sh::Frame& frame, ColorProp* to_track)
        : Sh::UICanvas(frame, Sh::Color::BLACK)
        , color(to_track) {

    for (int64_t x = 0; x < static_cast<int64_t>(canvas.size().x); ++x) {

        double h = static_cast<double>(x) / static_cast<double>(canvas.size().x);

        for (int64_t y = 0; y < static_cast<int64_t>(canvas.size().y); ++y) {
            canvas.setPixel({static_cast<size_t>(x), static_cast<size_t>(y)},
                             ColorUtils::Convert::HSVtoRGB(h, 1.0, 1.0)
                             );
        }
    }

    auto slider = attach<Sh::UIHorizontalSlider<HueSlider>>(
            Sh::Frame{ {0, 0}, frame.size }, 10, color
            );
    slider->slider->applyStyle(
                    Sh::Bordered{2, Sh::Color::BLACK}, Sh::UIWindow::ALL,
                    Sh::ColorFill{Sh::Color::WHITE}, Sh::UIWindow::ALL
                    );

    slider->slider->as<HueSlider>()->onPropUpdate();
}

/*============================================================================*/

SVSlider::SVSlider(Sh::UIWindow* target,
                   const Sh::Frame& frame,
                   ColorProp* to_track)
        : PropSlider(target, frame, to_track)
        { }

void SVSlider::modifyProp(const Sh::Vector2<double> &pos) {
    getProp<ColorProp>()->s = pos.x;
    getProp<ColorProp>()->v = 1 - pos.y;
}

void SVSlider::onPropUpdate() {
    set({getProp<ColorProp>()->s, 1 - getProp<ColorProp>()->v});
}

/*============================================================================*/

SVPicker::SVPicker(const Sh::Frame& frame, ColorProp* to_track)
        : Sh::UICanvas(frame, Sh::Color::WHITE)
        , color(to_track) {

    slider = attach<Sh::UIFreeSlider<SVSlider>>(
            Sh::Frame{{0, 0}, frame.size}, Sh::Vector2<double>{10, 10},
            color
            );
    slider->slider->applyStyle(
                    Sh::Bordered{2, Sh::Color::BLACK}, Sh::UIWindow::ALL,
                    Sh::ColorFill{Sh::Color::WHITE}, Sh::UIWindow::ALL
                    );

    slider->slider->as<SVSlider>()->onPropUpdate();

    Sh::SubscriptionManager::subscribe<PropUpdateEvent>(this, color);
    update();
}

void SVPicker::update() {

    for (int64_t x = 0; x < static_cast<int64_t>(canvas.size().x); ++x) {

        double S = static_cast<double>(x) / static_cast<double>(canvas.size().x);

        for (int64_t y = 0; y < static_cast<int64_t>(canvas.size().y); ++y) {

            double V = 1 - static_cast<double>(y) / static_cast<double>(canvas.size().y);

            canvas.setPixel({static_cast<size_t>(x), static_cast<size_t>(y)},
                            ColorUtils::Convert::HSVtoRGB(color->h, S, V)
            );
        }
    }
}

bool SVPicker::onEvent(Sh::Event& event) {

    if (event.mask() != Sh::Event::getMask<PropUpdateEvent>()) {
        return false;
    }

    auto prop_update = dynamic_cast<PropUpdateEvent&>(event);

    if (prop_update.updated() == color) {
        update();
        return true;
    }

    return false;
}

/*============================================================================*/

ColorPicker::ColorPicker(const Sh::Frame &frame,
                         ColorProp* to_track)
        : Sh::UIWindow(frame) {

    attach<SVPicker>(
        Sh::Frame{
            {BORDER_SIZE, BORDER_SIZE},
            {frame.size.x - 2 * BORDER_SIZE, frame.size.x - 2 * BORDER_SIZE}
        },
        to_track
    );

    attach<HuePicker>(
        Sh::Frame{
            {BORDER_SIZE, frame.size.x},
            {frame.size.x - 2 * BORDER_SIZE, frame.size.y - frame.size.x - BORDER_SIZE}
        },
        to_track
    );

}

/*============================================================================*/
