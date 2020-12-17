/*============================================================================*/
#ifndef CONTRAST_HPP
#define CONTRAST_HPP
/*============================================================================*/
#include "api.hpp"
#include <cstdint>
/*============================================================================*/

namespace PluginAPI::TYPE {

    constexpr Type RADIUS    = Type(COUNT + 0);
    constexpr Type AMOUNT    = Type(COUNT + 1);
    constexpr Type THRESHOLD = Type(COUNT + 2);

}

struct Color {
    uint8_t r, g, b, a;
};

class UnsharpMask : public PluginAPI::Plugin {
public:

    UnsharpMask() = default;

    bool init() override;

    bool deinit() override;

    void start_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;

    void apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;

    void stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;

};

/*============================================================================*/
#endif //CONTRAST_HPP
/*============================================================================*/