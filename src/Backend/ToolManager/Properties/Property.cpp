/*============================================================================*/
#include <stdexcept>

#include "IProperty.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

uint8_t Property::getUniqueId() {

    static constexpr uint8_t ID_LIMIT = 250;
    static uint8_t ID = 1;

    if (ID == ID_LIMIT) {
        throw std::runtime_error("reached limit of property types");
    }

    return ID++;
}


/*============================================================================*/
