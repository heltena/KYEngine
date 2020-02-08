#pragma once

#include <KYEngine/Entity.h>
#include <KYEngine/Utility/Vector4.h>

class Blackouter
{
public:
    Blackouter();
    virtual ~Blackouter();
    
public:
    bool isFinished() const { return ! m_running; }

public:
    void start(Entity* entity, bool onlyAlpha, double duration, double frequency, double offset = 0);
    void stop();
    void update(const double elapsedTime);

private:
    bool m_running;
    Entity* m_entity;
    bool m_onlyAlpha;
    Vector4 m_initialColor;
    double m_elapsedTime;
    double m_duration;
    double m_frequency;
    double m_offset;
};