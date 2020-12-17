/*============================================================================*/
#ifndef YAGE_IPROPERTY_HPP
#define YAGE_IPROPERTY_HPP
/*============================================================================*/
#include <cstdint>
#include "UIWindow.hpp"
#include "EventSystem.hpp"
/*============================================================================*/
namespace YAGE {

    class Property : public Sh::Listener {
    public:

        template <typename PropertyType>
        static uint8_t getId() {
            static uint8_t ID = getUniqueId();
            return ID;
        }

        virtual uint8_t id() = 0;

        virtual Sh::UIWindow* summonPicker(const Sh::Frame& frame) = 0;

        ~Property() override = default;

    private:

        static uint8_t getUniqueId();

    };

    /*------------------------------------------------------------------------*/

    class PropUpdateEvent : public Sh::Event {
    public:

        explicit PropUpdateEvent(Property* updated)
            : prop(updated)
        { }

        Mask mask() override {
            return Sh::Event::getMask<PropUpdateEvent>();
        }

        [[nodiscard]]
        Property* updated() const {
            return prop;
        }

    private:

        Property* prop;
    };

}
/*============================================================================*/
#endif //YAGE_IPROPERTY_HPP
/*============================================================================*/