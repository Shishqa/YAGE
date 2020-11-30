/*============================================================================*/
#include <cmath>
#include <algorithm>

#include "Convert.hpp"
/*============================================================================*/
using namespace YAGE::ColorUtils::Convert;
/*============================================================================*/

double HSVhelper(double n, double H, double S, double V) {
    double k = fmod(n + 6 * H, 6);
    return (V - V * S * std::max(0.0, std::min({k, 4.0 - k, 1.0})));
}

Color YAGE::ColorUtils::Convert::HSVtoRGB(double H, double S, double V) {

    if (std::isnan(H)) {
        return {0, 0, 0, 255};
    }

    return { static_cast<uint8_t>(HSVhelper(5, H, S, V) * 255),
             static_cast<uint8_t>(HSVhelper(3, H, S, V) * 255),
             static_cast<uint8_t>(HSVhelper(1, H, S, V) * 255),
             255 };


}

/*============================================================================*/
