/*============================================================================*/
#ifndef YAGE_DROPPER_HPP
#define YAGE_DROPPER_HPP
/*============================================================================*/
#include "Tool.hpp"
/*============================================================================*/
namespace YAGE::Tools {

    class Dropper : public Tool {
    public:

        Dropper() = default;

        void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            pickColor(img, pos);
        }

        void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            pickColor(img, pos);
        }

        void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            //pickColor(img, pos);
        }

        std::string_view getIcon() const override {
            return "./textures/tools/024-eyedropper.png";
        }

    private:

        static void pickColor(Sh::Image &img, const Sh::Vector2<int64_t> &pos) {
            GlobalColorManager::PrimaryColor().setColor(img.getPixel(
                static_cast<Sh::Vector2<size_t>>(pos)
            ));
        }
    };

}
/*============================================================================*/
#endif //YAGE_DROPPER_HPP
/*============================================================================*/