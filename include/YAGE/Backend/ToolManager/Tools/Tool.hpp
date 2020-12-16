/*============================================================================*/
#ifndef SHISHGL_TOOL_HPP
#define SHISHGL_TOOL_HPP
/*============================================================================*/
#include "Image.hpp"
#include "Vector2.hpp"
#include "IProperty.hpp"
/*============================================================================*/
namespace YAGE {

    class Tool {
    public:

        explicit Tool(bool on_new_layer = false)
                : need_layer(on_new_layer)
                { }

        using PropertyMap = std::unordered_map<uint8_t, Property*>;

        [[nodiscard]]
        bool needLayer() const {
            return need_layer;
        }

        virtual void startApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) = 0;

        virtual void update(Sh::Image& img, const Sh::Vector2<int64_t>& pos) = 0;

        virtual void stopApplying(Sh::Image& img, const Sh::Vector2<int64_t>& pos) = 0;

        template <typename SomeProperty, typename... Args>
        SomeProperty* addProperty(Args&&... args) {

            if (properties.count(Property::getId<SomeProperty>())) {
                delete properties[Property::getId<SomeProperty>()];
            }

            auto prop = new SomeProperty(std::forward<Args>(args)...);

            properties[Property::getId<SomeProperty>()] = prop;

            return prop;
        }

        template <typename SomeProperty>
        SomeProperty& getProperty() {
            return *dynamic_cast<SomeProperty*>(properties.at(Property::getId<SomeProperty>()));
        }

        [[nodiscard]]
        virtual std::string_view getIcon() const = 0;

        const PropertyMap& getProperties() {
            return properties;
        }

        virtual ~Tool() {
            for (auto& property : properties) {
                delete property.second;
            }
        }

    protected:
        
        std::unordered_map<uint8_t, Property*> properties;

        friend class ToolManager;

    private:

        bool need_layer;
    };

}
/*============================================================================*/
#endif //SHISHGL_TOOL_HPP
/*============================================================================*/
