#pragma once

#include <KYEngine/Utility/Mutex.h>

class Core;

class MutexManager
{
private:
	friend class Core;
	MutexManager();
	virtual ~MutexManager();
	
public:
    Mutex& textureLoaderMutex() { return m_textureLoaderMutex; }

private:
    Mutex m_textureLoaderMutex;
};