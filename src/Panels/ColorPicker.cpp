/*============================================================================*/
#include "ColorPicker.hpp"
#include "Convert.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

double ColorManager::H = 0.8;
double ColorManager::S = 1.0;
double ColorManager::V = 1.0;

/*============================================================================*/

YAGE::HuePicker::HuePicker(const Viewport& frame)
        : UIWindow(frame)
        , palette(static_cast<Vector2<size_t>>(frame.size), COLOR::NONE) {

    context = RENDERER().createContext(palette.size(), COLOR::NONE);

    for (int64_t x = 0; x < static_cast<int64_t>(palette.size().x); ++x) {

        double h = static_cast<double>(x) / static_cast<double>(palette.size().x);

        for (int64_t y = 0; y < static_cast<int64_t>(palette.size().y); ++y) {

            palette.setPixel({static_cast<size_t>(x), static_cast<size_t>(y)},
                             ColorUtils::Convert::HSVtoRGB(h, ColorManager::S, ColorManager::V)
                             );
        }
    }
}

void HuePicker::onRender() {
    palette.paste(context);
    RENDERER().displayContext(context, getPos());
}

/*============================================================================*/

SVPicker::SVPicker(const Viewport& frame)
        : UIWindow(frame)
        , palette(static_cast<Vector2<size_t>>(frame.size), COLOR::NONE) {

    context = RENDERER().createContext(palette.size(), COLOR::NONE);

    for (int64_t x = 0; x < static_cast<int64_t>(palette.size().x); ++x) {

        double S = static_cast<double>(x) / static_cast<double>(palette.size().x);

        for (int64_t y = 0; y < static_cast<int64_t>(palette.size().y); ++y) {

            double V = 1 - static_cast<double>(y) / static_cast<double>(palette.size().y);

            palette.setPixel({static_cast<size_t>(x), static_cast<size_t>(y)},
                             ColorUtils::Convert::HSVtoRGB(ColorManager::H, S, V)
            );
        }
    }
}

void SVPicker::onRender() {
    palette.paste(context);
    RENDERER().displayContext(context, getPos());
}

/*============================================================================*/
