/*============================================================================*/
#include "YAGE.hpp"
#include "Font.hpp"
#include "ColorFill.hpp"
#include "CoreApplication.hpp"
#include "WindowManager.hpp"
#include "SubscriptionManager.hpp"
#include "FpsLabel.hpp"
/*============================================================================*/
using namespace YAGE;

int main(int argc, char* argv[]) {

    Sh::CoreApplication::init(&argc, argv,
                              "/home/shishqa/dev/MIPT/2020_3/02_YAGE/assets/");

    constexpr Sh::Vector2<double> WIN_SIZE{
        1800, 1000
    };

    auto app = Sh::WindowManager::create<YageApp>(Sh::Frame{{30, 50}, WIN_SIZE});

    Sh::WindowManager::Root()->attach<Sh::UIDialog>(app);

    Sh::WindowManager::Root()->attach<Sh::FpsLabel>(
            Sh::Frame{{0, 0}, {100, 50}}
            )
            ->applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::Font{"fonts/FiraCode-Regular.ttf"},
                    Sh::FontSize{20},
                    Sh::ColorFill{Sh::Color::MAGENTA}
                    );

    Sh::WindowManager::dump("layout.dot");
    Sh::SubscriptionManager::dump("subs.dot");

    return Sh::CoreApplication::run();
}

/*============================================================================*/
