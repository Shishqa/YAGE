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
#include "SessionManager.hpp"
#include "UISelectList.hpp"
/*============================================================================*/
namespace YAGE::ToolsPanel {

    //////////////////////////////////////////////////////////
    static constexpr Sh::Vector2<double> BUTTON_SIZE{42, 42};
    static constexpr double PADDING = 5;
    static constexpr double SPACING = 3;
    static constexpr double TOOL_BORDER = 2;
    static constexpr size_t N_BUTTONS_IN_ROW = 5;
    //////////////////////////////////////////////////////////

    class ToolList : public Sh::UISelectList {
    public:

        explicit ToolList(const Sh::Frame& frame)
                : Sh::UISelectList(frame) {

            uint64_t curr_tool = 0;

            for (size_t y = 0; y <= TOOL_MANAGER().getTools().size() / N_BUTTONS_IN_ROW; ++y) {
                for (size_t x = 0; x < N_BUTTONS_IN_ROW; ++x) {

                    if (curr_tool == TOOL_MANAGER().getTools().size()) {
                        break;
                    }

                    auto db_x = static_cast<double>(x);
                    auto db_y = static_cast<double>(y);

                    auto selector = attach<Sh::UIButton<Sh::Selectable>>(
                            Sh::Frame{
                                {PADDING + db_x * BUTTON_SIZE.x + db_x * SPACING,
                                 PADDING + db_y * BUTTON_SIZE.y + db_y * SPACING},
                                BUTTON_SIZE
                                },
                            curr_tool);
                    selector->applyStyle(
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::BLACK}, Sh::UIWindow::NORMAL,
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::BEIGE}, Sh::UIWindow::HOVER,
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::RED}, Sh::UIWindow::SELECTED,
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::WHITE}, Sh::UIWindow::ALL,
                                    Sh::ColorFill{Sh::Color::WHITE}, Sh::UIWindow::ALL,
                                    Sh::TextureFill{TOOL_MANAGER().getTool(curr_tool).getIcon()}, Sh::UIWindow::ALL
                            );

                    Sh::SubscriptionManager::subscribe<Sh::UISelectEvent>(this, selector);
                    Sh::SubscriptionManager::subscribe<Sh::UISelectEvent>(selector->as<Sh::Selectable>(), this);

                    if (&TOOL_MANAGER().getTool(curr_tool) == &TOOL_MANAGER().activeTool()) {
                        Sh::EventSystem::sendEvent<Sh::UISelectEvent>(this, curr_tool);
                    }

                    ++curr_tool;
                }
            }

        }

        void onSelect(int option) override {

            TOOL_MANAGER().setTool(static_cast<size_t>(option));

        }

    };



}
/*============================================================================*/
#endif //YAGE_TOOL_LIST_HPP
/*============================================================================*/
