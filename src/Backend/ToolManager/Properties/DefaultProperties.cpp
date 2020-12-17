/*============================================================================*/
#include "DefaultProperties.hpp"
#include "ColorPicker.hpp"
#include "NumberPickers.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

Sh::UIWindow* ColorProp::summonPicker(const Sh::Frame &frame) {
    return Sh::WindowManager::create<ColorPicker>(
        Sh::Frame{
            frame.pos,
            {frame.size.x, frame.size.x + 15}
        }, this
        );
}

Sh::UIWindow* IntProp::summonPicker(const Sh::Frame &frame) {

    auto slider = Sh::WindowManager::create<Sh::UIHorizontalSlider<IntPropPicker>>(
        Sh::Frame{frame.pos, {frame.size.x, 25}}, 7, this
    );
    slider->slider->as<IntPropPicker>()->onPropUpdate();

    slider->applyStyle(
        Sh::ColorFill{Sh::Color(50, 50, 50)}, Sh::UIWindow::ALL
    );

    slider->slider->applyStyle(
        Sh::ColorFill{Sh::Color(200, 200, 240)}, Sh::UIWindow::ALL
    );

    return slider;
}

Sh::UIWindow* FloatingPointProp::summonPicker(const Sh::Frame &frame) {

    auto slider = Sh::WindowManager::create<Sh::UIHorizontalSlider<FloatingPropPicker>>(
        Sh::Frame{frame.pos, {frame.size.x, 25}}, 7, this
    );
    slider->slider->as<IntPropPicker>()->onPropUpdate();

    slider->applyStyle(
        Sh::ColorFill{Sh::Color(50, 50, 50)}, Sh::UIWindow::ALL
    );

    slider->slider->applyStyle(
        Sh::ColorFill{Sh::Color(200, 200, 240)}, Sh::UIWindow::ALL
    );

    return slider;
}

Sh::UIWindow* BoolProp::summonPicker(const Sh::Frame& frame) {
    return Sh::WindowManager::create<Sh::UIWindow>(
        Sh::Frame{ frame.pos, {20, 20} }
        )
        ->applyStyle(
            Sh::ColorFill(Sh::Color::MAGENTA), Sh::UIWindow::ALL
            );
}