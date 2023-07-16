#include "pch.hpp"

#include "Camera.hpp"

using namespace dice::view3d;

const glm::vec3 Camera::sc_left = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Camera::sc_up = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Camera::sc_front = glm::vec3(0.0f, 0.0f, -1.0f);

const std::unordered_map<Camera::Direction, glm::vec3> Camera::sc_directionMap
{
    { Direction::UP, -sc_up},
    { Direction::DOWN, +sc_up},
    { Direction::LEFT, sc_left},
    { Direction::RIGHT, -sc_left},
    { Direction::FORWARD, sc_front},
    { Direction::BACK, -sc_front}
};

void Camera::Move(const std::vector<Direction>& directions)
{
    if (directions.empty())
    {
        return;
    }

    glm::vec3 dPos { 0.0f };
    std::function<glm::vec3(glm::vec3, Direction)> perturbationFold = [](glm::vec3 pos, Direction dir)
    {
        return pos += sc_directionMap.at(dir);
    };
    dPos = std::accumulate(directions.begin(), directions.end(), dPos, perturbationFold);

    if (glm::length(dPos) > 0.0)
    {
        m_pos += m_speed * glm::normalize(dPos);
    }
}

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(m_pos, m_pos + sc_front, sc_up);
}
