#pragma once

#include <KYEngine/ConcretGame.h>
#include <KYEngine/Platform.h>
#include <KYEngine/Touch.h>

#include <KYEngine/Managers/AccelManager.h>
#include <KYEngine/Managers/HitManager.h>
#include <KYEngine/Managers/HudManager.h>
#include <KYEngine/Managers/I18nManager.h>
#include <KYEngine/Managers/InfoManager.h>
#include <KYEngine/Managers/MutexManager.h>
#include <KYEngine/Managers/ParticleSystemManager.h>
#include <KYEngine/Managers/SceneManager.h>
#include <KYEngine/Managers/RenderManager.h>
#include <KYEngine/Managers/ResourceManager.h>
#include <KYEngine/Managers/SoundManager.h>
#include <KYEngine/Managers/TelemetryManager.h>
#include <KYEngine/Managers/TimeManager.h>
#include <KYEngine/Managers/TouchManager.h>

#include <KYEngine/Utility/Vector4.h>

#include <map>

// Front Controller
class Core
{
private:
	static Core* m_instance;
	friend int main(int, char**);
	Core(ConcretGame* game, int width, int height, const std::string& version, const std::string& gameCenterSuffix);
	virtual ~Core();
	
public:
	static Core& instance();
    static AccelManager& accelManager();
    static HitManager& hitManager();
	static HudManager& hudManager();
	static I18nManager& i18nManager();
    static InfoManager& infoManager();
    static MutexManager& mutexManager();
    static ParticleSystemManager& particleSystemManager();
	static SceneManager& sceneManager();
	static RenderManager& renderManager();
	static ResourceManager& resourceManager();
	static SoundManager& soundManager();
    static TelemetryManager& telemetryManager();
    static TimeManager& timeManager();
	static TouchManager& touchManager();

    static const Platform& currentPlatform();

// Warning, use only from ObjC classes
public:
	void fireUpdate(const double elapsedTime);
    void fireSetAccelValue(float dx, float dy);
	void fireTouchesBegan(const std::map<int, Touch>& touches);
	void fireTouchesMoved(const std::map<int, Touch>& touches);
	void fireTouchesEnded(const std::map<int, Touch>& touches);
	void fireTouchesCancelled(const std::map<int, Touch>& touches);
	void fireInitRender();
	void fireRender();

private:
	ConcretGame* m_game;
    AccelManager m_accelManager;
    HitManager m_hitManager;
	HudManager m_hudManager;
	I18nManager m_i18nManager;
    InfoManager m_infoManager;
    MutexManager m_mutexManager;
    ParticleSystemManager m_particleSystemManager;
	SceneManager m_sceneManager;
	RenderManager m_renderManager;
	ResourceManager m_resourceManager;
	SoundManager m_soundManager;
    TelemetryManager m_telemetryManager;
    TimeManager m_timeManager;
    TouchManager m_touchManager;
    Platform m_currentPlatform;
};