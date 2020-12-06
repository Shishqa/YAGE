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
/*============================================================================*/
namespace YAGE {

    class ColorManager {
    public:

        struct Color {
            double h, s, v;
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

        explicit ColorPicker(const Sh::Frame& frame, ColorManager::Color* to_pick)
                : Sh::UIWindow(frame) {

            attach<SVPicker>(
                Sh::Frame{
                    {BORDER_SIZE, BORDER_SIZE},
                    {frame.size.x - 2 * BORDER_SIZE, frame.size.x - 2 * BORDER_SIZE}
                },
                to_pick
                );

            attach<HuePicker>(
                Sh::Frame{
                    {BORDER_SIZE, frame.size.x},
                    {frame.size.x - 2 * BORDER_SIZE, frame.size.y - frame.size.x - BORDER_SIZE}
                },
                to_pick
                );

            applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::ColorFill{Sh::Color(38, 38, 38)}
                    );

            //addBehavior<Sh::OneShot>();
        }

        ~ColorPicker() override {
            //removeBehavior<Sh::OneShot>();
        }

    };
//
//    class ColorToolerBehavior : public Sh::Che {
//    public:
//
//        explicit ColorToolerBehavior(Sh::UIWindow* target)
//                : Sh::Clickable(target)
//                , spawned_window(false)
//                { }
//
//        void reactOnRelease(Sh::MouseButtonEvent& event) override {
//
//            /*
//            if (spawned_window) {
//                return;
//            }
//             */
//
//            Sh::Vector2<double> where = event.where() - target<Sh::UIWindow>()->getPos();
//
//            if (where.x + where.y < std::min(
//                    target<Sh::UIWindow>()->getFrame().size.x,
//                    target<Sh::UIWindow>()->getFrame().size.y)) {
//
//                Sh::WindowManager::Root()->attach<ColorPicker>(
//                        Sh::Frame{
//                            target<Sh::UIWindow>()->getPos() +
//                                Sh::Vector2<double>{
//                                    target<Sh::UIWindow>()->getFrame().size.x,
//                                    0
//                                },
//                            {200, 250}
//                        },
//                        &ColorManager::primary
//                );
//
//                spawned_window = true;
//            }
//        }
//
//    private:
//
//        bool spawned_window;
//
//    };


    class ColorPickerSpawner {
    public:

        explicit ColorPickerSpawner(const Sh::Vector2<double>& position)
                : pos(position)
                , spawned_window(nullptr)
                { }

        void on() {

            spawned_window = Sh::WindowManager::Root()->attach<ColorPicker>(
                        Sh::Frame{
                            pos, {200, 250}
                        },
                        &ColorManager::primary
                );
        }

        void off() {

            Sh::WindowManager::destroy(spawned_window);
            spawned_window = nullptr;

        }

    private:

        Sh::Vector2<double> pos;
        Sh::UIWindow* spawned_window;

    };

    class ColorTooler : public Sh::UICanvas {
    public:

        explicit ColorTooler(const Sh::Frame& frame)
                : Sh::UICanvas(frame, Sh::Color::NONE)
                , primary(ColorManager::primary)
                , secondary(ColorManager::secondary) {

            update();
            addBehavior<Sh::CheckboxBehavior<ColorPickerSpawner>>(
                    getPos() + Sh::Vector2<double>{frame.size.x, 0}
                    );
        }

        ~ColorTooler() override {
            removeBehavior<Sh::CheckboxBehavior<ColorPickerSpawner>>();
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
