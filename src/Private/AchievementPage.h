#pragma once

#include <KYEngine/Entity.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>
#include <string>

class Core;
class RenderManager;

class AchievementPage
{
private:
    enum StateEnum {
        DEACTIVATED,
        HIDE,
        APPEARING,
        SHOWING,
        DISAPPEARING
    };
    
private:
	friend class RenderManager;
    AchievementPage();
    virtual ~AchievementPage();
    
public:
    void init(const Vector4& hidePos, const Vector4& showPos, const std::string& meshRef, const std::string& fontRef, double lineLength, double lineSpacing, AlignType align, const Vector4& pivot, const Vector4& borderColor, double appearDuration, double showingDuration, double disappearDuration, double accelMagnitude);
    void done();
    void update(const double elapsedTime);

public:
    void pushNewMessage(const std::string& message);

private:
    void updateHide(const double elapsedTime);
    void updateAppearing(const double elapsedTime);
    void updateShowing(const double elapsedTime);
    void updateDisappearing(const double elapsedTime);

    void startHide();
    void startAppearing();
    void startShowing();
    void startDisappearing();
    
    void testForNewMessage();
    
private:
    StateEnum m_state;
    RenderLayer* m_layer;
    Entity* m_backgroundEntity;
    Entity* m_textEntity;
    Vector4 m_hidePos;
    Vector4 m_showPos;
    double m_appearDuration;
    double m_showingDuration;
    double m_disappearDuration;
    double m_accelMagnitude;
    double m_timeout;
    std::list<std::string> m_messages;
};
