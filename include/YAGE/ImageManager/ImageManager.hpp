/*============================================================================*/
#ifndef SHISHGL_IMAGE_MANAGER_HPP
#define SHISHGL_IMAGE_MANAGER_HPP
/*============================================================================*/
#include <string_view>
#include <vector>
#include <cassert>
#include <list>

#include "Vector2.hpp"
#include "Color.hpp"
#include "Image.hpp"
/*============================================================================*/
namespace YAGE {

    class ImageManager {
    public:

        using LayerPool = std::list<Sh::Image>;

        ImageManager() = delete;

        static void loadImage(const std::string_view& filename) {
            delete ImageContext();
            ImageContext() = Sh::PLATFORM().loadContextFromImage(filename);
        }

        static void saveImage(const std::string_view& filename) {

            Sh::Image result(Layers().begin()->size(), Sh::Color::NONE);
            displayTo(result);

            result.paste(ImageContext());
            Sh::PLATFORM().saveContextAsImage(ImageContext(), filename);
        }

        static void setActiveLayer(size_t layer) {
            ActiveLayer() = Layers().begin();
            std::advance(ActiveLayer(), layer);
        }

        static const LayerPool& getLayers() {
            return Layers();
        }

        static Sh::Image& getActiveLayer() {
            return *ActiveLayer();
        };

        static void createImage(const Sh::Vector2<size_t>& size) {

            delete ImageContext();
            ImageContext() = Sh::PLATFORM().createContext(size, Sh::Color::WHITE);

            Layers().emplace_back(size, Sh::Color::WHITE);
            Layers().emplace_back(size, Sh::Color::NONE);
            Layers().emplace_back(size, Sh::Color::NONE);
            Layers().emplace_back(size, Sh::Color::NONE);
            ActiveLayer() = Layers().end();
            ActiveLayer()--;
        }

        static void displayTo(Sh::Image& result) {
            for (auto& layer : Layers()) {
                result.blend(layer);
            }
        }

        static void addLayer() {
            Layers().emplace_back(Layers().begin()->size(), Sh::Color::NONE);
        }

    private:


        static LayerPool::iterator& ActiveLayer() {
            static auto ACTIVTE_LAYER = Layers().begin();
            return ACTIVTE_LAYER;
        }

        static LayerPool& Layers() {
            static LayerPool LAYERS;
            return LAYERS;
        }

        static Sh::IPlatform::IContext*& ImageContext() {
            static Sh::IPlatform::IContext* CONTEXT;
            return CONTEXT;
        }

    };

}
/*============================================================================*/
#endif //SHISHGL_IMAGE_MANAGER_HPP
/*============================================================================*/
