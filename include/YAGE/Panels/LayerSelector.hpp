/*============================================================================*/
#ifndef YAGE_LAYERSELECTOR_HPP
#define YAGE_LAYERSELECTOR_HPP
/*============================================================================*/
#include "ImageManager.hpp"
#include "GUI.hpp"
#include "Styles.hpp"
#include "Behaviors.hpp"
/*============================================================================*/
namespace YAGE {

    class LayerSelector {
    public:

        explicit LayerSelector(size_t layer)
                : to_set(layer)
                { }

        void operator()() const {
            ImageManager::setActiveLayer(to_set);
        }

    private:

        size_t to_set;

    };

    /*------------------------------------------------------------------------*/

    class LayerList : public Sh::UIWindow {
    public:

        static constexpr double BUTTON_HEIGHT = 30;

        explicit LayerList(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            for (size_t layer = 0; layer < ImageManager::getLayers().size(); ++layer) {

                attach<Sh::UIButton<LayerSelector>>(
                        Sh::Frame{ {0, static_cast<double>(layer) * BUTTON_HEIGHT},
                                   {frame.size.x, BUTTON_HEIGHT} },
                        layer
                        )
                        ->applyStyle<Sh::UIWindow::NORMAL>(
                                Sh::ColorFill{Sh::Color(120, 120, 120)}
                                )
                        ->applyStyle<Sh::UIWindow::HOVER>(
                                Sh::ColorFill{Sh::Color(200, 200, 200)}
                                )
                        ->applyStyle<Sh::UIWindow::CLICK>(
                                Sh::ColorFill{Sh::Color(230, 230, 230)}
                                );

            }
        }
    };

}
/*============================================================================*/
#endif //YAGE_LAYERSELECTOR_HPP
/*============================================================================*/
