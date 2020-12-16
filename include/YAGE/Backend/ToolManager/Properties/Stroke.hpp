/*============================================================================*/
#ifndef SHISHGL_STROKE_PROPERTY_HPP
#define SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
#include <cstddef>

#include "Color.hpp"
#include "DefaultProperties.hpp"
/*============================================================================*/
namespace YAGE {

    class GlobalColorManager {
    public:

        GlobalColorManager() = delete;

        static void swap();
        static ColorProp& PrimaryColor();
        static ColorProp& SecondaryColor();

    };

    class Thickness : public IntProp {
    public:

        explicit Thickness(int32_t thickness)
                : IntProp(thickness)
                { }

    };

}
/*============================================================================*/
#endif //SHISHGL_STROKE_PROPERTY_HPP
/*============================================================================*/
