#pragma once

class FPSCounter
{
public:
    FPSCounter(double frameDuration);
    virtual ~FPSCounter();
  
public:
    double fps() const { return m_fps; }
    void rendered() { m_renderCount ++; }
    bool update(const double elapsedTime); // returns true if fps changed

private:
    const double m_frameDuration;
    int m_renderCount;
    double m_elapsedTime;
    double m_fps;
};