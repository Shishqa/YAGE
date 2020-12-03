/*============================================================================*/
#ifndef SHISHGL_STROKE_PROPERTY_HPP
#define SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
#include <cstddef>

#include "Color.hpp"
#include "UIWindow.hpp"
/*============================================================================*/
namespace YAGE {

    class Stroke {
    public:

        /*--------------------------------------------------------------------*/
        [[nodiscard]]
        const Sh::Color& activeColor() const;

        void setColor(const Sh::Color& new_color);
        /*--------------------------------------------------------------------*/

        /*--------------------------------------------------------------------*/
        [[nodiscard]]
        const size_t& activeThickness() const;

        void setThickness(const size_t& new_thickness);
        /*--------------------------------------------------------------------*/

    private:

        Sh::Color color = Sh::Color::GREEN;

        size_t thickness = 15;

    };

}
/*============================================================================*/
#endif //SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
