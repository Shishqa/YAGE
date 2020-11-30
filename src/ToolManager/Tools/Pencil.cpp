/*============================================================================*/
#include "Pencil.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

void Pencil::draw(Image& img, const Vector2<int64_t>& pos,
                  size_t thickness, const Color& color) {

    thickness /= 2;

    int64_t x_l = pos.x - static_cast<int64_t>(thickness);
    int64_t x_r = pos.x + static_cast<int64_t>(thickness);
    int64_t y_u = pos.y - static_cast<int64_t>(thickness);
    int64_t y_d = pos.y + static_cast<int64_t>(thickness);

    for (int64_t x = x_l; x < x_r; ++x) {
        for (int64_t y = y_u; y < y_d; ++y) {
            if (0 <= x && x < static_cast<int64_t>(img.size().x) &&
                0 <= y && y < static_cast<int64_t>(img.size().y)) {
                img.setPixel({static_cast<size_t>(x),
                              static_cast<size_t>(y)},
                             color);
            }
        }
    }
}

/*============================================================================*/