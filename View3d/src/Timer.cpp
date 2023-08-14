#include "pch.hpp"

#include "Timer.hpp"

using namespace dice::view3d;

Timer& Timer::GetInstance()
{
    static Timer timer;

    return timer;
}

void Timer::Update()
{
    m_lastFrameTime = m_currentFrameTime;
    m_currentFrameTime = glfwGetTime();
    m_dTime = m_currentFrameTime - m_lastFrameTime;
}

float Timer::GetTimeDelta() const
{
    return m_dTime;
}
