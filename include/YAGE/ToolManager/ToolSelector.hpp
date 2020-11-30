/*============================================================================*/
#ifndef SHISHGL_TOOL_SELECTOR_HPP
#define SHISHGL_TOOL_SELECTOR_HPP
/*============================================================================*/
#include "UIWindow.hpp"
#include "Clickable.hpp"
#include "ToolManager.hpp"
using namespace ShishGL;
/*============================================================================*/
namespace YAGE {

    class ToolSelector : public Clickable {
    public:

        explicit ToolSelector(UIWindow* target, Tool* tool)
            : Clickable(target)
            , impl_to_set(tool)
            { }

    protected:

        void reactOnRelease(MouseButtonEvent&) override {
            ToolManager::setTool(impl_to_set);
        }

    private:

        Tool* impl_to_set;

    };

}
/*============================================================================*/
#endif //SHISHGL_TOOL_SELECTOR_HPP
/*============================================================================*/
