/*============================================================================*/
#include "MainPanels.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

MainPanels::ImageOpener::ImageOpener(Sh::UIWindow *target)
    : Sh::Clickable(target)
    { }

void MainPanels::ImageOpener::reactOnRelease(Sh::MouseButtonEvent&) {

    auto selector = Sh::WindowManager::create<Sh::UIFileSelector>(
        Sh::Frame{ {30, 30}, {800, 600} },
        "./"
        );

    Sh::WindowManager::Root()->attach<Sh::UIDialog>(selector);

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

    auto selector = Sh::WindowManager::create<Sh::UIFileSelector>(
        Sh::Frame{ {30, 30}, {800, 600} },
        "./"
    );

    Sh::WindowManager::Root()->attach<Sh::UIDialog>(selector);
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

    saver->applyStyle<Sh::UIWindow::NORMAL>(
            Sh::ColorFill(Sh::Color(38, 38, 38)),
            Sh::StaticLabel("Save", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER)
        )
        ->applyStyle<Sh::UIWindow::HOVER>(
            Sh::ColorFill(Sh::Color(70, 70, 70)),
            Sh::StaticLabel("Save", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER)
        )
        ->applyStyle<Sh::UIWindow::CLICK>(
            Sh::ColorFill(Sh::Color(60, 60, 70)),
            Sh::StaticLabel("Save", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER)
        );


    auto opener = attach<Sh::UIButton<ImageOpener>>(
        Sh::Frame{ {75, 0}, {70, frame.size.y} }
    );

    opener->applyStyle<Sh::UIWindow::NORMAL>(
            Sh::ColorFill(Sh::Color(38, 38, 38)),
            Sh::StaticLabel("Open", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER)
        )
        ->applyStyle<Sh::UIWindow::HOVER>(
            Sh::ColorFill(Sh::Color(70, 70, 70)),
            Sh::StaticLabel("Open", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER)
        )
        ->applyStyle<Sh::UIWindow::CLICK>(
            Sh::ColorFill(Sh::Color(60, 60, 70)),
            Sh::StaticLabel("Open", Sh::Color::GHOST_WHITE, 20, Sh::Text::Align::CENTER)
        );

    applyStyle<Sh::UIWindow::NORMAL>(
        Sh::ColorFill(Sh::Color(38, 38, 38))
    );

}

/*----------------------------------------------------------------------------*/

MainPanels::CanvasFrame::CanvasFrame(const Sh::Frame& frame)
    : Sh::UIFrame(frame) {

    applyStyle<Sh::UIWindow::NORMAL>(
        Sh::ColorFill(Sh::Color(100, 100, 100))
    );

    Sh::SubscriptionManager::subscribe<ImageUpdateEvent>(this, &IMAGE_MANAGER());
    update();
}

void MainPanels::CanvasFrame::update() {

    std::cout << "update!\n";

    destroyChildren();
    attach<Canvas>(Sh::Frame{
        {40, 40},
        static_cast<Sh::Vector2<double>>(LAYER_MANAGER().getActiveLayer().size())
    });
    fit();
}

bool MainPanels::CanvasFrame::onEvent(Sh::Event& event) {

    std::cout << "got event\n";

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
