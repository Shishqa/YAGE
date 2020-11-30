/*============================================================================*/
#ifndef SHISHGL_STROKE_PROPERTY_HPP
#define SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
#include <cstddef>

#include "Color.hpp"
#include "ColorCollection.hpp"
#include "UIWindow.hpp"
using namespace ShishGL;
/*============================================================================*/
namespace YAGE {

    class Stroke {
    public:

        /*--------------------------------------------------------------------*/
        static constexpr Color DEFAULT_COLOR = COLOR::GREEN;

        [[nodiscard]]
        const Color& activeColor() const;

        void setColor(const Color& new_color);
        /*--------------------------------------------------------------------*/

        /*--------------------------------------------------------------------*/
        static constexpr size_t DEFAULT_THICKNESS = 5;

        [[nodiscard]]
        const size_t& activeThickness() const;

        void setThickness(const size_t& new_thickness);
        /*--------------------------------------------------------------------*/

    private:

        Color color = DEFAULT_COLOR;

        size_t thickness = DEFAULT_THICKNESS;

    };

}
/*============================================================================*/
#endif //SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
