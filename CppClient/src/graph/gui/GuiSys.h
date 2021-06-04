#ifndef __GUISYS_H__
#define __GUISYS_H__

#include "imgui.h"
#include "impl/imgui_impl_glfw.h"
#include "impl/imgui_impl_opengl3.h"

namespace DrawSys
{
    namespace GuiSys
    {
        void init();
        void drawGui();
        void renderGui();
        extern bool isRender;
    } // namespace GuiSys
} // namespace DrawSys

#endif // __GUISYS_H__