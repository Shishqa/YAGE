/*============================================================================*/
#ifndef YAGE_PROPERTYLIST_HPP
#define YAGE_PROPERTYLIST_HPP
/*============================================================================*/
#include "GUI.hpp"
#include "Styles.hpp"
#include "ColorPicker.hpp"
/*============================================================================*/
namespace YAGE {

    class PropertyList : public Sh::UIWindow {
    public:

        explicit PropertyList(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill( Sh::Color::WHITE )
                );

            attach<ColorPicker>(Sh::Frame{
                {10, 10},
                {frame.size.x - 20, frame.size.x + 10}
            },
            &ColorManager::primary);

        }

    };

}
/*============================================================================*/
#endif //YAGE_PROPERTYLIST_HPP
/*============================================================================*/