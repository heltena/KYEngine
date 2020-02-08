#pragma once

#include <KYEngine/AddJoystickButtonParam.h>
#include <KYEngine/Private/Huds/HudJoystickButton.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <string>

class AddJoystickButtonParamImpl
    : public AddJoystickButtonParam
{
public:
    AddJoystickButtonParamImpl();
    AddJoystickButtonParamImpl(const AddJoystickButtonParamImpl& other);
    virtual ~AddJoystickButtonParamImpl();
    
public:
	static const std::string XML_NODE;
	static AddJoystickButtonParamImpl* readFromXml(TiXmlElement* node);
    
public:
    const std::string& meshRef() const { return m_meshRef; }
    const std::string& backgroundMeshRef() const { return m_backgroundMeshRef; }
    const Vector4& appearedPos() const { return m_appearedPos; }
    const Vector4& disappearedPos() const { return m_disappearedPos; }
    double animDuration() const { return m_animDuration; }
    double accelMagnitude() const { return m_accelMagnitude; }
    double radius() const { return m_radius; }
    bool canMoveHorz() const { return m_canMoveHorz; }
    bool canMoveVert() const { return m_canMoveVert; }

// AddJoystickButtonParam implementation
public:
    int id() const { return m_id; }
    const std::string& name() const { return m_name; }
    HudJoystickButton* generateJoystickButton() const;
    
private:
    void setId(int id) { m_id = id; }
    void setName(const std::string& name) { m_name = name; }
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setBackgroundMeshRef(const std::string& backgroundMeshRef) { m_backgroundMeshRef = backgroundMeshRef; }
    void setAppearedPos(const Vector4& appearedPos) { m_appearedPos = appearedPos; }
    void setDisappearedPos(const Vector4& disappearedPos) { m_disappearedPos = disappearedPos; }
    void setAnimDuration(double animDuration) { m_animDuration = animDuration; }
    void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
    void setRadius(double radius) { m_radius = radius; }
    void setCanMoveHorz(bool canMoveHorz) { m_canMoveHorz = canMoveHorz; }
    void setCanMoveVert(bool canMoveVert) { m_canMoveVert = canMoveVert; }

private:
    int m_id;
    std::string m_name;
    std::string m_meshRef;
    std::string m_backgroundMeshRef;
    Vector4 m_appearedPos;
    Vector4 m_disappearedPos;
    double m_animDuration;
    double m_accelMagnitude;
    double m_radius;
    bool m_canMoveHorz;
    bool m_canMoveVert;
};