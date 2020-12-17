/*============================================================================*/
#include "PluginManager.hpp"
#include "LogSystem.hpp"
#include "GUI.hpp"

#include <cassert>
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

PluginPropContainer::PluginPropContainer(PluginManager::PluginToken* plugin)
        : token(plugin) {

    for (auto& prop : plugin->impl->properties) {

        if (prop.first < PluginAPI::TYPE::THICKNESS) {
            continue;
        }

        switch (prop.second.display_type) {

            case PluginAPI::Property::SLIDER:
                props[prop.first] = new IntProp{prop.second.int_value};
                break;

            case PluginAPI::Property::CHECKBOX:
                props[prop.first] = new BoolProp{prop.second.int_value};
                break;

            case PluginAPI::Property::COLOR_PICKER:
                props[prop.first] =
                    new ColorProp(*reinterpret_cast<Sh::Color*>(&prop.second.int_value));
                break;

            default:
                Sh::LogSystem::printWarning("Unsupported display type");
        }
    }

    setProps();
}

PluginPropContainer::~PluginPropContainer() {
    for (auto& prop : props) {
        delete prop.second;
    }
}

Sh::UIWindow* PluginPropContainer::summonPicker(const Sh::Frame &frame) {

    auto container = Sh::WindowManager::create<Sh::UIFrame>(frame);

    double offset = 0;
    for (auto& prop : props) {

        auto picker = prop.second->summonPicker(
            Sh::Frame{
                {0, offset},
                {frame.size.x, 1000}
            });

        container->attach(picker);

        offset += picker->getSize().y + 5;
    }

    return container;
}

void PluginPropContainer::setProps() {

    for (auto& prop : token->impl->properties) {

        if (PluginAPI::TYPE::PRIMARY_COLOR == prop.first) {
            auto to_set = static_cast<Sh::Color>(GlobalColorManager::PrimaryColor());
            prop.second.int_value = *reinterpret_cast<int32_t*>(&to_set);
            continue;
        }

        if (PluginAPI::TYPE::SECONDARY_COLOR == prop.first) {
            auto to_set = static_cast<Sh::Color>(GlobalColorManager::SecondaryColor());
            prop.second.int_value = *reinterpret_cast<int32_t*>(&to_set);
            continue;
        }

        if (prop.first == PluginAPI::TYPE::PRIMARY_COLOR) {

        }

        if (props[prop.first]->id() == Property::getId<ColorProp>()) {

            auto color = dynamic_cast<ColorProp*>(props[prop.first]);
            assert(color);

            auto to_set = static_cast<Sh::Color>(*color);
            prop.second.int_value = *reinterpret_cast<int32_t*>(&to_set);

        } else if (props[prop.first]->id() == Property::getId<IntProp>() ||
                   props[prop.first]->id() == Property::getId<BoolProp>()) {

            auto integer = dynamic_cast<IntProp*>(props[prop.first]);
            assert(integer);

            prop.second.int_value = integer->getValue();

        } else if (props[prop.first]->id() == Property::getId<FloatingPointProp>()) {

            auto floating = dynamic_cast<FloatingPointProp*>(props[prop.first]);
            assert(floating);

            prop.second.double_value = floating->getValue();

        }

    }
}

void PluginPropContainer::getProps() {

    for (auto& prop : token->impl->properties) {

        if (PluginAPI::TYPE::PRIMARY_COLOR == prop.first) {
            GlobalColorManager::PrimaryColor().setColor(
                *reinterpret_cast<Sh::Color*>(&prop.second.int_value)
            );
            continue;
        }

        if (PluginAPI::TYPE::SECONDARY_COLOR == prop.first) {
            GlobalColorManager::SecondaryColor().setColor(
                *reinterpret_cast<Sh::Color*>(&prop.second.int_value)
            );
            continue;
        }

        if (props[prop.first]->id() == Property::getId<ColorProp>()) {

            auto color = dynamic_cast<ColorProp*>(props[prop.first]);
            color->setColor(*reinterpret_cast<Sh::Color*>(&prop.second.int_value));

        } else if (props[prop.first]->id() == Property::getId<IntProp>() ||
                   props[prop.first]->id() == Property::getId<BoolProp>()) {

            auto integer = dynamic_cast<IntProp*>(props[prop.first]);
            integer->setValue(prop.second.int_value);

        } else if (props[prop.first]->id() == Property::getId<FloatingPointProp>()) {

            auto floating = dynamic_cast<FloatingPointProp*>(props[prop.first]);
            floating->setValue(prop.second.double_value);

        }

    }
}

/*----------------------------------------------------------------------------*/

PluginTool::PluginTool(PluginManager::PluginToken* plugin)
    : token(plugin) {

    addProperty<PluginPropContainer>(plugin);
}

/*----------------------------------------------------------------------------*/

void PluginTool::startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) {
    getProperty<PluginPropContainer>().setProps();
    token->impl->start_apply(
        PluginAPI::Canvas{ img.getData(), img.size().y, img.size().x },
        PluginAPI::Position{ pos.x, pos.y }
    );
}

void PluginTool::update(Sh::Image& img,const Sh::Vector2<int64_t>& pos) {
    token->impl->apply(
        PluginAPI::Canvas{ img.getData(), img.size().y, img.size().x },
        PluginAPI::Position{ pos.x, pos.y }
    );
}

void PluginTool::stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) {
    token->impl->stop_apply(
        PluginAPI::Canvas{ img.getData(), img.size().y, img.size().x },
        PluginAPI::Position{ pos.x, pos.y }
    );
    getProperty<PluginPropContainer>().getProps();
}

std::string_view PluginTool::getIcon() const {
    return token->icon_path;
}

/*============================================================================*/