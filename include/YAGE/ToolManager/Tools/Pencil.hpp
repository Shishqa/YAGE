/*============================================================================*/
#ifndef SHISHGL_PENCIL_HPP
#define SHISHGL_PENCIL_HPP
/*============================================================================*/
#include "Tool.hpp"
#include "ToolManager.hpp"
#include "Stroke.hpp"
/*============================================================================*/
namespace YAGE {

    class Pencil : public Tool {
    public:

        Pencil() : last_pos({})
        { }

        void startApplying(Image& img, const Vector2<int64_t>& pos) override {
            last_pos = pos;
            draw(img, pos, property<Stroke>().activeThickness(),
                 property<Stroke>().activeColor());
        }

        void update(Image& img, const Vector2<int64_t>& pos) override {
            draw(img, pos, property<Stroke>().activeThickness(),
                 property<Stroke>().activeColor());
            last_pos = pos;
        }

        void stopApplying(Image& img, const Vector2<int64_t>& pos) override {
            update(img, pos);
        }

        [[nodiscard]]
        std::string_view getIcon() const override {
            return "./textures/tools/011-pencil.png";
        }

    protected:

        static void draw(Image& img, const Vector2<int64_t>& pos,
                         size_t thickness, const Color& color);

        Vector2<int64_t> last_pos;

    };

}
/*============================================================================*/
#endif //SHISHGL_PENCIL_HPP
/*============================================================================*/
