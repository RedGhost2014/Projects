//#include <Windows.h>
//#include <synchapi.h>
#include <iostream>
#include <raylibcpp/include/raylib-cpp.hpp>
#include "Application.h"
//#include <Windows.h>
#include <stdlib.h>
//void __stdcall Sleep(unsigned long milliseconds);

int main() 
{
    //_sleep(5000);
    //Sleep(5);
    std::string appname = "Chess";
    size_t width = 1920;
    size_t height = 1080;

    Application myApp(width, height, appname, FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE);
    myApp.loadFigures("alpha/");
    myApp.setGameSettings(8, 8, 80);
    myApp.startApplicationWorkCycle();


    //raylib::Window window(screenWidth, screenHeight, "Chess");
    //raylib::Texture logo("raylib_logo.png");
    //MouseButton 
    //window.Maximize();
    //window.SetTargetFPS(60);
    //// window.Init;
    ////window.SetFullscreen(true);
    //while (!window.ShouldClose())
    //{
    //    window.BeginDrawing();

    //    window.ClearBackground(RAYWHITE);

    //    DrawText("Congrats! You created your first window!", 190, 200, 20, RED);
    //    DrawRectangle(100, 100, 50, 50, LIGHTGRAY);
    //    DrawRectangle(50, 50, 50, 50, DARKGRAY);
    //    // Object methods.
    //    //logo.Draw(screenWidth / 2 - logo.GetWidth() / 2, screenHeight / 2 - logo.GetHeight() / 2);

    //    window.EndDrawing();
    //}

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}