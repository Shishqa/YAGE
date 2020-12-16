/*============================================================================*/
#include "ToolManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

void ToolManager::setTool(Tool* new_tool) {
    active_tool = new_tool;
    Sh::EventSystem::sendEvent<ToolSelectEvent>(this, active_tool);
}

Tool& ToolManager::activeTool() {
    return *active_tool;
}

/*============================================================================*/
