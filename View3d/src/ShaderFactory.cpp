#include "pch.hpp"

#include "ShaderFactory.hpp"

#include "Shader.hpp"

using namespace dice::view3d;

namespace fs = std::filesystem;

const fs::path ShaderFactory::sc_cubeVertexShaderPath = "./shaders/Cube.vert";
const fs::path ShaderFactory::sc_cubeFragmentShaderPath = "./shaders/Cube.frag";

std::shared_ptr<Shader> ShaderFactory::CreateCubeShader()
{
    const GLchar* vertexShader = LoadShader(sc_cubeVertexShaderPath);
    const GLchar* fragmentShader = LoadShader(sc_cubeFragmentShaderPath);

    return std::make_shared<Shader>(vertexShader, fragmentShader);
}

const GLchar* ShaderFactory::LoadShader(const fs::path& shaderPath)
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
