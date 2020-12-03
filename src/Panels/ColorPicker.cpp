/*============================================================================*/
#include "ColorPicker.hpp"
#include "Convert.hpp"
#include "UISlider.hpp"
#include "UISlider2D.hpp"
#include "ColorFill.hpp"
#include "ToolManager.hpp"
#include "Stroke.hpp"
#include "Bordered.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

ColorManager::Color ColorManager::primary   = {0.0, 0.0, 0.0};
ColorManager::Color ColorManager::secondary = {0.0, 0.0, 1.0};

/*============================================================================*/

class HueSelector {
public:

    explicit HueSelector(ColorManager::Color* selectable)
            : color(selectable)
            { }

    void set(const double& value) {

        color->h = value;

        ToolManager::activeTool().property<Stroke>().setColor(
                ColorUtils::Convert::HSVtoRGB(color->h,
                                              color->s,
                                              color->v));
    }

private:

    ColorManager::Color* color;
};

class SVSelector {
public:

    explicit SVSelector(ColorManager::Color* selectable)
            : color(selectable)
            { }

    void set(const Sh::Vector2<double>& value) {

        color->s = value.x;
        color->v = 1 - value.y;

        ToolManager::activeTool().property<Stroke>().setColor(
                ColorUtils::Convert::HSVtoRGB(color->h,
                                              color->s,
                                              color->v));
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

    attach<Sh::UISlider<HueSelector>>(
            Sh::Frame{ {0, 0}, {10, frame.size.y} },
            Sh::Segment2<double>{ {0, 0}, {frame.size.x - 10, 0} },
            color
            )
            ->applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::Bordered{2, Sh::Color::BLACK},
                    Sh::ColorFill{Sh::Color::WHITE}
                    );
}

/*============================================================================*/

SVPicker::SVPicker(const Sh::Frame& frame, ColorManager::Color* c)
        : Sh::UICanvas(frame, Sh::Color::WHITE)
        , last_hue(c->h)
        , color(c) {

    attach<Sh::UISlider2D<SVSelector>>(
            Sh::Frame{{0, 0}, {10, 10}},
            Sh::Frame{{0, 0}, frame.size},
            color
            )
            ->applyStyle<Sh::UIWindow::NORMAL>(
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
