#pragma once

#include <KYEngine/Touch.h>
#include <KYEngine/TouchListener.h>

#include <list>
#include <map>

class Core;

class TouchManager
{
private:
	friend class Core;
	TouchManager();
	virtual ~TouchManager();
	
public:
    void addListener(TouchListener* listener);
    void removeListener(TouchListener* listener);
    void removeAllListeners();
    
public:
    void touchesBegan(const std::map<int, Touch>& touches);
	void touchesMoved(const std::map<int, Touch>& touches);
	void touchesEnded(const std::map<int, Touch>& touches);
	void touchesCancelled(const std::map<int, Touch>& touches);

private:
    std::list<TouchListener*> m_listeners;
};