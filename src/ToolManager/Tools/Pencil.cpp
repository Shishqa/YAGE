/*============================================================================*/
#include "Pencil.hpp"
#include "Utils.hpp"
/*============================================================================*/
using namespace YAGE::Tools;
/*============================================================================*/

void Pencil::draw(Sh::Image& img, const Sh::Vector2<int64_t>& pos,
                  int64_t thickness, const Sh::Color& color) const {

    static constexpr int64_t N_POINTS = 50;

    thickness /= 2;

    for (int64_t t = 0; t < N_POINTS; ++t) {

        Sh::Vector2<int64_t> curr_pos =
                last_pos + Sh::Vector2<int64_t>{(pos.x - last_pos.x) * t / N_POINTS,
                                                (pos.y - last_pos.y) * t / N_POINTS};

        int64_t x_l = curr_pos.x - thickness;
        int64_t x_r = curr_pos.x + thickness;
        int64_t y_u = curr_pos.y - thickness;
        int64_t y_d = curr_pos.y + thickness;

        for (int64_t x_c = x_l; x_c < x_r; ++x_c) {
            for (int64_t y_c = y_u; y_c < y_d; ++y_c) {
                if (0 <= x_c && x_c < static_cast<int64_t>(img.size().x) &&
                    0 <= y_c && y_c < static_cast<int64_t>(img.size().y)) {
                    img.setPixel({static_cast<size_t>(x_c),
                                  static_cast<size_t>(y_c)},
                                 color);
                }
            }
        }
    }
}

/*============================================================================*/