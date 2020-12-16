/*============================================================================*/
#ifndef SHISHGL_COLOR_PICKER_HPP
#define SHISHGL_COLOR_PICKER_HPP
/*============================================================================*/
#include <cmath>
#include <algorithm>

#include "UICanvas.hpp"
#include "Image.hpp"
#include "CircleShape.hpp"
#include "Convert.hpp"
#include "Behaviors.hpp"
#include "Styles.hpp"
#include "GUI.hpp"
#include "ToolManager.hpp"
#include "Stroke.hpp"
#include "ThicknessPicker.hpp"
/*============================================================================*/
namespace YAGE {

    class HueSlider : public PropSlider {
    public:

        explicit HueSlider(Sh::UIWindow* target,
                           const Sh::Frame& frame,
                           ColorProp* to_track);

        void modifyProp(const Sh::Vector2<double> &pos) override;

        void onPropUpdate() override;

    };

    /*------------------------------------------------------------------------*/

    class HuePicker : public Sh::UICanvas {
    public:

        explicit HuePicker(const Sh::Frame& frame, ColorProp* to_track);

    private:

        ColorProp* color;
    };

    /*========================================================================*/

    class SVSlider : public PropSlider {
    public:

        explicit SVSlider(Sh::UIWindow* target,
                          const Sh::Frame& frame,
                          ColorProp* to_track);

        void modifyProp(const Sh::Vector2<double> &pos) override;

        void onPropUpdate() override;

    };

    /*------------------------------------------------------------------------*/

    class SVPicker : public Sh::UICanvas {
    public:

        explicit SVPicker(const Sh::Frame& frame, ColorProp* to_pick);

        void update();

        bool onEvent(Sh::Event& event) override;

    private:

        Sh::UIFreeSlider<SVSlider>* slider;

        ColorProp* color;
    };

    /*========================================================================*/

    class ColorPicker : public Sh::UIWindow {
    public:

        static constexpr double BORDER_SIZE = 5;

        explicit ColorPicker(const Sh::Frame& frame, ColorProp* to_pick);

    };

}
/*============================================================================*/
#endif //SHISHGL_COLOR_PICKER_HPP
/*============================================================================*/
