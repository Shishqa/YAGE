/*============================================================================*/
#include "YAGE.hpp"
#include "Font.hpp"
#include "ColorFill.hpp"
#include "CoreApplication.hpp"
#include "WindowManager.hpp"
#include "SubscriptionManager.hpp"
#include "FpsLabel.hpp"
#include "SessionManager.hpp"
/*============================================================================*/
using namespace YAGE;

int main(int argc, char* argv[]) {

    Sh::CoreApplication::init(&argc, argv, "./assets");

    SessionManager::initSession();

    constexpr Sh::Vector2<double> WIN_SIZE{
        1800, 1000
    };

    Sh::SPAWN_DIALOG<YageApp>(Sh::Frame{{30, 50}, WIN_SIZE});

    Sh::WindowManager::Root()->attach<Sh::FpsLabel>(
            Sh::Frame{{0, 0}, {100, 50}}
            );

    Sh::WindowManager::dump("layout.dot");
    Sh::SubscriptionManager::dump("subs.dot");

    Sh::CoreApplication::run();

    SessionManager::finalizeSession();

    return 0;
}

/*============================================================================*/
