#include "pch.hpp"

#include "App.hpp"

#include "Cube.hpp"
#include "Shaders.hpp"

using namespace dice::view3d;

App::App(GLFWwindow* pWnd) :
    m_pWnd(pWnd)
{
    // Create shaders.
    const GLchar* vertexShaderSrc = Shaders::GetVertexShaderSource();
    const GLchar* fragmentShaderSrc = Shaders::GetFragmentShaderSource();
    m_pShader = std::make_unique<Shader>(vertexShaderSrc, fragmentShaderSrc);

    // Create renderables.
    m_pCube = std::make_unique<Cube>();
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
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_pShader)
    {
        m_renderer.Render(m_pCube.get(), *m_pShader);
    }
}
