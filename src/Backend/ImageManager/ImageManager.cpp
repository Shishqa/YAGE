/*============================================================================*/
#include "ImageManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

LayerManager::LayerManager()
        : image_size({})
        { }

void LayerManager::setActiveLayer(size_t layer) {
    active_layer = layers.begin();
    std::advance(active_layer, layer);
}

Sh::Image& LayerManager::getActiveLayer() {
    return *active_layer;
}

void LayerManager::displayTo(Sh::Image& result) {
    for (auto& layer : layers) {
        result.blend(layer);
    }
}

void LayerManager::addLayer(const Sh::Color& color) {
    ++active_layer;
    layers.emplace(active_layer, image_size, color);
    --active_layer;
    Sh::EventSystem::sendEvent<LayersUpdateEvent>(this);
}

void LayerManager::removeLayer() {
    if (layers.size() == 1) {
        return;
    }
    layers.erase(active_layer);
    active_layer = --layers.end();
    Sh::EventSystem::sendEvent<LayersUpdateEvent>(this);
}

void LayerManager::clearLayers(const Sh::Vector2<size_t>& new_size,
                               const Sh::Color& bg_color) {
    image_size = new_size;

    layers.clear();
    layers.emplace_back(image_size, bg_color);
    active_layer = layers.begin();
    Sh::EventSystem::sendEvent<LayersUpdateEvent>(this);
}

size_t LayerManager::numberOfLayers() {
    return layers.size();
}

size_t LayerManager::activeLayer() {
    return std::distance(layers.begin(), active_layer);
}

/*----------------------------------------------------------------------------*/

LayerManager& ImageManager::layerManager() {
    return layer_manager;
}

void ImageManager::createImage(const Sh::Vector2<size_t>& size) {

    image_path.reset();

    layerManager().clearLayers(size, Sh::Color::WHITE);
    layerManager().addLayer(Sh::Color::NONE);
    layerManager().setActiveLayer(1);

    Sh::EventSystem::sendEvent<ImageUpdateEvent>(this);
}

void ImageManager::loadImage(const std::string_view& filename) {

    std::cout << "loading image\n";

    image_path.emplace(filename);

    Sh::IPlatform::IContext* context =
        Sh::PLATFORM().loadContextFromImage(filename);

    layerManager().clearLayers(context->getSize(), Sh::Color::BLACK);
    context->paste(layerManager().getActiveLayer());

    delete context;

    Sh::EventSystem::sendEvent<ImageUpdateEvent>(this);
}

bool ImageManager::saveImage() {

    if (!image_path.has_value()) {
        return false;
    }

    Sh::Image result(layerManager().getActiveLayer().size(), Sh::Color::NONE);
    layerManager().displayTo(result);

    auto context = Sh::PLATFORM().createContext(result.size(), Sh::Color::NONE);

    result.paste(context);
    Sh::PLATFORM().saveContextAsImage(context, image_path.value());

    delete context;

    return true;
}

/*============================================================================*/