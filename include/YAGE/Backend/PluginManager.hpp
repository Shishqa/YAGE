/*============================================================================*/
#ifndef YAGE_PLUGIN_MANAGER_HPP
#define YAGE_PLUGIN_MANAGER_HPP
/*============================================================================*/

#include <memory>
#include <unordered_set>

#include <iostream>
#include <iomanip>
#include <cstdio>
#include "api.hpp"

#include "Tool.hpp"
#include "Stroke.hpp"

/*============================================================================*/
namespace YAGE {

    class PluginManager {
    public:

        using PluginHandle = void*;
        using Plugin = PluginAPI::Plugin;

        struct PluginToken {
            Plugin* impl;
            std::string icon_path;
        };

        static bool initPlugins();

        static bool finalizePlugins();

    private:

        using PluginPool = std::unordered_map<PluginHandle, PluginToken*>;

        static PluginPool& Plugins() {
            static PluginPool POOL;
            return POOL;
        }

    };

    /*------------------------------------------------------------------------*/

    class PluginPropContainer : public Property {
    public:

        explicit PluginPropContainer(PluginManager::PluginToken* plugin);

        Sh::UIWindow* summonPicker(const Sh::Frame &frame) override;

        ~PluginPropContainer() override;

        uint8_t id() override {
            return getId<PluginPropContainer>();
        }

        void getProps();

        void setProps();

        std::unordered_map<PluginAPI::TYPE::Type, Property*> props;

    private:

        PluginManager::PluginToken* token;
    };

    class PluginTool : public Tool {
    public:

        explicit PluginTool(PluginManager::PluginToken* plugin);

        void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override;

        void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override;

        void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override;

        [[nodiscard]]
        std::string_view getIcon() const override;

        ~PluginTool() override = default;

    private:

        PluginManager::PluginToken* token;
    };

}
/*============================================================================*/
#endif //YAGE_PLUGIN_MANAGER_HPP
/*============================================================================*/