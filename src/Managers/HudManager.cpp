#include <KYEngine/Core.h>
#include <KYEngine/Managers/HudManager.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <stdexcept>

HudManager::HudManager()
    : m_playingHud(NULL)
    , m_nextPlayingHud(NULL)
{
}

HudManager::~HudManager()
{
}

void HudManager::usePlayingHud(std::string const &name, bool appear, PlayingHudListener* listener)
{
    if (m_playingHud != NULL && m_playingHudName == name) {
        m_playingHud->setListener(listener);
    } else if (m_playingHud == NULL || m_playingHudName != name) {
        PlayingHud* tmpPlayingHud = Core::resourceManager().playingHud(name);
        if (appear)
            tmpPlayingHud->appear(listener);

        if (m_playingHud) {
            m_playingHud->disappear();
            m_nextPlayingHud = tmpPlayingHud;
        } else
             m_playingHud = tmpPlayingHud;
             
        m_playingHudName = name;
    }
}

bool HudManager::isPlayingHudActive() const
{
    return m_playingHud != NULL && m_playingHud->isAppeared();
}

bool HudManager::isPlayingHudDisappeared() const
{
    return m_playingHud == NULL || m_playingHud->isDisappeared();
}

PlayingHud& HudManager::playingHud()
{
    if (m_playingHud)
        return *m_playingHud;
    else
        throw std::runtime_error("PlayingHud doesn't exist");
}

void HudManager::abortPlayingHud()
{
    if (m_playingHud != NULL) {
        m_playingHud->abort();
        m_playingHud = m_nextPlayingHud;
    }
}

void HudManager::disappearPlayingHud()
{
    if (m_playingHud != NULL)
        m_playingHud->disappear();
}

void HudManager::update(const double elapsedTime)
{
    if (m_playingHud) {
        m_playingHud->update(elapsedTime);
        if (m_playingHud->isDisappeared()) {
            m_playingHud = m_nextPlayingHud;
            m_nextPlayingHud = NULL;
        }
    }
}

