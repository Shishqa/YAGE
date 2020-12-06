/*============================================================================*/
#ifndef YAGE_MAIN_PANELS_HPP
#define YAGE_MAIN_PANELS_HPP
/*============================================================================*/
#include "Behaviors.hpp"
#include "Styles.hpp"
#include "GUI.hpp"
#include "Canvas.hpp"
#include "ColorPicker.hpp"
#include "LayerSelector.hpp"
/*============================================================================*/
namespace YAGE::MainPanels {

    class Menu : public Sh::UIWindow {
    public:

        explicit Menu(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            attach<Sh::UIWindow>(
                    Sh::Frame{ {0, 0}, {70, frame.size.y} }
                    )
                    ->addBehavior<Sh::Clickable>()
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
    };

    class CanvasFrame : public Sh::UIFrame {
    public:

        explicit CanvasFrame(const Sh::Frame& frame)
                : Sh::UIFrame(frame,
                              {{0, 0},
                               static_cast<Sh::Vector2<double>>(ImageManager::getActiveLayer().size())
                              }) {

            attach<Canvas>(Sh::Frame{
                {40, 40},
                static_cast<Sh::Vector2<double>>(ImageManager::getActiveLayer().size())
            });

            applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::ColorFill(Sh::Color(10, 10, 10))
                    );

        }

    };

    class ToolingPanel : public Sh::UIWindow {
    public:

        explicit ToolingPanel(const Sh::Frame& frame)
                : Sh::UIWindow(frame) {

            double tool_list_width = 2 * ToolsPanel::PADDING +
                                     ToolsPanel::N_BUTTONS_IN_ROW * (
                                             ToolsPanel::BUTTON_SIZE.x +
                                             ToolsPanel::SPACING
                                     ) -
                                     ToolsPanel::SPACING;

            attach<ToolsPanel::ToolList>(Sh::Frame{
                    {0, 0},
                    {tool_list_width, 600}
            })
            ->applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::ColorFill(Sh::Color(90, 80, 80))
                    );

            attach<ColorTooler>(
                    Sh::Frame{ {0, 600}, {tool_list_width, tool_list_width} }
                    );

        }
    };

    class AsidePanel : public Sh::UIWindow {
    public:

        explicit AsidePanel(const Sh::Frame& frame)
                : Sh::UIWindow(frame)
                , n_layers(ImageManager::getLayers().size()) {

            layer_list = attach<LayerList>(
                    Sh::Frame{ {0, 0}, {frame.size.x, 500} }
                    );

            applyStyle<Sh::UIWindow::NORMAL>(
                    Sh::ColorFill{Sh::Color(90, 80, 80)}
                    );

        }

        void onRender() override {

            Sh::UIWindow::onRender();

            if (n_layers != ImageManager::getLayers().size()) {

                Sh::WindowManager::destroy(layer_list);
                layer_list = attach<LayerList>(
                        Sh::Frame{ {0, 0}, {getFrame().size.x, 500} }
                );

                n_layers = ImageManager::getLayers().size();
            }

        }

    private:

        size_t n_layers;
        Sh::UIWindow* layer_list;

    };

}
/*============================================================================*/
#endif //YAGE_MAIN_PANELS_HPP
/*============================================================================*/
