#pragma once

#include <KYEngine/Core.h>
#include <KYEngine/Action.h>
#include <KYEngine/ActionBlockedListener.h>
#include <KYEngine/Utility/Box.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/AnimSceneActions/ShowDialogPhraseParam.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <list>
#include <string>

class AnimSceneFactory;

class ShowDialogAction
    : public Action
    , public ActionBlockedListener
{
public:
	ShowDialogAction();
	virtual ~ShowDialogAction();

private:
    enum StateEnum {
        APPEARING,
        SHOWING,
        CHANGE_HEIGHT,
        DISAPPEARING,
        FINISHED
    };
    
public:
	static const std::string XML_NODE;
	static ShowDialogAction* readFromXml(TiXmlElement* node);
	
// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info);
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);

// ActionBlockedListener implementation
public:
    void actionUnblocked(SceneTimelineInfo* info);

// Actions
private:
    void appear(SceneTimelineInfo* info);
    void show(SceneTimelineInfo* info);
    void setFirstText(SceneTimelineInfo* info);
    void changeToNextText(SceneTimelineInfo* info);
    void disappear(SceneTimelineInfo* info);
    void hide(SceneTimelineInfo* info);
    
private:
    void updateAppearing(const double elapsedTime, SceneTimelineInfo* info);
    void updateShowing(const double elapsedTime, SceneTimelineInfo* info);
    void updateChangeHeight(const double elapsedTime, SceneTimelineInfo* info);
    void updateDisappearing(const double elapsedTime, SceneTimelineInfo* info);
    
	void setName(const std::string& name) { m_name = name; }
    void setBackgroundEntityRef(const std::string& backgroundEntityRef) { m_backgroundEntityRef = backgroundEntityRef; }
    void setZ(double z) { m_z = z; }
    void setAppearingCelerity(double appearingCelerity) { m_appearingCelerity = appearingCelerity; }
    void setDisapparingCelerity(double disappearingCelerity) { m_disappearingCelerity = disappearingCelerity; }
    void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; }
    void setBorderWidth(double borderWidth) { m_borderWidth = borderWidth; }
    void setBorderHeight(double borderHeight) { m_borderHeight = borderHeight; }
    void addTextParam(const ShowDialogPhraseParam& param) { m_textParams.push_back(param); }
    
private:
    void setPos(const Vector4& pos); 

private:
    StateEnum m_state;
	std::string m_name;
    std::string m_backgroundEntityRef;
    Vector4 m_pos;
    double m_appearingCelerity;
    double m_disappearingCelerity;
    std::string m_fontRef;
    Entity* m_backgroundEntity;
    Entity* m_entity;
    double m_borderWidth;
    double m_borderHeight;
    std::list<ShowDialogPhraseParam> m_textParams;
    std::list<ShowDialogPhraseParam>::iterator m_currentTextParam;

    bool m_useTime;
    double m_currentTime;
    int m_currentMessageId;
    int m_currentMessageCount;
    MessageKeyType m_currentKey;
    std::string m_currentText;
    Vector4 m_currentColor;
    
    double m_z;
    double m_fromPosY;
    double m_toPosY;
    double m_timeout;
    
    bool m_mustRegister;
};