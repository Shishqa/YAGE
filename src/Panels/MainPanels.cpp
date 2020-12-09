/*============================================================================*/
#include "MainPanels.hpp"
/*============================================================================*/
using namespace YAGE;
/*============================================================================*/

MainPanels::ImageCreator::ImageCreator(Sh::UIWindow* target)
    : Sh::Clickable(target)
    { }

void MainPanels::ImageCreator::reactOnRelease(Sh::MouseButtonEvent&) {
    ImageManager::createImage({100, 100});
}


MainPanels::MainMenu::MainMenu(const Sh::Frame& frame)
    : Sh::UIWindow(frame) {

    attach<Sh::UILabelButton<ImageCreator>>(
        Sh::Frame{ {0, 0}, {70, frame.size.y} },
        "New", Sh::IPlatform::Align::CENTER
    )
        ->applyStyle<Sh::UIWindow::NORMAL>(
            Sh::ColorFill(Sh::Color(38, 38, 38))
        )
        ->applyStyle<Sh::UIWindow::HOVER>(
            Sh::ColorFill(Sh::Color(70, 70, 70))
        )
        ->applyStyle<Sh::UIWindow::CLICK>(
            Sh::ColorFill(Sh::Color(60, 60, 70))
        )
        ->attach<Sh::UILabel>(
            Sh::Frame{ {0, 0}, {100, frame.size.y} },
            "save"
        )
        ->applyStyle<Sh::UIWindow::NORMAL>(
            Sh::Font("fonts/FiraCode-Regular.ttf"),
            Sh::FontSize(20),
            Sh::ColorFill(Sh::Color::GHOST_WHITE)
        );

    applyStyle<Sh::UIWindow::NORMAL>(
        Sh::ColorFill(Sh::Color(38, 38, 38))
    );

}

/*----------------------------------------------------------------------------*/

MainPanels::CanvasFrame::CanvasFrame(const Sh::Frame& frame)
    : Sh::UIFrame(frame) {

    attach<Canvas>(Sh::Frame{
        {40, 40},
        static_cast<Sh::Vector2<double>>(ImageManager::getActiveLayer().size())
    });
    fit();

    applyStyle<Sh::UIWindow::NORMAL>(
        Sh::ColorFill(Sh::Color(10, 10, 10))
    );

}

/*============================================================================*/

MainPanels::AsidePanel::AsidePanel(const Sh::Frame &frame)
    : Sh::UIWindow(frame) {

    attach<LayerPanel>(
        Sh::Frame{ {0, 0}, {frame.size.x, 700} }
    );

    applyStyle<Sh::UIWindow::NORMAL>(
        Sh::ColorFill{Sh::Color(90, 80, 80)}
    );
}
