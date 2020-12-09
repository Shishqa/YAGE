/*============================================================================*/
#include "LayerList.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

LayerSelector::LayerSelector(Sh::UIWindow* target, size_t layer)
        : Sh::Clickable(target)
        , to_set(layer)
        { }

void LayerSelector::reactOnRelease(Sh::MouseButtonEvent&) {
    Sh::EventSystem::sendEvent<LayerSelectEvent>(target<Sh::UIWindow>(), to_set);
}

bool LayerSelector::onEvent(Sh::Event& event) {

    if (event.mask() != Sh::Event::getMask<LayerSelectEvent>()) {
        return false;
    }

    auto layer_select = dynamic_cast<LayerSelectEvent&>(event);

    if (layer_select.layer() == to_set) {
        target<Sh::UIWindow>()->setState(Sh::UIWindow::SELECTED);
    } else {
        target<Sh::UIWindow>()->setState(Sh::UIWindow::NORMAL);
    }

    return true;
}

/*----------------------------------------------------------------------------*/

LayerList::LayerList(const Sh::Frame& frame)
        : Sh::UIFrame(frame, SB_WIDTH)
        , n_layers(ImageManager::getLayers().size()) {
    update();
}

/*----------------------------------------------------------------------------*/

bool LayerList::onEvent(Sh::Event& event) {

    if (event.mask() != Sh::Event::getMask<LayerSelectEvent>()) {
        return false;
    }

    auto layer_select = dynamic_cast<LayerSelectEvent&>(event);
    ImageManager::setActiveLayer(layer_select.layer());

    Sh::EventSystem::sendEvent(this, event);

    return true;
}

/*----------------------------------------------------------------------------*/

void LayerList::onRender() {

    Sh::UIWindow::onRender();

    if (n_layers != ImageManager::getLayers().size()) {
        n_layers = ImageManager::getLayers().size();
        update();
    }
}

/*----------------------------------------------------------------------------*/

void LayerList::update() {

    std::unordered_set<Sh::Window*> to_destroy;
    for (auto& child : getChildren()) {
        if (child != v_scrollbar && child != h_scrollbar) {
            to_destroy.insert(child);
        }
    }
    for (auto& child : to_destroy) {
        Sh::WindowManager::destroy(detach(child));
    }

    for (size_t layer = 0; layer < n_layers; ++layer) {

        auto button = attach<Sh::UILabelButton<LayerSelector>>(
            Sh::Frame{ {0, static_cast<double>(layer) * BUTTON_HEIGHT},
                       {getFrame().size.x, BUTTON_HEIGHT} },
            "layer " + std::to_string(layer), Sh::IPlatform::Align::CENTER,
            layer
            );
        button->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{Sh::Color(120, 120, 120)}
            )
            ->applyStyle<Sh::UIWindow::HOVER>(
                Sh::ColorFill{Sh::Color(200, 200, 200)}
            )
            ->applyStyle<Sh::UIWindow::SELECTED>(
                Sh::ColorFill{Sh::Color(230, 230, 230)}
            );
        button->label->applyStyle<Sh::UIWindow::NORMAL>(
            Sh::Font{"./fonts/FiraCode-Regular.ttf"},
            Sh::FontSize{16},
            Sh::ColorFill{Sh::Color::BLACK}
            );

        Sh::SubscriptionManager::subscribe<LayerSelectEvent>(this, button);
        Sh::SubscriptionManager::subscribe<LayerSelectEvent>(button->as<LayerSelector>(), this);
    }

    Sh::EventSystem::sendEvent<LayerSelectEvent>(this, ImageManager::activeLayer());

    fit();
}

/*============================================================================*/