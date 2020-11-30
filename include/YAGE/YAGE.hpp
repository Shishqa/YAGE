/*============================================================================*/
#ifndef SHISHGL_YAGE_HPP
#define SHISHGL_YAGE_HPP
/*============================================================================*/
#include "UIWindow.hpp"
using namespace ShishGL;
/*============================================================================*/
namespace YAGE {

    void init();

    UIWindow* createMainLayout(const Viewport& frame);

    UIWindow* createMenuLayout(const Viewport& frame);

    UIWindow* createCanvasLayout(const Viewport& frame);

    UIWindow* createToolsLayout(const Viewport& frame);

}
/*============================================================================*/
#endif //SHISHGL_YAGE_HPP
/*============================================================================*/