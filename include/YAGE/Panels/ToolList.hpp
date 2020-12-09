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

    class ToolSelectEvent : public Sh::Event {
    public:

        explicit ToolSelectEvent(Tool* impl)
            : impl_to_set(impl)
            { }

        Sh::EventMask mask() override {
            return Sh::Event::getMask<ToolSelectEvent>();
        }

        [[nodiscard]]
        Tool* tool() const {
            return impl_to_set;
        }

        bool happen(Sh::Listener *listener) override {
            return listener->onEvent(*this);
        }

    private:

        Tool* impl_to_set;
    };

    /*------------------------------------------------------------------------*/

    class ToolSelector : public Sh::Clickable {
    public:

        explicit ToolSelector(Sh::UIWindow* target, Tool* impl)
            : Sh::Clickable(target)
            , tool(impl)
            { }

        void reactOnRelease(Sh::MouseButtonEvent& event) override {
            Sh::EventSystem::sendEvent<ToolSelectEvent>(target<Sh::UIWindow>(), tool);
        }

        bool onEvent(Sh::Event& event) override {

            if (event.mask() != Sh::Event::getMask<ToolSelectEvent>()) {
                return false;
            }

            auto tool_select = dynamic_cast<ToolSelectEvent&>(event);

            if (tool_select.tool() == tool) {
                target<Sh::UIWindow>()->setState(Sh::UIWindow::SELECTED);
            } else {
                target<Sh::UIWindow>()->setState(Sh::UIWindow::NORMAL);
            }

            return true;
        }

    private:

        Tool* tool;
    };

    /*------------------------------------------------------------------------*/

    //////////////////////////////////////////////////////////
    static constexpr Sh::Vector2<double> BUTTON_SIZE{42, 42};
    static constexpr double PADDING = 5;
    static constexpr double SPACING = 3;
    static constexpr double TOOL_BORDER = 2;
    static constexpr size_t N_BUTTONS_IN_ROW = 5;
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

                    auto selector = attach<Sh::UIButton<ToolSelector>>(
                            Sh::Frame{
                                {PADDING + db_x * BUTTON_SIZE.x + db_x * SPACING,
                                 PADDING + db_y * BUTTON_SIZE.y + db_y * SPACING},
                                BUTTON_SIZE
                                },
                            *curr_tool);
                    selector->applyStyle<Sh::UIWindow::NORMAL>(
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::BLACK},
                                    Sh::ColorFill{Sh::Color::WHITE},
                                    Sh::TextureFill{(*curr_tool)->getIcon()}
                            )
                            ->applyStyle<Sh::UIWindow::HOVER>(
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::BEIGE},
                                    Sh::ColorFill{Sh::Color::WHITE},
                                    Sh::TextureFill{(*curr_tool)->getIcon()}
                            )
                            ->applyStyle<Sh::UIWindow::SELECTED>(
                                    Sh::Bordered{TOOL_BORDER, Sh::Color::RED},
                                    Sh::ColorFill{Sh::Color::WHITE},
                                    Sh::TextureFill{(*curr_tool)->getIcon()}
                            );

                    ++curr_tool;

                    Sh::SubscriptionManager::subscribe<ToolSelectEvent>(this, selector);
                    Sh::SubscriptionManager::subscribe<ToolSelectEvent>(selector->as<ToolSelector>(), this);
                }
            }

            Sh::EventSystem::sendEvent<ToolSelectEvent>(this, *ToolManager::allTools().begin());
        }

        bool onEvent(Sh::Event& event) override {

            if (event.mask() != Sh::Event::getMask<ToolSelectEvent>()) {
                return false;
            }

            auto tool_select = dynamic_cast<ToolSelectEvent&>(event);

            ToolManager::setTool(tool_select.tool());
            Sh::EventSystem::sendEvent(this, event);

            return true;

        }
    };



}
/*============================================================================*/
#endif //YAGE_TOOL_LIST_HPP
/*============================================================================*/
