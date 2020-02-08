#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Utility/Vector4.h>
#include <KYEngine/Private/Natives/NativeUtils.h>

#include <iostream>
#include <stdexcept>

#include <Chipmunk/chipmunk.h>

Core* Core::m_instance = NULL;

Core::Core(ConcretGame* game, int width, int height, const std::string& version, const std::string& gameCenterSuffix)
	: m_game(game)
    , m_infoManager(version, gameCenterSuffix)
{
    if (m_instance != NULL)
		throw std::runtime_error("Core is a singleton!");
	m_instance = this;
    Math::init();
    nativeUtilsInit();
    m_currentPlatform.setResolution(Box(height, width)); // Rotate!
    m_currentPlatform.setSuffix(width == 320 ? "" : "@2x");
    std::cout << "Resolution to " << m_currentPlatform.resolution() << " suffix: '" << m_currentPlatform.suffix() << "'" << std::endl;
    cpInitChipmunk();
    m_infoManager.setAppId(m_game->appId());
    m_infoManager.setBuyFullAppId(m_game->buyFullAppId());
    m_infoManager.setBuyLiteAppId(m_game->buyLiteAppId());
    m_infoManager.setBuyButtonPressedScript(m_game->buyButtonPressedScript());
    m_infoManager.load();
    
    std::cout << "Current country: " << currentCountry() << std::endl;
    std::cout << "iTunes URL: " << Core::infoManager().ratingInfo().traslatedUrl() << std::endl;

	m_game->initGame(*this);
}

Core::~Core()
{
}

Core& Core::instance()
{
	return *m_instance;
}

AccelManager& Core::accelManager()
{
    return m_instance->m_accelManager;
}

HitManager& Core::hitManager()
{
    return m_instance->m_hitManager;
}

HudManager& Core::hudManager()
{
	return m_instance->m_hudManager;
}

I18nManager& Core::i18nManager()
{
	return m_instance->m_i18nManager;
}

InfoManager& Core::infoManager()
{
    return m_instance->m_infoManager;
}

MutexManager& Core::mutexManager()
{
    return m_instance->m_mutexManager;
}

ParticleSystemManager& Core::particleSystemManager()
{
    return m_instance->m_particleSystemManager;
}

SceneManager& Core::sceneManager()
{
	return m_instance->m_sceneManager;
}

RenderManager& Core::renderManager()
{
	return m_instance->m_renderManager;
}

ResourceManager& Core::resourceManager()
{
	return m_instance->m_resourceManager;
}

SoundManager& Core::soundManager()
{
	return m_instance->m_soundManager;
}

TelemetryManager& Core::telemetryManager()
{
    return m_instance->m_telemetryManager;
}

TimeManager& Core::timeManager()
{
    return m_instance->m_timeManager;
}

TouchManager& Core::touchManager()
{
    return m_instance->m_touchManager;
}

const Platform& Core::currentPlatform()
{
    return m_instance->m_currentPlatform;
}

void Core::fireUpdate(const double elapsedTime)
{
    m_hitManager.update(elapsedTime);
    m_hudManager.update(elapsedTime);
    m_sceneManager.update(elapsedTime);
	m_soundManager.update(elapsedTime);
    m_timeManager.update(elapsedTime);
    m_particleSystemManager.update(elapsedTime);
	m_renderManager.update(elapsedTime);
}

void Core::fireSetAccelValue(float dx, float dy)
{
    m_accelManager.setAccelValue(Vector4(dx, dy).normalize());
}

void Core::fireTouchesBegan(const std::map<int, Touch>& touches)
{
    m_touchManager.touchesBegan(touches);
}

void Core::fireTouchesMoved(const std::map<int, Touch>& touches)
{
    m_touchManager.touchesMoved(touches);
}

void Core::fireTouchesEnded(const std::map<int, Touch>& touches)
{
    m_touchManager.touchesEnded(touches);
}

void Core::fireTouchesCancelled(const std::map<int, Touch>& touches)
{
    m_touchManager.touchesCancelled(touches);
}

void Core::fireInitRender()
{
	m_renderManager.init();
    m_particleSystemManager.init();
}

void Core::fireRender()
{
	m_renderManager.render();
}

