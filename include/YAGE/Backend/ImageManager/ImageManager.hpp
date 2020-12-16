/*============================================================================*/
#ifndef SHISHGL_IMAGE_MANAGER_HPP
#define SHISHGL_IMAGE_MANAGER_HPP
/*============================================================================*/
#include <string_view>
#include <string>
#include <vector>
#include <cassert>
#include <list>
#include <climits>

#include "Vector2.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include "RenderSystem.hpp"
#include "EventSystem.hpp"
#include "UIFileSelector.hpp"
/*============================================================================*/
namespace YAGE {

    class LayersUpdateEvent : public Sh::Event {
    public:
        Mask mask() override {
            return Sh::Event::getMask<LayersUpdateEvent>();
        }
    };

    class LayerManager : public Sh::Listener {
    public:

        LayerManager();

        void setActiveLayer(size_t layer);

        Sh::Image& getActiveLayer();

        void addLayer(const Sh::Color& color = Sh::Color::NONE);

        void removeLayer();

        void clearLayers(const Sh::Vector2<size_t>& new_size,
                         const Sh::Color& bg_color);

        size_t numberOfLayers();

        void displayTo(Sh::Image& result);

        size_t activeLayer();

    private:

        using LayerPool = std::list<Sh::Image>;

        LayerPool layers;
        LayerPool::iterator active_layer;

        Sh::Vector2<size_t> image_size;
    };

    /*------------------------------------------------------------------------*/

    class ImageManager : public Sh::Listener {
    public:

        ImageManager() = default;

        /*--------------------------------------------------------------------*/

        void createImage(const Sh::Vector2<size_t>& size);

        void loadImage(const std::string_view& filename);

        bool saveImage();

        void setImagePath(const std::string_view& path) {
            image_path.emplace(path);
        }

        /*--------------------------------------------------------------------*/

        LayerManager& layerManager();

    private:

        LayerManager layer_manager;

        std::optional<std::string> image_path;
    };

}
/*============================================================================*/
#endif //SHISHGL_IMAGE_MANAGER_HPP
/*============================================================================*/
