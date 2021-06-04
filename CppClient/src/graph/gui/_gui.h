#pragma once
#include "imgui.h"
#include "impl/imgui_impl_glfw.h"
#include "impl/imgui_impl_opengl3.h"

class Gui
{
private:
    ImFont *font_default; // = io.Fonts->AddFontDefault();
    ImFont *font_cousine; // = io.Fonts -> AddFontFromFileTTF("resource/font/Cousine-Regular.ttf", 15.0f);
    ImFont *font_karla;   // = io.Fonts -> AddFontFromFileTTF("resource/font/Karla-Regular.ttf", 18.0f);
    ImFont *font_latol;   // = io void init()
    ImVec4 clear_color;   // = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    /* data */
public:
    void init();
    void drawGui();
    void renderGui();
};

extern Gui _Gui;