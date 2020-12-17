/*============================================================================*/
#ifndef YAGE_PROPERTYLIST_HPP
#define YAGE_PROPERTYLIST_HPP
/*============================================================================*/
#include "GUI.hpp"
#include "Styles.hpp"
#include "ColorPicker.hpp"
#include "NumberPickers.hpp"
#include "IProperty.hpp"
#include "SessionManager.hpp"
/*============================================================================*/
namespace YAGE {

    class PropertyList : public Sh::UIFrame {
    public:

        static constexpr double PADDING = 10;

        explicit PropertyList(const Sh::Frame& frame)
                : Sh::UIFrame(frame) {
            update();
            Sh::SubscriptionManager::subscribe<ToolSelectEvent>(this, &TOOL_MANAGER());
        }

        bool onEvent(Sh::Event& event) override {

            if (event.mask() != Sh::Event::getMask<ToolSelectEvent>()) {
                return Sh::UIFrame::onEvent(event);
            }

            update();

            return true;
        }

        void update() {

            destroyChildren();

            double curr_offset = PADDING;
            double width = getSize().x - 2 * PADDING;

            for (auto& prop : TOOL_MANAGER().activeTool().getProperties()) {

                auto picker = prop.second->summonPicker(
                    Sh::Frame{
                        {PADDING, curr_offset},
                        {width, getSize().y - curr_offset}
                    });

                attach(picker);

                curr_offset += picker->getSize().y + PADDING;
            }

            fit();
        }

    };

}
/*============================================================================*/
#endif //YAGE_PROPERTYLIST_HPP
/*============================================================================*/