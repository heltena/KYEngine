#include <KYEngine/Private/AnimSceneActions/EarnAchievementAction.h>
#include <KYEngine/Core.h>
#include <KYEngine/SceneTimelineInfo.h>

#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string EarnAchievementAction::XML_NODE = "earn-achievement";

EarnAchievementAction::EarnAchievementAction()
{
}

EarnAchievementAction::~EarnAchievementAction()
{
}

EarnAchievementAction* EarnAchievementAction::readFromXml(TiXmlElement* element) {
	EarnAchievementAction* action = new EarnAchievementAction();
	
	const std::string name = TiXmlHelper::readString(element, "name", false, "<<undefined>>");
	const std::string achievementID = TiXmlHelper::readString(element, "achievement-id", true);
    const std::string percentage = TiXmlHelper::readString(element, "percentage", false, "100.0");
    
	action->setName(name);
	action->setAchievementID(achievementID);
    action->setPercentage(percentage);

	return action;
}

void EarnAchievementAction::start(SceneTimelineInfo* info)
{
    std::string achievementID = info->executeEL(m_achievementID);
    std::string percentage = info->executeEL(m_percentage);
    std::stringstream ss(percentage);
    double value;
    if (! (ss >> value))
        throw std::runtime_error("EarnAchievementAction::start: cannot convert " + m_percentage + "(" + percentage + ")");
    Core::infoManager().updateAchievementPercentage(m_achievementID, value);
}

bool EarnAchievementAction::isBlocking()
{
	return false;
}

bool EarnAchievementAction::isFinished()
{
	return true;
}

void EarnAchievementAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
