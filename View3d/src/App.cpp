#include "pch.hpp"

#include "App.hpp"

#include "Cube.hpp"
#include "Shader.hpp"
#include "Shaders.hpp"

using namespace dice::view3d;

App::App(GLFWwindow* pWnd, int width, int height) :
    m_pWnd(pWnd),
    m_pShaders(Shaders::GetInstance())
{
    // Set up viewport size with a callback.
    glfwSetFramebufferSizeCallback(pWnd, ResizeCallback);
    ResizeCallback(pWnd, width, height);

    // Create renderables.
    if (!m_pShaders)
    {
        throw std::runtime_error("Failed to initialise shaders.");
    }

    std::weak_ptr<Shader> pCubeShader = m_pShaders->GetCubeShader();
    std::unique_ptr<Cube> pCube = std::make_unique<Cube>(pCubeShader);

    m_renderables.push_back(std::move(pCube));
}

void App::ResizeCallback(GLFWwindow*, int width, int height)
{
    Renderer::SetAspectRatio((1.0f * width) / height);
    glViewport(0, 0, width, height);
}

void App::RenderLoop()
{
    while (!glfwWindowShouldClose(m_pWnd))
    {
        ProcessInput();

        m_renderer.Render(m_renderables);

        glfwSwapBuffers(m_pWnd);
        glfwPollEvents();
    }
}

void App::ProcessInput()
{
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(m_pWnd, true);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_SPACE))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Movement.
    std::vector<Camera::Direction> directions;
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_W))
    {
        directions.push_back(Camera::Direction::FORWARD);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_S))
    {
        directions.push_back(Camera::Direction::BACK);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_A))
    {
        directions.push_back(Camera::Direction::LEFT);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_D))
    {
        directions.push_back(Camera::Direction::RIGHT);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_E))
    {
        directions.push_back(Camera::Direction::UP);
    }
    if (GLFW_PRESS == glfwGetKey(m_pWnd, GLFW_KEY_Q))
    {
        directions.push_back(Camera::Direction::DOWN);
    }
    m_camera.Move(directions);

    glm::mat4 view = m_camera.GetView();
    for (const auto& pRenderable : m_renderables)
    {
        std::shared_ptr<Shader> pShader = pRenderable ? pRenderable->GetShader().lock() : nullptr;
        if (pShader)
        {
            pShader->SetTransform(view);
        }
    }
}
