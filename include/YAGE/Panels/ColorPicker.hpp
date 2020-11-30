/*============================================================================*/
#ifndef SHISHGL_COLOR_PICKER_HPP
#define SHISHGL_COLOR_PICKER_HPP
/*============================================================================*/
#include <cmath>
#include <algorithm>

#include "UIWindow.hpp"
#include "Image.hpp"
#include "CircleShape.hpp"
using namespace ShishGL;
/*============================================================================*/
namespace YAGE {

    class ColorManager {
    public:

        static double H, S, V;

    };

    class HuePicker : public UIWindow {
    public:

        explicit HuePicker(const Viewport& frame);

        void onRender() override;

    private:

        Image palette;
        IPlatform::IContext* context;

    };

    /*------------------------------------------------------------------------*/

    class SVPicker : public UIWindow {
    public:

        explicit SVPicker(const Viewport& frame);

        void onRender() override;

    private:

        Image palette;
        IPlatform::IContext* context;

    };

}
/*============================================================================*/
#endif //SHISHGL_COLOR_PICKER_HPP
/*============================================================================*/
