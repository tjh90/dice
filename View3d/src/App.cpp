#include "pch.hpp"

#include "App.hpp"

#include "Cube.hpp"
#include "Shader.hpp"
#include "ShaderFactory.hpp"

using namespace dice::view3d;

#ifdef DEBUG
std::ofstream g_log = std::ofstream("./log.log");
void LogCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* msg,
                 const void* userParam);
#endif

App::App(GLFWwindow* pWnd, int width, int height) :
    m_pWnd(pWnd)
{
#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(LogCallback, 0);
#endif

    // Set up viewport size with a callback.
    glfwSetFramebufferSizeCallback(pWnd, ResizeCallback);
    ResizeCallback(pWnd, width, height);

    // Create renderables.
    ShaderFactory shaderFactory;

    Colour cubeColour = ShaderFactory::CreateColour(128U, 0U, 0U);
    std::shared_ptr<Shader> pCubeShader = shaderFactory.CreateCubeShader(&cubeColour);
    std::unique_ptr<IRenderable> pCube = std::make_unique<Cube>(pCubeShader, glm::vec3 { 0.0f });

    Colour cube2Colour = ShaderFactory::CreateColour(0, 128U, 0U);
    std::shared_ptr<Shader> pCube2Shader = shaderFactory.CreateCubeShader(&cube2Colour);
    std::unique_ptr<IRenderable> pCube2 = std::make_unique<Cube>(pCube2Shader, glm::vec3 { 0.0f, 0.0f, -10.0f });

    m_renderables.push_back(std::move(pCube));
    m_renderables.push_back(std::move(pCube2));
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
        std::shared_ptr<Shader> pShader = pRenderable ? pRenderable->GetShader() : nullptr;
        if (pShader)
        {
            pShader->SetTransform(view);
        }
    }
}

#ifdef DEBUG
void LogCallback(GLenum,
                 GLenum type,
                 GLuint,
                 GLenum severity,
                 GLsizei,
                 const GLchar* msg,
                 const void*)
{
    std::string severityStr;
    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            severityStr = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityStr = "MED";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityStr = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityStr = "INFO";
            break;
        default:
            severityStr = "UNKNOWN";
            break;
    }

    std::string typeStr;
    switch(type)
    {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "DEPRECATED";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "UB";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "PERFORMANCE";
            break;
        default:
            typeStr = "OTHER";
            break;
    }

    g_log << "[" << severityStr << "] <<" << typeStr << ">>    " << msg << std::endl;
}
#endif
