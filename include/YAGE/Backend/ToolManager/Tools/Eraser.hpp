/*============================================================================*/
#ifndef SHISHGL_ERASER_HPP
#define SHISHGL_ERASER_HPP
/*============================================================================*/
#include "Pencil.hpp"
/*============================================================================*/
namespace YAGE::Tools {

    class Eraser : public Pencil {
    public:

        Eraser() : Pencil() {
            addProperty<Thickness>(20);
        }

        void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            last_pos = pos;
            draw(img, pos, getProperty<Thickness>().getValue(), Sh::Color::NONE);
        }

        void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            draw(img, pos, getProperty<Thickness>().getValue(), Sh::Color::NONE);
            last_pos = pos;
        }

        void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            //update(img, pos);
        }

        [[nodiscard]]
        std::string_view getIcon() const override {
            return "./textures/tools/019-eraser.png";
        }

    };

}
/*============================================================================*/
#endif //SHISHGL_ERASER_HPP
/*============================================================================*/
