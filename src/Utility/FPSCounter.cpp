#include <KYEngine/Utility/FPSCounter.h>

FPSCounter::FPSCounter(double frameDuration)
    : m_frameDuration(frameDuration)
    , m_renderCount(0)
    , m_elapsedTime(0)
    , m_fps(0)
{
}

FPSCounter::~FPSCounter()
{
}

bool FPSCounter::update(const double elapsedTime)
{
    m_elapsedTime += elapsedTime;
    if (m_elapsedTime < m_frameDuration)
        return false;
        
    m_fps = m_renderCount / m_elapsedTime;
    m_elapsedTime = 0;
    m_renderCount = 0;
    return true;
}