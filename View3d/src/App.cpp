#include "App.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Cube.hpp"

using namespace dice::view3d;

App::App()
{
    // OpenGL setup.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, sc_openGlMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, sc_openGlMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_pWnd = glfwCreateWindow(sc_viewportSizeX, sc_viewportSizeY, "Learn OpenGL", nullptr, nullptr);
    if (!m_pWnd)
    {
        throw std::runtime_error("Failed to create GLFW window.");
    }
    glfwMakeContextCurrent(m_pWnd);

    // Set up viewport size with a callback.
    GLFWframebuffersizefun resizeCallback = [] (GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    };
    glfwSetFramebufferSizeCallback(m_pWnd, resizeCallback);

    // GLAD steup.
    GLADloadproc procFunc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
    if (!gladLoadGLLoader(procFunc))
    {
        throw std::runtime_error("Failed to initialise GLAD.");
    }

    m_pCube = std::make_unique<Cube>();
}

App::~App()
{
    glfwTerminate();
}

void App::RenderLoop()
{
    while (!glfwWindowShouldClose(m_pWnd))
    {
        ProcessInput();

        Render();

        glfwSwapBuffers(m_pWnd);
        glfwPollEvents();
    }
}

void App::ProcessInput()
{
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_W))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_S))
    {
        glfwSetWindowShouldClose(m_pWnd, true);
    }
}

void App::Render()
{
    if (m_pCube)
    {
        m_pCube->Render();
    }
}
