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
/*============================================================================*/
namespace YAGE {

    class ColorManager {
    public:

        struct Color {
            double h, s, v, a;
        };

        static Color primary;
        static Color secondary;

    };

    /*------------------------------------------------------------------------*/

    class HuePicker : public Sh::UICanvas {
    public:

        explicit HuePicker(const Sh::Frame& frame, ColorManager::Color* color);

    };

    /*------------------------------------------------------------------------*/

    class SVPicker : public Sh::UICanvas {
    public:

        explicit SVPicker(const Sh::Frame& frame, ColorManager::Color* color);

        void onRender() override;

        void update();

    private:

        double last_hue;
        ColorManager::Color* color;

    };

    /*========================================================================*/

    class ColorPicker : public Sh::UIWindow {
    public:

        static constexpr double BORDER_SIZE = 5;

        explicit ColorPicker(const Sh::Frame& frame,
                             ColorManager::Color* to_pick);

    };

    class ColorPickerSpawner : public Sh::ClickSwitchable {
    public:

        explicit ColorPickerSpawner(Sh::UIWindow* target)
                : Sh::ClickSwitchable(target)
                , spawned_window(nullptr)
                { }

        void onSelect() override {

            spawned_window = Sh::WindowManager::Root()->attach<ColorPicker>(
                        Sh::Frame{
                            target<Sh::UIWindow>()->getPos() +
                            Sh::Vector2<double>{target<Sh::UIWindow>()->getSize().x, 0},
                            {200, 250}
                        },
                        &ColorManager::primary
                );
        }

        void onDeselect() override {
            Sh::WindowManager::destroy(spawned_window);
            spawned_window = nullptr;
        }

        void onTargetUpdate() override {
            Sh::WindowManager::destroy(spawned_window);
            spawned_window = nullptr;
        }

    private:

        Sh::UIWindow* spawned_window;

    };

    class ColorTooler : public Sh::UICanvas {
    public:

        explicit ColorTooler(const Sh::Frame& frame)
                : Sh::UICanvas(frame, Sh::Color::NONE)
                , primary(ColorManager::primary)
                , secondary(ColorManager::secondary) {

            update();
            setBehavior<ColorPickerSpawner>();
        }

        void onRender() override {

            if (primary.h != ColorManager::primary.h || // TODO: operator ==
                primary.s != ColorManager::primary.s ||
                primary.v != ColorManager::primary.v ||
                secondary.h != ColorManager::secondary.h ||
                secondary.s != ColorManager::secondary.s ||
                secondary.v != ColorManager::secondary.v) {

                primary = ColorManager::primary;
                secondary = ColorManager::secondary;

                update();
            }

            Sh::UICanvas::onRender();
        }

        void update() {
            for (size_t x = 0; x < canvas.size().x; ++x) {
                for (size_t y = 0; y < canvas.size().y; ++y) {

                    if (x + y < std::min(canvas.size().x, canvas.size().y)) {
                        canvas.setPixel({x, y}, ColorUtils::Convert::HSVtoRGB(
                                primary.h,
                                primary.s,
                                primary.v
                                ));
                    } else {
                        canvas.setPixel({x, y}, ColorUtils::Convert::HSVtoRGB(
                                secondary.h,
                                secondary.s,
                                secondary.v
                        ));
                    }

                }
            }

        }

    private:

        ColorManager::Color primary, secondary;

    };


}
/*============================================================================*/
#endif //SHISHGL_COLOR_PICKER_HPP
/*============================================================================*/
