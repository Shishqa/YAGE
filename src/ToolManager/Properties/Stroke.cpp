/*============================================================================*/
#include "Stroke.hpp"
#include "WindowManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

const Sh::Color& Stroke::activeColor() const {
    return color;
}

void Stroke::setColor(const Sh::Color& new_color) {
    color = new_color;
}

/*============================================================================*/

const size_t& Stroke::activeThickness() const {
    return thickness;
}

void Stroke::setThickness(const size_t& new_thickness) {
    thickness = new_thickness;
}

/*============================================================================*/
