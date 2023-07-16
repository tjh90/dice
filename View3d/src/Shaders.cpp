#include "pch.hpp"

#include "Shaders.hpp"

#include "Shader.hpp"

using namespace dice::view3d;

namespace fs = std::filesystem;

const fs::path Shaders::sc_cubeVertexShaderPath = "./shaders/Cube.vert";
const fs::path Shaders::sc_cubeFragmentShaderPath = "./shaders/Cube.frag";

std::unique_ptr<Shaders> Shaders::sc_pInstance = nullptr;

Shaders* Shaders::GetInstance()
{
    if (!sc_pInstance)
    {
        sc_pInstance = std::unique_ptr<Shaders>(new Shaders);
    }

    return sc_pInstance.get();
}

std::weak_ptr<Shader> Shaders::GetCubeShader()
{
    if (!m_pCubeShader)
    {
        const GLchar* vertexShader = LoadShader(sc_cubeVertexShaderPath);
        const GLchar* fragmentShader = LoadShader(sc_cubeFragmentShaderPath);

        m_pCubeShader = std::make_shared<Shader>(vertexShader, fragmentShader);
    }

    return m_pCubeShader;
}

const GLchar* Shaders::LoadShader(const fs::path& shaderPath)
{
    auto it = m_shaderPathMap.find(shaderPath);
    bool requiresLoading = it == m_shaderPathMap.end() || it->second.empty();
    if (requiresLoading && fs::exists(shaderPath))
    {
        std::fstream file(shaderPath, std::ios::in);
        std::uintmax_t fileSize = fs::file_size(shaderPath);
        std::string content(fileSize, '\0');
        file.read(content.data(), fileSize);

        m_shaderPathMap[shaderPath] = content;
    }

    return m_shaderPathMap[shaderPath].c_str();
}
