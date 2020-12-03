/*============================================================================*/
#ifndef SHISHGL_YAGE_HPP
#define SHISHGL_YAGE_HPP
/*============================================================================*/
#include "UIWindow.hpp"
#include "ToolList.hpp"
#include "ToolManager.hpp"
#include "Tools.hpp"
#include "MainPanels.hpp"
/*============================================================================*/
namespace YAGE {

    class YageApp : public Sh::UIWindow {
    public:

        explicit YageApp(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            ImageManager::createImage({800, 600});

            ToolManager::allTools().push_back(ToolManager::getImpl<Pencil>());
            ToolManager::allTools().push_back(ToolManager::getImpl<Eraser>());
            ToolManager::allTools().push_back(ToolManager::getImpl<Rectangle>());

            attach<MainPanels::Menu>(Sh::Frame{
                {0, 0},
                {frame.size.x, 30}
            });

            attach<MainPanels::ToolingPanel>(Sh::Frame{
                {0, 30},
                {50, frame.size.y - 30}
            });

            attach<MainPanels::CanvasFrame>(Sh::Frame{
                {50, 30},
                {frame.size.x - 200, frame.size.y - 30}
            });

            attach<MainPanels::AsidePanel>(Sh::Frame{
                {frame.size.x - 150, 30},
                {150, frame.size.y - 30}
            });

        }

    };

}
/*============================================================================*/
#endif //SHISHGL_YAGE_HPP
/*============================================================================*/