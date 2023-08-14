#ifndef DICE_VIEW3D_TIME_HPP
#define DICE_VIEW3D_TIME_HPP

namespace dice::view3d
{

class Timer
{
public:
    static Timer& GetInstance();

    void Update();

    float GetTimeDelta() const;

private:
    float m_currentFrameTime = 0.0f;
    float m_lastFrameTime = 0.0f;
    float m_dTime = 0.0f;

    Timer() = default;
    Timer(const Timer& other) = delete;
    Timer(Timer&& other) = delete;

    Timer& operator=(const Timer& other) = delete;
    Timer&& operator=(Timer&& other) = delete;
};

}

#endif
