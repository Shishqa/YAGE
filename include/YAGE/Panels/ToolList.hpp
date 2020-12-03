/*============================================================================*/
#ifndef YAGE_TOOL_LIST_HPP
#define YAGE_TOOL_LIST_HPP
/*============================================================================*/
#include "ToolManager.hpp"
#include "UIWindow.hpp"
#include "UIButton.hpp"
#include "Bordered.hpp"
#include "ColorFill.hpp"
#include "TextureFill.hpp"
/*============================================================================*/
namespace YAGE::ToolsPanel {

    class ToolSelector {
    public:

        explicit ToolSelector(Tool* impl)
            : tool(impl)
            { }

        void operator()() {
            ToolManager::setTool(tool);
        }

    private:

        Tool* tool;
    };

    /*------------------------------------------------------------------------*/

    //////////////////////////////////////////////////////////
    static constexpr Sh::Vector2<double> BUTTON_SIZE{40, 40};
    static constexpr double PADDING = 5;
    static constexpr double SPACING = 3;
    static constexpr double TOOL_BORDER = 2;
    static constexpr size_t N_BUTTONS_IN_ROW = 1;
    //////////////////////////////////////////////////////////

    class ToolList : public Sh::UIWindow {
    public:

        explicit ToolList(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            auto curr_tool = ToolManager::allTools().begin();

            for (size_t y = 0; y <= ToolManager::allTools().size() / N_BUTTONS_IN_ROW; ++y) {

                if (curr_tool == ToolManager::allTools().end()) {
                    break;
                }

                for (size_t x = 0; x < N_BUTTONS_IN_ROW; ++x) {

                    if (curr_tool == ToolManager::allTools().end()) {
                        break;
                    }

                    auto db_x = static_cast<double>(x);
                    auto db_y = static_cast<double>(y);

                    attach<Sh::UIButton<ToolSelector>>(
                            Sh::Frame{
                                {PADDING + db_x * BUTTON_SIZE.x + db_x * SPACING,
                                 PADDING + db_y * BUTTON_SIZE.y + db_y * SPACING},
                                BUTTON_SIZE
                                },
                            *curr_tool)
                            ->applyStyle<Sh::UIWindow::NORMAL>(
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::BLACK},
                                    Sh::ColorFill{Sh::Color::WHITE},
                                    Sh::TextureFill{(*curr_tool)->getIcon()}
                            )
                            ->applyStyle<Sh::UIWindow::HOVER>(
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::BEIGE},
                                    Sh::ColorFill{Sh::Color::WHITE},
                                    Sh::TextureFill{(*curr_tool)->getIcon()}
                            )
                            ->applyStyle<Sh::UIWindow::CLICK>(
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::RED},
                                    Sh::ColorFill{Sh::Color::WHITE},
                                    Sh::TextureFill{(*curr_tool)->getIcon()}
                            );

                    ++curr_tool;
                }
            }

        }
    };



}
/*============================================================================*/
#endif //YAGE_TOOL_LIST_HPP
/*============================================================================*/
