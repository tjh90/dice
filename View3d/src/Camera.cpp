#include "pch.hpp"

#include "Camera.hpp"

#include "Timer.hpp"

using namespace dice::view3d;

float Camera::s_speedFactor = 2.5f;

void Camera::ChangeSpeedFactor(bool increaseSpeed)
{
    float newSpeed = s_speedFactor + (increaseSpeed ? sc_speedIncrement : -sc_speedIncrement);
    if (newSpeed > 0.0f)
    {
        s_speedFactor = newSpeed;
    }
}

void Camera::Move(const std::vector<Direction>& directions)
{
    if (directions.empty())
    {
        return;
    }

    glm::vec3 dPos { 0.0f };
    for (Direction dir : directions)
    {
        switch(dir)
        {
            case Direction::UP:
                dPos -= m_up;
                break;
            case Direction::DOWN:
                dPos += m_up;
                break;
            case Direction::LEFT:
                dPos += m_left;
                break;
            case Direction::RIGHT:
                dPos -= m_left;
                break;
            case Direction::FORWARD:
                dPos += m_front;
                break;
            case Direction::BACK:
                dPos -= m_front;
                break;
        }
    };

    if (glm::length(dPos) > 0.0)
    {
        float speed = s_speedFactor * Timer::GetInstance().GetTimeDelta();
        m_pos += speed * glm::normalize(dPos);
        m_pos.y = std::max(0.1f, m_pos.y);
    }
}

glm::mat4 Camera::GetView() const
{
    return glm::lookAt(m_pos, m_pos + m_front, m_up);
}
