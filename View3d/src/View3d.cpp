#include "pch.hpp"

#include "App.hpp"

constexpr int sc_openGlMajorVersion = 4;
constexpr int sc_openGlMinorVersion = 6;

constexpr int sc_viewportSizeX = 1024;
constexpr int sc_viewportSizeY = 768;

using namespace dice::view3d;

int main()
{
    // OpenGL setup.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, sc_openGlMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, sc_openGlMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWnd = glfwCreateWindow(sc_viewportSizeX, sc_viewportSizeY, "Learn OpenGL", nullptr, nullptr);
    if (!pWnd)
    {
        throw std::runtime_error("Failed to create GLFW window.");
    }
    glfwMakeContextCurrent(pWnd);

    // GLAD steup.
    GLADloadproc procFunc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
    if (!gladLoadGLLoader(procFunc))
    {
        throw std::runtime_error("Failed to initialise GLAD.");
    }

    // Run app.
    App app(pWnd, sc_viewportSizeX, sc_viewportSizeY);
    app.RenderLoop();

    // Clean up.
    glfwTerminate();

    return 0;
}
