/*============================================================================*/
#ifndef SHISHGL_PENCIL_HPP
#define SHISHGL_PENCIL_HPP
/*============================================================================*/
#include "Tool.hpp"
#include "ToolManager.hpp"
#include "Stroke.hpp"
/*============================================================================*/
namespace YAGE::Tools {

    class Pencil : public Tool {
    public:

        Pencil() : last_pos({}) {
            addProperty<Thickness>(20);
        }

        void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            last_pos = pos;
            draw(img, pos, getProperty<Thickness>().getValue(),
                 static_cast<Sh::Color>(GlobalColorManager::PrimaryColor()));
        }

        void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            draw(img, pos, getProperty<Thickness>().getValue(),
                 static_cast<Sh::Color>(GlobalColorManager::PrimaryColor()));
            last_pos = pos;
        }

        void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            //update(img, pos);
        }

        [[nodiscard]]
        std::string_view getIcon() const override {
            return "./textures/tools/011-pencil.png";
        }

    protected:

        void draw(Sh::Image& img, const Sh::Vector2<int64_t>& pos,
                  int64_t thickness, const Sh::Color& color) const;

        Sh::Vector2<int64_t> last_pos;

    };

}
/*============================================================================*/
#endif //SHISHGL_PENCIL_HPP
/*============================================================================*/
