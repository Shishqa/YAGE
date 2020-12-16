/*============================================================================*/
#include "PluginManager.hpp"
#include "LogSystem.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

PluginTool::PluginTool(PluginManager::PluginToken* plugin)
    : token(plugin) {

    addProperty<PluginPropContainer>();

    for (auto& prop : token->impl->properties) {

        switch (prop.first) {

            case PluginAPI::TYPE::THICKNESS:
                addProperty<Thickness>(prop.second.int_value);
                break;

            default: {

                switch (prop.second.display_type) {

                    case PluginAPI::Property::SLIDER:
                        getProperty<PluginPropContainer>().props[prop.first] =
                            new FloatingPointProp{prop.second.double_value};
                        break;

                    case PluginAPI::Property::CHECKBOX:
                        getProperty<PluginPropContainer>().props[prop.first] =
                            new BoolProp{prop.second.int_value};
                        break;

                    case PluginAPI::Property::COLOR_PICKER:
                        getProperty<PluginPropContainer>().props[prop.first] =
                            new ColorProp(*reinterpret_cast<Sh::Color*>(&prop.second.int_value));
                        break;

                    default:
                        Sh::LogSystem::printWarning("Unsupported display type");
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------*/

void PluginTool::startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) {
    setProps();
    token->impl->start_apply(
        PluginAPI::Canvas{ img.getData(), img.size().x, img.size().y },
        PluginAPI::Position{ pos.x, pos.y }
    );
}

void PluginTool::update(Sh::Image& img,const Sh::Vector2<int64_t>& pos) {
    token->impl->apply(
        PluginAPI::Canvas{ img.getData(), img.size().x, img.size().y },
        PluginAPI::Position{ pos.x, pos.y }
    );
}

void PluginTool::stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) {
    token->impl->stop_apply(
        PluginAPI::Canvas{ img.getData(), img.size().x, img.size().y },
        PluginAPI::Position{ pos.x, pos.y }
    );
    getProps();
}

/*----------------------------------------------------------------------------*/

/* TODO: REFACTOR COPY-PASTE SOMEHOW */

void PluginTool::setProps() {

    for (auto& prop : token->impl->properties) {

        switch (prop.first) {

            case PluginAPI::TYPE::PRIMARY_COLOR: {
                auto to_set = static_cast<Sh::Color>(GlobalColorManager::PrimaryColor());
                prop.second.int_value = *reinterpret_cast<int32_t*>(&to_set);
                break;
            }

            case PluginAPI::TYPE::SECONDARY_COLOR: {
                auto to_set = static_cast<Sh::Color>(GlobalColorManager::SecondaryColor());
                prop.second.int_value = *reinterpret_cast<int32_t*>(&to_set);
                break;
            }

            case PluginAPI::TYPE::THICKNESS:
                prop.second.int_value = getProperty<Thickness>().getValue();
                break;

            default: {

                switch (prop.second.display_type) {

                    case PluginAPI::Property::SLIDER: {
                        auto floating = dynamic_cast<FloatingPointProp*>(
                            getProperty<PluginPropContainer>().props[prop.first]
                            );

                        prop.second.double_value = floating->getValue();
                        break;
                    }

                    case PluginAPI::Property::CHECKBOX: {
                        auto integer = dynamic_cast<BoolProp*>(
                            getProperty<PluginPropContainer>().props[prop.first]
                            );

                        prop.second.int_value = integer->getValue();
                        break;
                    }

                    case PluginAPI::Property::COLOR_PICKER: {
                        auto color = dynamic_cast<ColorProp*>(
                            getProperty<PluginPropContainer>().props[prop.first]
                            );

                        auto to_set = static_cast<Sh::Color>(*color);
                        prop.second.int_value = *reinterpret_cast<int32_t*>(&to_set);
                        break;
                    }

                    default:
                        Sh::LogSystem::printWarning("Plugin has unsupported display type");
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------*/

void PluginTool::getProps() {

    for (auto& prop : token->impl->properties) {

        switch (prop.first) {

            case PluginAPI::TYPE::PRIMARY_COLOR: {
                GlobalColorManager::PrimaryColor().setColor(
                    *reinterpret_cast<Sh::Color*>(&prop.second.int_value)
                    );
                break;
            }

            case PluginAPI::TYPE::SECONDARY_COLOR: {
                GlobalColorManager::SecondaryColor().setColor(
                    *reinterpret_cast<Sh::Color*>(&prop.second.int_value)
                );
                break;
            }

            case PluginAPI::TYPE::THICKNESS:
                getProperty<Thickness>().setValue(prop.second.int_value);
                break;

            default: {

                switch (prop.second.display_type) {

                    case PluginAPI::Property::SLIDER: {
                        auto floating = dynamic_cast<FloatingPointProp*>(
                            getProperty<PluginPropContainer>().props[prop.first]
                        );

                        floating->setValue(prop.second.double_value);
                        break;
                    }

                    case PluginAPI::Property::CHECKBOX: {
                        auto integer = dynamic_cast<BoolProp*>(
                            getProperty<PluginPropContainer>().props[prop.first]
                        );

                        integer->setValue(prop.second.int_value);
                        break;
                    }

                    case PluginAPI::Property::COLOR_PICKER: {
                        auto color = dynamic_cast<ColorProp*>(
                            getProperty<PluginPropContainer>().props[prop.first]
                        );
                        color->setColor(*reinterpret_cast<Sh::Color*>(&prop.second.int_value));
                        break;
                    }

                    default:
                        Sh::LogSystem::printWarning("Unsupported display type");

                }
            }
        }
    }
}

/*----------------------------------------------------------------------------*/

std::string_view PluginTool::getIcon() const {
    return token->icon_path;
}

/*============================================================================*/