#pragma once

#include <KYEngine/Utility/Vector4.h>

#include <iostream>

class Core;

class AccelManager
{
private:
	friend class Core;
	AccelManager();
	virtual ~AccelManager();
	
public:
    void activate();
    void deactivate();
    bool isActivated() const { return m_activated; }
    const Vector4& accelValue() const { return m_accelValue; }

private:
    void setAccelValue(const Vector4& accelValue) { m_accelValue = accelValue; }

private:
    bool m_activated;
    Vector4 m_accelValue;
};