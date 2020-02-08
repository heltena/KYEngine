#include <KYEngine/Core.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Private/AnimSceneActions/WaitForMusicTimeValueAction.h>

#include <iostream>

const std::string WaitForMusicTimeValueAction::XML_NODE = "wait-for-music-time-value";

WaitForMusicTimeValueAction::WaitForMusicTimeValueAction()
	: m_music(NULL)
{
}

WaitForMusicTimeValueAction::~WaitForMusicTimeValueAction()
{
}

WaitForMusicTimeValueAction* WaitForMusicTimeValueAction::readFromXml(TiXmlElement* node)
{
	WaitForMusicTimeValueAction* action = new WaitForMusicTimeValueAction();

	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const std::string musicRef = TiXmlHelper::readString(node, "music-ref", true);
    const double value = TiXmlHelper::readDouble(node, "value", true);
	const double delta = TiXmlHelper::readDouble(node, "delta", false, 0.125);
    
	action->setName(name);
    action->setMusicRef(musicRef);
    action->setValue(value);
	action->setDelta(delta);
    
	return action;
}

void WaitForMusicTimeValueAction::start(SceneTimelineInfo* info)
{
    m_music = Core::resourceManager().music(m_musicRef);
    m_curDelta = 0;
    m_finished = ! m_music->isPlaying() || m_music->currentTime() >= m_value;

    std::cout << "WaitForMusicTimeValueAction::start: " << m_music->currentTime() << " wait for " << m_value << std::endl;
}

bool WaitForMusicTimeValueAction::isBlocking()
{
	return true;
}

bool WaitForMusicTimeValueAction::isFinished()
{
	return m_finished;
}

void WaitForMusicTimeValueAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
    m_curDelta += elapsedTime;
    if (m_curDelta >= m_delta) {
        m_finished = ! m_music->isPlaying() || m_music->currentTime() >= m_value;
        m_curDelta = 0;
    }
}
