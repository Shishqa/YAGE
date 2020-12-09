/*============================================================================*/
#include "ColorPicker.hpp"
#include "Convert.hpp"
#include "UISlider.hpp"
#include "ColorFill.hpp"
#include "ToolManager.hpp"
#include "Stroke.hpp"
#include "Bordered.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

ColorManager::Color ColorManager::primary   = {0.0, 0.0, 0.0, 1.0};
ColorManager::Color ColorManager::secondary = {0.0, 0.0, 1.0, 1.0};

/*============================================================================*/

class HueSlider : public Sh::Slidable {
public:

    explicit HueSlider(Sh::UIWindow* target,
                       const Sh::Frame& frame,
                       ColorManager::Color* selectable)
            : Sh::Slidable(target, frame)
            , color(selectable)
            { }

    void onSlide(const Sh::Vector2<double>& pos) override {

        color->h = pos.x;
        Sh::Color new_color = ColorUtils::Convert::HSVtoRGB(color->h,
                                                            color->s,
                                                            color->v);

        new_color.a = static_cast<uint8_t>(color->a * 255);

        ToolManager::activeTool().getProperty<Color>().value = new_color;
    }

private:

    ColorManager::Color* color;
};

/*----------------------------------------------------------------------------*/

class SVSlider : public Sh::Slidable {
public:

    explicit SVSlider(Sh::UIWindow* target, const Sh::Frame& frame,
                      ColorManager::Color* selectable)
            : Sh::Slidable(target, frame)
            , color(selectable)
            { }

    void onSlide(const Sh::Vector2<double>& pos) override {

        color->s = pos.x;
        color->v = 1 - pos.y;
        Sh::Color new_color = ColorUtils::Convert::HSVtoRGB(color->h,
                                                            color->s,
                                                            color->v);
        new_color.a = static_cast<uint8_t>(color->a * 255);

        ToolManager::activeTool().getProperty<Color>().value = new_color;
    }

private:

    ColorManager::Color* color;

};

/*============================================================================*/

YAGE::HuePicker::HuePicker(const Sh::Frame& frame, ColorManager::Color* color)
        : Sh::UICanvas(frame, Sh::Color::BLACK) {

    for (int64_t x = 0; x < static_cast<int64_t>(canvas.size().x); ++x) {

        double h = static_cast<double>(x) / static_cast<double>(canvas.size().x);

        for (int64_t y = 0; y < static_cast<int64_t>(canvas.size().y); ++y) {
            canvas.setPixel({static_cast<size_t>(x), static_cast<size_t>(y)},
                             ColorUtils::Convert::HSVtoRGB(h, 1.0, 1.0)
                             );
        }
    }

    auto sl = attach<Sh::UIHorizontalSlider<HueSlider>>(
            Sh::Frame{ {0, 0}, frame.size }, 10, color
            );
    sl->slider->applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::Bordered{2, Sh::Color::BLACK},
                    Sh::ColorFill{Sh::Color::WHITE}
                    );
}

/*============================================================================*/

SVPicker::SVPicker(const Sh::Frame& frame, ColorManager::Color* c)
        : Sh::UICanvas(frame, Sh::Color::WHITE)
        , last_hue(c->h)
        , color(c) {

    auto sl = attach<Sh::UIFreeSlider<SVSlider>>(
            Sh::Frame{{0, 0}, frame.size}, Sh::Vector2<double>{10, 10},
            color
            );
    sl->slider->applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::Bordered{2, Sh::Color::BLACK},
                    Sh::ColorFill{Sh::Color::WHITE}
                    );

    update();
}

void SVPicker::onRender() {

    if (color->h != last_hue) {
        last_hue = color->h;
        update();
    }

    Sh::UICanvas::onRender();
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

/*============================================================================*/

ColorPicker::ColorPicker(const Sh::Frame &frame,
                         ColorManager::Color *to_pick)
        : Sh::UIWindow(frame) {

    attach<SVPicker>(
        Sh::Frame{
            {BORDER_SIZE, BORDER_SIZE},
            {frame.size.x - 2 * BORDER_SIZE, frame.size.x - 2 * BORDER_SIZE}
        },
        to_pick
    );

    attach<HuePicker>(
        Sh::Frame{
            {BORDER_SIZE, frame.size.x},
            {frame.size.x - 2 * BORDER_SIZE, frame.size.y - frame.size.x - BORDER_SIZE}
        },
        to_pick
    );

    applyStyle<Sh::UIWindow::NORMAL>(
        Sh::ColorFill{Sh::Color(38, 38, 38)}
    );
}

/*============================================================================*/
