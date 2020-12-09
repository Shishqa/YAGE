/*============================================================================*/
#ifndef YAGE_PROPERTYLIST_HPP
#define YAGE_PROPERTYLIST_HPP
/*============================================================================*/
#include "GUI.hpp"
#include "Styles.hpp"
#include "ColorPicker.hpp"
#include "IProperty.hpp"
/*============================================================================*/
namespace YAGE {

    class PropertyList : public Sh::UIFrame {
    public:

        explicit PropertyList(const Sh::Frame& frame)
                : Sh::UIFrame(frame)
                , for_tool(&ToolManager::activeTool()){

            applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill( Sh::Color::GREY )
                );

            update();
        }

        void onRender() override {

            Sh::UIFrame::onRender();

            if (for_tool != &ToolManager::activeTool()) {
                for_tool = &ToolManager::activeTool();
                update();
            }

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

            double curr_height = 10;
            for (auto& prop : ToolManager::activeTool().getProperties()) {

                if (prop.first == Property::getId<Color>()) {

                    attach<ColorPicker>(Sh::Frame{
                        {10, curr_height},
                        {getSize().x - 20, getSize().x + 10}
                    },
                    &ColorManager::primary
                    );

                    curr_height += getSize().x + 20;

                } else if (prop.first == Property::getId<Thickness>()) {

                    auto win = attach<Sh::UIWindow>(Sh::Frame{
                        {10, curr_height},
                        {getSize().x - 20, 30}
                    });
                    curr_height += 40;

                    win->applyStyle<Sh::UIWindow::NORMAL>(
                        Sh::ColorFill{ Sh::Color::MAGENTA }
                        );
                }
            }

            fit();
        }

    private:

        Tool* for_tool;

    };

}
/*============================================================================*/
#endif //YAGE_PROPERTYLIST_HPP
/*============================================================================*/