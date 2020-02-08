#include <KYEngine/Core.h>
#include <KYEngine/Private/AnimSceneActions/InitGameCenterAction.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <cmath>
#include <iostream>

const std::string InitGameCenterAction::XML_NODE = "init-game-center";

InitGameCenterAction::InitGameCenterAction()
{
}

InitGameCenterAction::~InitGameCenterAction()
{
}

InitGameCenterAction* InitGameCenterAction::readFromXml(TiXmlElement* node)
{
	InitGameCenterAction* action = new InitGameCenterAction();
	
	const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const Vector4 hidePos = TiXmlHelper::readVector(node, "hx", "hy", "hz", "", READ_X | READ_Y | READ_Z);
	const Vector4 showPos = TiXmlHelper::readVector(node, "sx", "sy", "sz", "", READ_X | READ_Y | READ_Z);
    const std::string meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
	const std::string fontRef = TiXmlHelper::readString(node, "font-ref", true);
	double lineLength = TiXmlHelper::readDouble(node, "line-length", true);
    double lineSpacing = TiXmlHelper::readDouble(node, "line-spacing", true);
    AlignType align = TiXmlHelper::readAlignType(node, "align", false, ALIGN_LEFT);
	const std::string defaultText = TiXmlHelper::readString(node, "default-text", false, "");
    const Vector4 pivot = TiXmlHelper::readVector(node, "px", "py", "", "", NO_READ, 0, 0, 0, 0);
    const Vector4 borderColor = TiXmlHelper::readVector(node, "br", "bg", "bb", "ba", NO_READ, 0, 0, 0, 1);
    double appearDuration = TiXmlHelper::readDouble(node, "appear-duration", true);
    double showingDuration = TiXmlHelper::readDouble(node, "showing-duration", true);
    double disappearDuration = TiXmlHelper::readDouble(node, "disappear-duration", false, appearDuration);
    double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", false, 0.0);
    
	action->setName(name);
    action->setHidePos(hidePos);
    action->setShowPos(showPos);
    action->setMeshRef(meshRef);
	action->setFontRef(fontRef);
	action->setLineLength(lineLength);
	action->setLineSpacing(lineSpacing);
	action->setAlign(align);
    action->setPivot(pivot);
    action->setBorderColor(borderColor);
    action->setAppearDuration(appearDuration);
    action->setShowingDuration(showingDuration);
    action->setDisappearDuration(disappearDuration);
    action->setAccelMagnitude(accelMagnitude);
    
	return action;
}

void InitGameCenterAction::start(SceneTimelineInfo* info)
{
    Core::infoManager().initGameCenter();
    Core::infoManager().authenticateLocalUser();
    
    Core::renderManager().initAchievementPage(m_hidePos, m_showPos, m_meshRef, m_fontRef, m_lineLength, m_lineSpacing, m_align, m_pivot, m_borderColor, m_appearDuration, m_showingDuration, m_disappearDuration, m_accelMagnitude);
}

bool InitGameCenterAction::isBlocking()
{
	return false;
}

bool InitGameCenterAction::isFinished()
{
	return true;
}

void InitGameCenterAction::update(const double elapsedTime, SceneTimelineInfo* info)
{
}
