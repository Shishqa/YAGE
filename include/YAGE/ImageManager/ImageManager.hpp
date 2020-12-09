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
/*============================================================================*/
namespace YAGE {

    class ImageManager {
    public:

        using LayerPool = std::list<Sh::Image>;

        ImageManager() = delete;

        static void loadImage(const std::string_view& filename) {
            delete Image().context;

            Image().filename = filename;
            Image().filename_given = true;

            Image().context = Sh::PLATFORM().loadContextFromImage(filename);
        }

        static void setFilename(const std::string_view& filename) {
            Image().filename = filename;
            Image().filename_given = true;
        }

        static bool saveImage() {

            if (!Image().filename_given) {
                return false;
            }

            Sh::Image result(Layers().begin()->size(), Sh::Color::NONE);
            displayTo(result);

            result.paste(Image().context);
            Sh::PLATFORM().saveContextAsImage(Image().context, Image().filename);

            return true;
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

            Image().filename_given = false;

            delete Image().context;
            Image().context = Sh::PLATFORM().createContext(size, Sh::Color::WHITE);

            Layers().emplace_back(size, Sh::Color::WHITE);
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
            ActiveLayer()++;
            printf("Layers size: %lu\n", Layers().size());
            Layers().emplace(ActiveLayer(), Layers().begin()->size(), Sh::Color::NONE);
            printf("Layers size: %lu\n", Layers().size());
            ActiveLayer()--;
        }

        static void removeLayer() {
            if (Layers().size() == 1) {
                return;
            }
            Layers().erase(ActiveLayer());
            ActiveLayer() = Layers().begin();
        }

        static size_t activeLayer() {
            return std::distance(Layers().begin(), ActiveLayer());
        }

    private:

        struct ImageInfo {
            Sh::IPlatform::IContext* context;
            std::string filename;
            bool filename_given;
        };

        static LayerPool::iterator& ActiveLayer() {
            static auto ACTIVTE_LAYER = Layers().begin();
            return ACTIVTE_LAYER;
        }

        static LayerPool& Layers() {
            static LayerPool LAYERS;
            return LAYERS;
        }

        static ImageInfo& Image() {
            static ImageInfo INFO{ nullptr, "", false };
            return INFO;
        }

    };

}
/*============================================================================*/
#endif //SHISHGL_IMAGE_MANAGER_HPP
/*============================================================================*/
