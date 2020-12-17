/*============================================================================*/
#include "Contrast.hpp"
/*============================================================================*/

extern "C" PluginAPI::Plugin* get_plugin() {
    return PluginAPI::get_instance<Contrast>();
}

/*----------------------------------------------------------------------------*/

bool Contrast::init() {

    properties[PluginAPI::TYPE::CONTRAST].display_type =
        PluginAPI::Property::SLIDER;

    return true;
}

bool Contrast::deinit() { return true; }

/*----------------------------------------------------------------------------*/

uint8_t truncate(double color) {

    if (color > 255) {
        color = 255.0;
    } else if (color < 0) {
        color = 0.0;
    }

    return static_cast<uint8_t>(color);
}

void Contrast::start_apply(PluginAPI::Canvas canvas, PluginAPI::Position) {

    double contrast = properties[PluginAPI::TYPE::CONTRAST].int_value - 50;
    double factor = ( (259.0 / 255.0) * (contrast + 255.0) / (259 - contrast) );

    auto pixels = reinterpret_cast<Color*>(canvas.pixels);

    for (size_t x = 0; x < canvas.width; ++x) {
        for (size_t y = 0; y < canvas.height; ++y) {

            size_t offset = y * canvas.width + x;

            double r = pixels[offset].r;
            double g = pixels[offset].g;
            double b = pixels[offset].b;

            pixels[offset].r = truncate(factor * (r - 128) + 128);
            pixels[offset].g = truncate(factor * (g - 128) + 128);
            pixels[offset].b = truncate(factor * (b - 128) + 128);

        }
    }
}

void Contrast::apply(PluginAPI::Canvas, PluginAPI::Position) {}
void Contrast::stop_apply(PluginAPI::Canvas, PluginAPI::Position) {}

/*============================================================================*/