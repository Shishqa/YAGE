/*============================================================================*/
#ifndef YAGE_PLUGIN_MANAGER_HPP
#define YAGE_PLUGIN_MANAGER_HPP
/*============================================================================*/

#include <memory>
#include <unordered_set>

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <json.hpp>
#include "api.hpp"

#include "Tool.hpp"
#include "Stroke.hpp"

/*============================================================================*/
namespace YAGE {

    class PluginManager {
    public:

        struct PluginToken {
            PluginAPI::Plugin* impl;
            std::string icon_path;
        };

        static bool initPlugins();

        static bool deinitPlugins();

    private:

        using PluginPool  = std::unordered_map<void*, PluginToken>;

        static PluginPool& Plugins() {
            static PluginPool POOL;
            return POOL;
        }

    };

    class PluginTool : public Tool {
    public:

        explicit PluginTool(PluginManager::PluginToken* plugin)
            : token(plugin) {

            for (auto& prop : token->impl->properties) {

                switch (prop.first) {

                    case PluginAPI::TYPE::PRIMARY_COLOR:
                    case PluginAPI::TYPE::SECONDARY_COLOR:
                        addProperty<Color>(*reinterpret_cast<Sh::Color*>(&prop.second.int_value));
                        break;

                    case PluginAPI::TYPE::THICKNESS:
                        addProperty<Thickness>(prop.second.int_value);
                        break;

                    default:
                        break;
                }
            }

        }

        void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            token->impl->start_apply(
                PluginAPI::Canvas{ img.getData(), img.size().x, img.size().y },
                PluginAPI::Position{ pos.x, pos.y }
                );
        }

        void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            token->impl->apply(
                PluginAPI::Canvas{ img.getData(), img.size().x, img.size().y },
                PluginAPI::Position{ pos.x, pos.y }
            );
        }

        void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) override {
            token->impl->stop_apply(
                PluginAPI::Canvas{ img.getData(), img.size().x, img.size().y },
                PluginAPI::Position{ pos.x, pos.y }
            );
        }

        [[nodiscard]]
        std::string_view getIcon() const override {
            return token->icon_path;
        }

        ~PluginTool() override = default;

    private:

        PluginManager::PluginToken* token;

    };

}
/*============================================================================*/
#endif //YAGE_PLUGIN_MANAGER_HPP
/*============================================================================*/