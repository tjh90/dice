#include "App.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace dice::view3d;

int main()
{
    try
    {
        App app;
        app.RenderLoop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}