/*============================================================================*/
#include "LayerList.hpp"
#include "SessionManager.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

LayerList::LayerList(const Sh::Frame& frame)
        : Sh::UISelectList(frame, SB_WIDTH)
        , n_layers(LAYER_MANAGER().numberOfLayers()) {
    Sh::SubscriptionManager::subscribe<LayersUpdateEvent>(this, &LAYER_MANAGER());
}

/*----------------------------------------------------------------------------*/

bool LayerList::onEvent(Sh::Event& event) {

    if (event.mask() != Sh::Event::getMask<LayersUpdateEvent>()) {
        return Sh::UISelectList::onEvent(event);
    }

    update();

    return true;
}

/*----------------------------------------------------------------------------*/

void LayerList::onSelect(int option) {
    LAYER_MANAGER().setActiveLayer(option);
}

/*----------------------------------------------------------------------------*/

void LayerList::update() {

    n_layers = LAYER_MANAGER().numberOfLayers();
    destroyChildren();

    for (size_t layer = 0; layer < n_layers; ++layer) {

        auto button = attach<Sh::UIButton<Sh::Selectable>>(
            Sh::Frame{ {0, static_cast<double>(layer) * BUTTON_HEIGHT},
                       {getFrame().size.x - SB_WIDTH, BUTTON_HEIGHT} },
            layer
            );
        button->applyStyle<Sh::UIWindow::NORMAL>(
                Sh::ColorFill{Sh::Color(120, 120, 120)},
                Sh::StaticLabel{"layer " + std::to_string(layer), Sh::Color::BLACK,
                                16, Sh::Text::Align::LEFT}
            )
            ->applyStyle<Sh::UIWindow::HOVER>(
                Sh::ColorFill{Sh::Color(200, 200, 200)},
                Sh::StaticLabel{"layer " + std::to_string(layer), Sh::Color::BLACK,
                                16, Sh::Text::Align::LEFT}
            )
            ->applyStyle<Sh::UIWindow::SELECTED>(
                Sh::ColorFill{Sh::Color(230, 230, 230)},
                Sh::StaticLabel{"layer " + std::to_string(layer), Sh::Color::BLACK,
                                16, Sh::Text::Align::LEFT}
            );

        Sh::SubscriptionManager::subscribe<Sh::UISelectEvent>(this, button);
        Sh::SubscriptionManager::subscribe<Sh::UISelectEvent>(button->as<Sh::Selectable>(), this);
    }

    Sh::EventSystem::sendEvent<Sh::UISelectEvent>(this, LAYER_MANAGER().activeLayer());

    Sh::UISelectList::update();
}

/*============================================================================*/