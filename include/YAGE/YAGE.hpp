/*============================================================================*/
#ifndef SHISHGL_YAGE_HPP
#define SHISHGL_YAGE_HPP
/*============================================================================*/
#include "UIWindow.hpp"
#include "ToolList.hpp"
#include "ToolManager.hpp"
#include "Tools.hpp"
#include "MainPanels.hpp"
#include "PluginManager.hpp"
#include "PropertyList.hpp"
/*============================================================================*/
namespace YAGE {

    class KeyboardListener : public Sh::Behavior {
    public:

        explicit KeyboardListener(Sh::UIWindow* target)
                : Sh::Behavior(target) {
            Sh::SubscriptionManager::subscribe<Sh::KeyboardEvent>(
                this, Sh::EventSystem::SystemEvents);
        }

        bool onKeyboard(Sh::KeyboardEvent& event) override {

            if (event.state() == Sh::Keyboard::DOWN) {
                return false;
            }

            if (event.key() == Sh::Keyboard::S &&
                event.modifiers() & Sh::Keyboard::L_CTRL_MOD) {

                return true;
            }

            return false;
        }


    };

    class YageApp : public Sh::UIWindow {
    public:

        explicit YageApp(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            if (!PluginManager::initPlugins()) {
                return;
            }

            ImageManager::createImage({1380, 720});

            ToolManager::allTools().push_back(ToolManager::getImpl<Tools::Pencil>());
            ToolManager::allTools().push_back(ToolManager::getImpl<Tools::Eraser>());
            ToolManager::allTools().push_back(ToolManager::getImpl<Tools::Rectangle>());

            attach<MainPanels::MainMenu>(Sh::Frame{
                {0, 0},
                {frame.size.x, 30}
            });

            attach<ToolsPanel::ToolList>(Sh::Frame{
                {0, 30},
                {250, 200}
            });

            attach<PropertyList>(Sh::Frame{
                {0, 230},
                {250, frame.size.y - 230}
            });

            attach<MainPanels::CanvasFrame>(Sh::Frame{
                {250, 30},
                {frame.size.x - 350, frame.size.y - 30}
            });

            attach<MainPanels::AsidePanel>(Sh::Frame{
                {frame.size.x - 100, 30},
                {100, frame.size.y - 30}
            });

            setBehavior<KeyboardListener>();
        }

        ~YageApp() override {
            PluginManager::deinitPlugins();
        }

    };

}
/*============================================================================*/
#endif //SHISHGL_YAGE_HPP
/*============================================================================*/