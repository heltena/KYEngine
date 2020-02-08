#pragma once

#include <KYEngine/Core.h>
#include <KYEngine/Action.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/ActionBlockedListener.h>
#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/EffectType.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Private/AnimSceneActions/ShowDialogPhraseParam.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <list>
#include <string>

class AnimSceneFactory;

class ShowPopupAction
    : public Action
    , public ActionBlockedListener
{
public:
	ShowPopupAction();
	virtual ~ShowPopupAction();

private:
    enum StateEnum {
        APPEARING,
        SHOWING,
        DISAPPEARING,
        FINISHED
    };
    
public:
	static const std::string XML_NODE;
	static ShowPopupAction* readFromXml(TiXmlElement* node);
	
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
    void disappear(SceneTimelineInfo* info);
    void hide(SceneTimelineInfo* info);
    
private:
    void updateAppearing(const double elapsedTime, SceneTimelineInfo* info);
    void updateShowing(const double elapsedTime, SceneTimelineInfo* info);
    void updateDisappearing(const double elapsedTime, SceneTimelineInfo* info);
    
	void setName(const std::string& name) { m_name = name; }
    void setText(const std::string& text) { m_text = text; }
    void setBackgroundEntityRef(const std::string& backgroundEntityRef) { m_backgroundEntityRef = backgroundEntityRef; }
    void setPos(const Vector4& pos) { m_pos = pos; }
    void setAppearDuration(double appearDuration) { m_appearDuration = appearDuration; }
    void setAppearEffect(EffectType appearEffect) { m_appearEffect = appearEffect; }
    void setAppearAccelMagnitude(double appearAccelMagnitude) { m_appearAccelMagnitude = appearAccelMagnitude; }
    void setDisappearDuration(double disappearDuration) { m_disappearDuration = disappearDuration; }
    void setDisappearEffect(EffectType disappearEffect) { m_disappearEffect = disappearEffect; }
    void setDisappearAccelMagnitude(double disappearAccelMagnitude) { m_disappearAccelMagnitude = disappearAccelMagnitude; }
    void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; }
    void setBorderWidth(double borderWidth) { m_borderWidth = borderWidth; }
    void setBorderHeight(double borderHeight) { m_borderHeight = borderHeight; }
    void setColor(const Vector4& color) { m_color = color; }
    void setAlign(AlignType align) { m_align = align; }
    void setVerticalAlign(AlignType verticalAlign) { m_verticalAlign = verticalAlign; }
    void setLineLength(double lineLength) { m_lineLength = lineLength; }
    void setUseTime(bool useTime) { m_useTime = useTime; }
    void setTime(double time) { m_time = time; }
    void setWaitForTouch(bool waitForTouch) { m_waitForTouch = waitForTouch; }
    void setUseBackground(bool useBackground) { m_useBackground = useBackground; }

private:
    StateEnum m_state;
	std::string m_name;
    std::string m_text;
    std::string m_backgroundEntityRef;
    Vector4 m_pos;
    double m_appearDuration;
    double m_appearAccelMagnitude;
    EffectType m_appearEffect;
    double m_disappearDuration;
    double m_disappearAccelMagnitude;
    EffectType m_disappearEffect;
    std::string m_fontRef;
    Entity* m_backgroundEntity;
    Entity* m_entity;
    double m_borderWidth;
    double m_borderHeight;
    Vector4 m_color;
    AlignType m_align;
    AlignType m_verticalAlign;
    double m_lineLength;
    bool m_useTime;
    double m_time;
    bool m_waitForTouch;
    bool m_useBackground;
    
    double m_currentTime;
    
    Box m_box;
    Vector4 m_backgroundScale;
    double m_backgroundAlpha;
    double m_timeout;
    
    Vector4 m_firstAppearPos;
    Vector4 m_showPos;
    Vector4 m_disappearedPos;
    Vector4 m_textOffset;
    
    bool m_mustRegister;
};