#include <KYEngine/Managers/AccelManager.h>
#include <KYEngine/Private/Natives/NativeUtils.h>

AccelManager::AccelManager()
    : m_activated(false)
{
}

AccelManager::~AccelManager()
{
}

void AccelManager::activate()
{
    m_activated = true;
    accelerometerActivate();
}

void AccelManager::deactivate()
{
    accelerometerDeactivate();
    m_activated = false;
}

