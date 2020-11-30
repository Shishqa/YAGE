/*============================================================================*/
#ifndef SHISHGL_TOOL_MANAGER_HPP
#define SHISHGL_TOOL_MANAGER_HPP
/*============================================================================*/
#include "Image.hpp"
#include "Vector2.hpp"
#include "Tool.hpp"
/*============================================================================*/
using namespace ShishGL;
/*============================================================================*/
namespace YAGE {

    class ToolManager {
    public:

        /* TODO: imheritance protection */
        template <typename SomeTool>
        static SomeTool* getImpl() {
            static auto TOOL = new SomeTool();
            return TOOL;
        }

        template <typename SomeTool>
        static void set() {
            tool() = getImpl<SomeTool>();
        }

        static void setTool(Tool* new_tool);

        static Tool& activeTool();

    private:

        static Tool*& tool();

    };

}
/*============================================================================*/
#endif //SHISHGL_TOOL_MANAGER_HPP
/*============================================================================*/