/*============================================================================*/
#ifndef SHISHGL_TOOL_MANAGER_HPP
#define SHISHGL_TOOL_MANAGER_HPP
/*============================================================================*/
#include <vector>

#include "Image.hpp"
#include "Vector2.hpp"
#include "Tool.hpp"
#include "EventSystem.hpp"
/*============================================================================*/
namespace YAGE {

    class ToolSelectEvent : public Sh::Event {
    public:

        explicit ToolSelectEvent(Tool* selected)
                : tool(selected)
                { }

        Mask mask() override {
            return Sh::Event::getMask<ToolSelectEvent>();
        }

        [[nodiscard]]
        Tool* selected() const {
            return tool;
        }

    private:

        Tool* tool;
    };

    class ToolManager : public Sh::Listener {
    public:

        ToolManager() : active_tool(nullptr) {};

        template <typename SomeTool, typename... Args>
        void addTool(Args&&... args) {
            tools.push_back(new SomeTool(std::forward<Args>(args)...));
        }

        void setTool(Tool* active_tool);

        void setTool(size_t number) {
            setTool(tools[number]);
        }

        Tool& activeTool();

        Tool& getTool(size_t number) {
            return *tools[number];
        }

        [[nodiscard]]
        const std::vector<Tool*>& getTools() const {
            return tools;
        }

        ~ToolManager() override {
            for (auto& tool : tools) {
                delete tool;
            }
        }

    private:

        Tool* active_tool;

        std::vector<Tool*> tools;

        friend class SessionManager;

    };

}
/*============================================================================*/
#endif //SHISHGL_TOOL_MANAGER_HPP
/*============================================================================*/