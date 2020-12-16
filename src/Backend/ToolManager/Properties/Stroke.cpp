/*============================================================================*/
#include "Stroke.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

ColorProp& GlobalColorManager::PrimaryColor() {
    static ColorProp PRIMARY(Sh::Color::BLACK);
    return PRIMARY;
}

ColorProp& GlobalColorManager::SecondaryColor() {
    static ColorProp SECONDARY(Sh::Color::WHITE);
    return SECONDARY;
}

void GlobalColorManager::swap() {
    std::swap(PrimaryColor(), SecondaryColor());
}

/*============================================================================*/
