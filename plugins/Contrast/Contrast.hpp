/*============================================================================*/
#ifndef CONTRAST_HPP
#define CONTRAST_HPP
/*============================================================================*/
#include "api.hpp"
#include <cstdint>
/*============================================================================*/

namespace PluginAPI::TYPE {

    constexpr Type CONTRAST = Type(COUNT);

}

struct Color {
    uint8_t r, g, b, a;
};

class Contrast : public PluginAPI::Plugin {
public:

    Contrast() = default;

    bool init() override;

    bool deinit() override;

    void start_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;

    void apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;

    void stop_apply(PluginAPI::Canvas canvas, PluginAPI::Position pos) override;

};

/*============================================================================*/
#endif //CONTRAST_HPP
/*============================================================================*/