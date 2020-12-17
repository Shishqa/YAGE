/*============================================================================*/
#ifndef YAGE_DEFAULTPROPERTIES_HPP
#define YAGE_DEFAULTPROPERTIES_HPP
/*============================================================================*/
#include "IProperty.hpp"
#include "Color.hpp"
#include "Convert.hpp"

#include <algorithm>
#include <cmath>
/*============================================================================*/
namespace YAGE {

    class ColorProp : public Property {
    public:

        explicit ColorProp(const Sh::Color& color)
                : h(0), s(0), v(0), a(1) {
            setColor(color);
        }

        void setColor(const Sh::Color& color) {

            a = static_cast<double>(color.a) / 255;

            double r = static_cast<double>(color.r) / 255;
            double g = static_cast<double>(color.g) / 255;
            double b = static_cast<double>(color.b) / 255;

            double c_max = std::max({r, g, b});
            double c_min = std::min({r, g, b});
            double delta = c_max - c_min;

            v = c_max;

            if (delta == 0) {
                h = 0;
            } else if (c_max == r) {
                h = std::fmod((g - b) / delta, 6) / 6;
            } else if (c_max == g) {
                h = ((b - r) / delta + 2) / 6;
            } else {
                h = ((r - g) / delta + 4) / 6;
            }

            if (c_max == 0) {
                s = 0;
            } else {
                s = delta / c_max;
            }

            Sh::EventSystem::sendEvent<PropUpdateEvent>(this, this);
        }

        explicit operator Sh::Color() const {
            Sh::Color output = ColorUtils::Convert::HSVtoRGB(h, s, v);
            output.a = static_cast<uint8_t>(a * 255);
            return output;
        }

        Sh::UIWindow* summonPicker(const Sh::Frame& frame) override;

        uint8_t id() override {
            return getId<ColorProp>();
        }

        double h, s, v, a;

    };

    class FloatingPointProp : public Property {
    public:

        explicit FloatingPointProp(double val)
                : value(0) {
            setValue(val);
        }

        [[nodiscard]]
        double getValue() const {
            return value;
        }

        void setValue(double new_value) {
            value = new_value;
            Sh::EventSystem::sendEvent<PropUpdateEvent>(this, this);
        }

        Sh::UIWindow* summonPicker(const Sh::Frame& frame) override;

        uint8_t id() override {
            return getId<FloatingPointProp>();
        }

    private:

        double value;

    };

    class IntProp : public Property {
    public:

        explicit IntProp(int32_t val)
                : value(0) {
            setValue(val);
        }

        [[nodiscard]]
        int32_t getValue() const {
            return value;
        }

        void setValue(int32_t new_value) {
            value = new_value;
            Sh::EventSystem::sendEvent<PropUpdateEvent>(this, this);
        }

        Sh::UIWindow* summonPicker(const Sh::Frame& frame) override;

        uint8_t id() override {
            return getId<IntProp>();
        }

    private:

        int32_t value;
    };

    class BoolProp : public IntProp {
    public:

        explicit BoolProp(int32_t val)
                : IntProp(val)
                { }

        uint8_t id() override {
            return getId<BoolProp>();
        }

        Sh::UIWindow* summonPicker(const Sh::Frame& frame) override;
    };

}
/*============================================================================*/
#endif //YAGE_DEFAULTPROPERTIES_HPP
/*============================================================================*/