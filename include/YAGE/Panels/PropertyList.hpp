/*============================================================================*/
#ifndef YAGE_PROPERTYLIST_HPP
#define YAGE_PROPERTYLIST_HPP
/*============================================================================*/
#include "GUI.hpp"
#include "Styles.hpp"
#include "ColorPicker.hpp"
#include "ThicknessPicker.hpp"
#include "IProperty.hpp"
/*============================================================================*/
namespace YAGE {

    class PropertyList : public Sh::UIFrame {
    public:

        explicit PropertyList(const Sh::Frame& frame)
                : Sh::UIFrame(frame) {
            update();
        }

        void update() {

            std::unordered_set<Sh::Window*> to_destroy;
            for (auto& child : getChildren()) {
                if (child != v_scrollbar && child != h_scrollbar) {
                    to_destroy.insert(child);
                }
            }
            for (auto& child : to_destroy) {
                Sh::WindowManager::destroy(detach(child));
            }

            double curr_offset = 0;

            for (auto& prop : TOOL_MANAGER().activeTool().getProperties()) {

                if (prop.first == Property::getId<ColorProp>()) {

                    attach<ColorPicker>(
                        Sh::Frame{ {0, curr_offset}, {getSize().x, 400} },
                        dynamic_cast<ColorProp*>(prop.second)
                        );

                    curr_offset += 400;

                } else if (prop.first == Property::getId<Thickness>()) {

                    auto slider = attach<Sh::UIHorizontalSlider<IntPropPicker>>(
                        Sh::Frame{ {0, curr_offset}, {getSize().x, 30} }, 30,
                        dynamic_cast<Thickness*>(prop.second)
                        );

                    slider->applyStyle<Sh::UIWindow::NORMAL>(
                        Sh::ColorFill{ Sh::Color::MAGENTA }
                        );

                    slider->slider->applyStyle<Sh::UIWindow::NORMAL>(
                        Sh::ColorFill{ Sh::Color::WHITE }
                        );

                    curr_offset += 30;

                }

            }

        }


    };

}
/*============================================================================*/
#endif //YAGE_PROPERTYLIST_HPP
/*============================================================================*/