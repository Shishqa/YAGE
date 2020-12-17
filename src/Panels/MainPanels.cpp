/*============================================================================*/
#include "MainPanels.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

MainPanels::ImageOpener::ImageOpener(Sh::UIWindow *target)
    : Sh::Clickable(target)
    { }

void MainPanels::ImageOpener::reactOnRelease(Sh::MouseButtonEvent&) {

    auto selector = Sh::SPAWN_DIALOG<Sh::UIFileSelector>(
        Sh::Frame{ {30, 30}, {800, 600} },
        "Open", "./"
        );

    Sh::SubscriptionManager::subscribe<Sh::FileSelectEvent>(this, selector);
}

bool MainPanels::ImageOpener::onEvent(Sh::Event& event) {

    if (event.mask() != Sh::Event::getMask<Sh::FileSelectEvent>()) {
        return false;
    }

    auto file_select = dynamic_cast<Sh::FileSelectEvent&>(event);

    IMAGE_MANAGER().loadImage(file_select.file());

    return true;
}

/*----------------------------------------------------------------------------*/

MainPanels::ImageSaver::ImageSaver(Sh::UIWindow *target)
        : Sh::Clickable(target)
        { }

void MainPanels::ImageSaver::reactOnRelease(Sh::MouseButtonEvent&) {

    if (IMAGE_MANAGER().saveImage()) {
        return;
    }

    auto selector = Sh::SPAWN_DIALOG<Sh::UIFileSelector>(
        Sh::Frame{ {30, 30}, {800, 600} },
        "Save", "./"
    );

    Sh::SubscriptionManager::subscribe<Sh::FileSelectEvent>(this, selector);
}

bool MainPanels::ImageSaver::onEvent(Sh::Event& event) {

    if (event.mask() != Sh::Event::getMask<Sh::FileSelectEvent>()) {
        return false;
    }

    auto file_select = dynamic_cast<Sh::FileSelectEvent&>(event);

    IMAGE_MANAGER().setImagePath(file_select.file());
    IMAGE_MANAGER().saveImage();

    return true;
}

/*----------------------------------------------------------------------------*/

MainPanels::UpperMenu::UpperMenu(const Sh::Frame& frame)
    : Sh::UIWindow(frame) {

    auto saver = attach<Sh::UIButton<ImageSaver>>(
        Sh::Frame{ {0, 0}, {70, frame.size.y} }
    );

    saver->applyStyle(
            Sh::ColorFill(Sh::Color(38, 38, 38)), Sh::UIWindow::NORMAL,
            Sh::ColorFill(Sh::Color(70, 70, 70)), Sh::UIWindow::HOVER,
            Sh::ColorFill(Sh::Color(60, 60, 70)), Sh::UIWindow::CLICK,
            Sh::StaticLabel("Save", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER),
                Sh::UIWindow::ALL
        );

    auto opener = attach<Sh::UIButton<ImageOpener>>(
        Sh::Frame{ {75, 0}, {70, frame.size.y} }
    );

    opener->applyStyle(
        Sh::ColorFill(Sh::Color(38, 38, 38)), Sh::UIWindow::NORMAL,
        Sh::ColorFill(Sh::Color(70, 70, 70)), Sh::UIWindow::HOVER,
        Sh::ColorFill(Sh::Color(60, 60, 70)), Sh::UIWindow::CLICK,
        Sh::StaticLabel("Open", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER),
        Sh::UIWindow::ALL
    );

    applyStyle(
        Sh::ColorFill(Sh::Color(38, 38, 38)), Sh::UIWindow::ALL
    );

}

/*----------------------------------------------------------------------------*/

MainPanels::CanvasFrame::CanvasFrame(const Sh::Frame& frame)
    : Sh::UIFrame(frame, SB_WIDTH) {

    applyStyle(
        Sh::ColorFill(Sh::Color(100, 100, 100)), Sh::UIWindow::ALL
    );

    Sh::SubscriptionManager::subscribe<ImageUpdateEvent>(this, &IMAGE_MANAGER());
    update();
}

void MainPanels::CanvasFrame::update() {

    destroyChildren();

    auto canvas_size =
        static_cast<Sh::Vector2<double>>(LAYER_MANAGER().getActiveLayer().size());

    auto bg = attach<Sh::UIWindow>(Sh::Frame{
        {0, 0}, canvas_size + Sh::Vector2<double>{100 + SB_WIDTH, 100 + SB_WIDTH}
    });

    bg->attach<Canvas>(Sh::Frame{
        {50, 50},
        static_cast<Sh::Vector2<double>>(LAYER_MANAGER().getActiveLayer().size())
    });
    fit();
}

bool MainPanels::CanvasFrame::onEvent(Sh::Event& event) {

    if (event.mask() != Sh::Event::getMask<ImageUpdateEvent>()) {
        return Sh::UIFrame::onEvent(event);
    }

    update();

    return true;
}

/*============================================================================*/

MainPanels::AsidePanel::AsidePanel(const Sh::Frame &frame)
    : Sh::UIWindow(frame) {

    attach<LayerPanel>(
        Sh::Frame{ {0, 0}, {frame.size.x, 700} }
    );

}
