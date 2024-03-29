#include "_gui.h"
#include "graph/_Graph.h"
#include "system_related/imgui_impl_sys.h"
#include "imgui.h"
#include "app.h"
// Gui _Gui;

void Gui::init()
{
	auto& graph = *App::getInstance().graphPtr;

	// WindowInfoModel &wim = WindowInfoModel::getInstance();
	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	imguiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(imguiContext);
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui_ImplSdl_Init(graph.gameWindow.window);
	// ImGui_ImplGlfw_InitForOpenGL(graph.gameWindow.window, true);
	// ImGui_ImplOpenGL3_Init();

	// Setup style
	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	ImGui::StyleColorsLight();
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(graph.highDPIscaleFactor);
	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	ImFontConfig config;
	config.SizePixels = 18.0f * graph.highDPIscaleFactor;
	font_default = io.Fonts->AddFontDefault(&config);
	font_cousine = io.Fonts->AddFontFromFileTTF("resource/font/Cousine-Regular.ttf", 15.0f * graph.highDPIscaleFactor);
	font_karla = io.Fonts->AddFontFromFileTTF("resource/font/Karla-Regular.ttf", 18.0f * graph.highDPIscaleFactor);
	font_latol = io.Fonts->AddFontFromFileTTF("resource/font/Lato-Regular.ttf", 18.0f * graph.highDPIscaleFactor);

	// io.Fonts->AddFontFromFileTTF("resource/font/DroidSans.ttf", 16.0f);
	// io.Fonts->AddFontFromFileTTF("resource/font/ProggyTiny.ttf", 10.0f);
	// ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	// IM_ASSERT(font != NULL);
	clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// io.MouseDrawCursor = true;

	// if (view)
	// {
	//     const float dpi = (float)[view.window backingScaleFactor];
	//     io.DisplaySize = ImVec2((float)view.bounds.size.width, (float)view.bounds.size.height);
	//     io.DisplayFramebufferScale = ImVec2(dpi, dpi);
	// }
	// float dpi = io.dpiMainViewport->DpiScale;
	// io.DisplaySize = ImVec2((float)w / dpi, (float)h / dpi);
}

void Gui::drawGui()
{
	// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::renderGui()
{
	// Start the ImGui frame
	// ImGui_ImplOpenGL3_NewFrame();
	// ImGui_ImplGlfw_NewFrame();
	ImGui_ImplSdl_NewFrame(App::getInstance().graphPtr->gameWindow.window);
	// ImGui::NewFrame();

	static int font_current = 0;
	static int old_font_current = 0;
	switch (font_current)
	{
	case 0:
		ImGui::PushFont(font_default);
		break;
	case 1:
		ImGui::PushFont(font_cousine);
		break;
	case 2:
		ImGui::PushFont(font_karla);
		break;
	case 3:
		ImGui::PushFont(font_latol);
		break;
	}

	// 1. Show a simple window.
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
	{
		static float f = 0.0f;
		static float fpitch = 0.0f;
		static int counter = 0;
		ImGui::Text("Hello, world!"); // Display some text (you can use a format string too)
		{
			auto camPtr = App::getInstance().graphPtr->cameraPtr;
			if (camPtr)
			{
				char buff[90] = { 0 };
				sprintf_s(buff, "cam pos: %.2f %.2f %.2f", camPtr->getPosition().x, camPtr->getPosition().y, camPtr->getPosition().z);
				ImGui::Text(buff);
			}
			// auto player=
			if (App::getInstance().gamePtr)
			{
				auto player = App::getInstance().gamePtr->mainPlayer;
				if (player)
				{
					char buff[90] = { 0 };
					sprintf_s(buff, "cam chunk pos: %d %d %d",
						player->chunkX,
						player->chunkY,
						player->chunkZ);
					ImGui::Text(buff);

					auto& blockSelector = player->mainPlayerWorldOperator.blockSelector;
					if (blockSelector.active) {
						char buff[90] = { 0 };
						sprintf_s(buff, "raycasted block: %d %d %d",
							blockSelector.position.x,
							blockSelector.position.y,
							blockSelector.position.z);
						ImGui::Text(buff);
					}
				}
			}
		}
		{
			auto& cursor = App::getInstance().graphPtr->gameWindow.cursor;
			// auto io = App::getInstance().ioPtr;
			// if (io)
			// {
			char buff[50] = { 0 };
			sprintf_s(buff, "cursor x:%.2f, y:%.2f", cursor.cursorX, cursor.cursorY);
			ImGui::Text(buff);
			// }
		}

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
		// App::getInstance().graphPtr->cameraPtr->Yaw = 360 * f;
		ImGui::SliderFloat("float2", &fpitch, -89.0f, 89.0f);
		// App::getInstance().graphPtr->cameraPtr->Pitch = fpitch;

		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		ImGui::Text("Windows");
		// ImGui::Checkbox("Demo Window", &show_demo_window);    // Edit bools storing our windows open/close state
		// ImGui::Checkbox("Themes Window", &show_theme_window); // Edit bools storing our windows open/close state
		// ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::Text("Font Samples");
		ImGui::PushFont(font_cousine);
		ImGui::Text("Font Render Test - Cousine: Bit Test.123");
		ImGui::Text("Font Render Test - Cousine: XXXXXXXXXXXX");
		ImGui::PopFont();

		ImGui::PushFont(font_karla);
		ImGui::Text("Font Render Test - Karla: Bit Test.123");
		ImGui::Text("Font Render Test - Karla: XXXXXXXXXXXX");
		ImGui::PopFont();

		ImGui::PushFont(font_latol);
		ImGui::Text("Font Render Test - Lato: Bit Test.123");
		ImGui::Text("Font Render Test - Lato: XXXXXXXXXXXX");
		ImGui::PopFont();

		if (ImGui::Button("Button")) // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		{
			counter++;
			std::cout << "hhh" << std::endl;
			// printf("no gui click\r\n");
			// printf("no gui clic\r\n");
		}

		if (ImGui::Button("Render"))
		{
			// isRender = !isRender;
		}

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		if ( //ImGui::GetIO().MouseClicked[0] &&
			ImGui::GetIO().MouseClicked[0] &&
			!ImGui::IsAnyItemHovered() &&
			!ImGui::IsAnyWindowHovered())
		{
			std::cout << "hhhs" << std::endl;
			guiNothingClick_EventPublisher.pub2All();
			// for (auto i : guiNothingClickEventPuber.listeners)
			// {
			//     i->GuiNothingClickListenerCallback();
			// }
		}
	}

	ImGui::PopFont();

	// Rendering
	ImGui::Render();
}
