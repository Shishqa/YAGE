/*============================================================================*/
#ifndef SHISHGL_TOOL_HPP
#define SHISHGL_TOOL_HPP
/*============================================================================*/
#include "Image.hpp"
#include "Vector2.hpp"
/*============================================================================*/
namespace YAGE {

    class Tool {
    public:

        virtual void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) = 0;

        virtual void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) = 0;

        virtual void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) = 0;

        template <typename SomeProperty>
        SomeProperty& property() {
            static SomeProperty PROPERTY;
            return PROPERTY;
        }

        [[nodiscard]]
        virtual std::string_view getIcon() const = 0;

        virtual ~Tool() = default;

    protected:

        Tool() = default;

        friend class ToolManager;

    };

}
/*============================================================================*/
#endif //SHISHGL_TOOL_HPP
/*============================================================================*/
