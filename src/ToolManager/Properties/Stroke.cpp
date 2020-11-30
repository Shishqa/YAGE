/*============================================================================*/
#include "Stroke.hpp"
#include "ColorCollection.hpp"
#include "WindowManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

const Color& Stroke::activeColor() const {
    return color;
}

void Stroke::setColor(const Color& new_color) {
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
