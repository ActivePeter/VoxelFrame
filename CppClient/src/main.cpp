#include <iostream>
#include "app.h"
// #include "Systems/DrawSys/DrawSys.h"
// #include "Systems/NetSys/NetSys.h"
// #include "Models/WindowInfoModel.h"
// #pragma comment(lib, "glfw3.lib")
// #pragma comment(lib, "ws2_32.lib")
// #pragma comment(lib, "libprotobuf.lib")
// #pragma comment(lib,"lib文件名或路径")
// #include "stb_image.h"

int main()
{
    auto &app1 = App::getInstance();
    app1.run();
    return 0;
}
