/*============================================================================*/
#ifndef YAGE_IPROPERTY_HPP
#define YAGE_IPROPERTY_HPP
/*============================================================================*/
#include <cstdint>
/*============================================================================*/
namespace YAGE {

    class Property {
    public:

        template <typename PropertyType>
        static uint8_t getId() {
            static uint8_t ID = getUniqueId();
            return ID;
        }

        virtual ~Property() = default;

    private:

        static uint8_t getUniqueId();

    };


}
/*============================================================================*/
#endif //YAGE_IPROPERTY_HPP
/*============================================================================*/