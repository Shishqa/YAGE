/*============================================================================*/
#include "ToolManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

Tool*& ToolManager::tool() {
    static Tool* ACTIVE_TOOL = nullptr;
    return ACTIVE_TOOL;
}

std::list<Tool*>& ToolManager::tools() {
    static std::list<Tool*> TOOLS;
    return TOOLS;
}

void ToolManager::setTool(Tool* new_tool) {
    tool() = new_tool;
}

Tool& ToolManager::activeTool() {
    return *tool();
}

std::list<Tool*>& ToolManager::allTools() {
    return tools();
}

/*============================================================================*/
