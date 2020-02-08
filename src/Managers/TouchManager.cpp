#include <KYEngine/Managers/TouchManager.h>

#include <iostream>

TouchManager::TouchManager()
{
}

TouchManager::~TouchManager()
{
}

void TouchManager::addListener(TouchListener* listener)
{
    m_listeners.push_back(listener);
}

void TouchManager::removeListener(TouchListener* listener)
{
    m_listeners.remove(listener);
}

void TouchManager::removeAllListeners()
{
    m_listeners.clear();
}

void TouchManager::touchesBegan(const std::map<int, Touch>& touches)
{
    for(std::list<TouchListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); it++) {
        TouchListener* listener = *it;
        listener->touchesBegan(touches);
    }
}

void TouchManager::touchesMoved(const std::map<int, Touch>& touches)
{
    for(std::list<TouchListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); it++) {
        TouchListener* listener = *it;
        listener->touchesMoved(touches);
    }
}

void TouchManager::touchesEnded(const std::map<int, Touch>& touches)
{
    for(std::list<TouchListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); it++) {
        TouchListener* listener = *it;
        listener->touchesEnded(touches);
    }
}

void TouchManager::touchesCancelled(const std::map<int, Touch>& touches)
{
    for(std::list<TouchListener*>::iterator it = m_listeners.begin(); it != m_listeners.end(); it++) {
        TouchListener* listener = *it;
        listener->touchesCancelled(touches);
    }
}
