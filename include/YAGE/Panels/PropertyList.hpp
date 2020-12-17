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

    class GeneralColorPicker : public Sh::UIWindow {
    public:

        explicit GeneralColorPicker(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            attach<Sh::UIWindow>(
                Sh::Frame{{5, 5}, {frame.size.x / 2, 20}}
                )
                ->applyStyle(
                    Sh::StaticLabel("Primary", Sh::Color::WHITE, 14, Sh::Text::Align::LEFT),
                        Sh::UIWindow::ALL
                );

            attach<ColorPicker>(Sh::Frame{
                {0, 25},
                {frame.size.x / 2, frame.size.x / 2 + 20}
            }, &GlobalColorManager::PrimaryColor());

            attach<Sh::UIWindow>(
                Sh::Frame{{frame.size.x / 2 + 5, 5}, {frame.size.x / 2, 20}}
                )
                ->applyStyle(
                    Sh::StaticLabel("Secondary", Sh::Color::WHITE, 14, Sh::Text::Align::LEFT),
                    Sh::UIWindow::ALL
                );

            attach<ColorPicker>(Sh::Frame{
                {frame.size.x / 2, 25},
                {frame.size.x / 2, frame.size.x / 2 + 20}
            }, &GlobalColorManager::SecondaryColor());

            applyStyle(
                Sh::ColorFill(Sh::Color(30, 30, 40)), Sh::UIWindow::ALL
                );

        }
    };

    /*------------------------------------------------------------------------*/

    class PropertyList : public Sh::UIFrame {
    public:

        static constexpr double PADDING = 10;

        explicit PropertyList(const Sh::Frame& frame)
                : Sh::UIFrame(frame) {

            applyStyle(
                Sh::ColorFill(Sh::Color(30, 30, 40)), Sh::UIWindow::ALL
            );

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

            attach<Sh::UIWindow>(Sh::Frame{
                {PADDING, PADDING},
                {width, 20}
            })
            ->applyStyle(
                Sh::StaticLabel("Properties", Sh::Color::GHOST_WHITE, 14, Sh::Text::Align::LEFT),
                    Sh::UIWindow::ALL
                );

            curr_offset += 20 + PADDING;

            for (auto& prop : TOOL_MANAGER().activeTool().getProperties()) {

                if (prop.first == Property::getId<Thickness>()) {

                    attach<Sh::UIWindow>(Sh::Frame{
                        {PADDING, curr_offset},
                        {width, 20}
                    })
                    ->applyStyle(
                        Sh::StaticLabel("Thickness", Sh::Color(150, 150, 150), 15, Sh::Text::Align::LEFT),
                            Sh::UIWindow::ALL
                        );

                    curr_offset += 25;

                }

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