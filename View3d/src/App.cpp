#include "pch.hpp"

#include "App.hpp"

#include "Cube.hpp"
#include "Shader.hpp"
#include "Shaders.hpp"

using namespace dice::view3d;

App::App(GLFWwindow* pWnd) :
    m_pWnd(pWnd),
    m_pShaders(Shaders::GetInstance())
{
    // Create renderables.
    if (!m_pShaders)
    {
        throw std::runtime_error("Failed to initialise shaders.");
    }

    std::weak_ptr<Shader> pCubeShader = m_pShaders->GetCubeShader();
    std::unique_ptr<Cube> pCube = std::make_unique<Cube>(pCubeShader);

    m_renderables.push_back(std::move(pCube));
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

    for (std::unique_ptr<IRenderable>& pRenderable : m_renderables)
    {
        m_renderer.Render(pRenderable.get());
    }
}
