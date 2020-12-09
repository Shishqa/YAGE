/*============================================================================*/
#ifndef YAGE_THICKNESSPICKER_HPP
#define YAGE_THICKNESSPICKER_HPP
/*============================================================================*/
#include "Slidable.hpp"
#include "Stroke.hpp"
#include "ToolManager.hpp"
/*============================================================================*/
namespace YAGE {

    class ThicknessPicker : public Sh::Slidable {
    public:

        static constexpr double DIV = 100;

        ThicknessPicker(Sh::UIWindow* target, const Sh::Frame& frame)
                : Sh::Slidable(target, frame) {

            auto thick = static_cast<double>(
                ToolManager::activeTool().getProperty<Thickness>().value
            );

            set(Sh::Vector2<double>{thick / DIV, 0});
        }

        void onSlide(const Sh::Vector2<double>& pos) override {

            ToolManager::activeTool().getProperty<Thickness>().value =
                static_cast<int64_t>(pos.x * DIV);

        }

    };

}
/*============================================================================*/
#endif //YAGE_THICKNESSPICKER_HPP
/*============================================================================*/