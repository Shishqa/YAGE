/*============================================================================*/
#ifndef YAGE_RECTANGLE_HPP
#define YAGE_RECTANGLE_HPP
/*============================================================================*/
#include "Tool.hpp"
#include "Stroke.hpp"
/*============================================================================*/
namespace YAGE::Tools {

    class Rectangle : public Tool {
    public:

        Rectangle() : apply_pos({})
            {}

        void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            apply_pos = pos;
        }

        void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {

            img.fill(Sh::Color::NONE);

            Sh::Vector2<int64_t> from = {std::max(0L, std::min(pos.x, apply_pos.x)),
                                         std::max(0L, std::min(pos.y, apply_pos.y))};

            Sh::Vector2<int64_t> to   = {
                    std::min(static_cast<int64_t>(img.size().x), std::max(pos.x, apply_pos.x)),
                    std::min(static_cast<int64_t>(img.size().y), std::max(pos.y, apply_pos.y))
            };

            for (int64_t x = from.x; x < to.x; ++x) {
                for (int64_t y = from.y; y < to.y; ++y) {

                    img.setPixel(
                        Sh::Vector2<size_t>{
                            static_cast<size_t>(x),
                            static_cast<size_t>(y)
                        },
                        static_cast<Sh::Color>(GlobalColorManager::PrimaryColor())
                    );

                }
            }
        }

        void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
        }

        [[nodiscard]]
        std::string_view getIcon() const override {
            return "./textures/tools/023-foreground.png";
        }

    protected:

        Sh::Vector2<int64_t> apply_pos;

    };


}
/*============================================================================*/
#endif //YAGE_RECTANGLE_HPP
/*============================================================================*/
