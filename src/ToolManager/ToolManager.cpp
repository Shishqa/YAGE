/*============================================================================*/
#include "ToolManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

Tool*& ToolManager::tool() {
    static Tool* ACTIVE_TOOL = nullptr;
    return ACTIVE_TOOL;
}

void ToolManager::setTool(Tool* new_tool) {
    tool() = new_tool;
}

Tool& ToolManager::activeTool() {
    return *tool();
}

/*============================================================================*/
