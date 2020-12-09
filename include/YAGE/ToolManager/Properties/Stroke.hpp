/*============================================================================*/
#ifndef SHISHGL_STROKE_PROPERTY_HPP
#define SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
#include <cstddef>

#include "Color.hpp"
#include "UIWindow.hpp"
#include "IProperty.hpp"
/*============================================================================*/
namespace YAGE {

    class Color : public Property {
    public:

        explicit Color(const Sh::Color& color)
            : value(color)
            { }

        Sh::Color value;
    };

    class Thickness : public Property {
    public:

        explicit Thickness(int64_t thick)
            : value(thick)
            { }

        int64_t value;
    };

}
/*============================================================================*/
#endif //SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
