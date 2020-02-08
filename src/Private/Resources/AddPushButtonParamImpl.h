#pragma once

#include <KYEngine/AddPushButtonParam.h>
#include <KYEngine/Private/Huds/HudPushButton.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <string>

class AddPushButtonParamImpl
    : public AddPushButtonParam
{
public:
    AddPushButtonParamImpl();
    AddPushButtonParamImpl(const AddPushButtonParamImpl& other);
    virtual ~AddPushButtonParamImpl();
    
public:
	static const std::string XML_NODE;
	static AddPushButtonParamImpl* readFromXml(TiXmlElement* node);

public:
    const std::string& meshRef() const { return m_meshRef; }
    const std::string& overMeshRef() const { return m_overMeshRef; }
    const Vector4& appearedPos() const { return m_appearedPos; }
    const Vector4& disappearedPos() const { return m_disappearedPos; }
    double animDuration() const { return m_animDuration; }
    double accelMagnitude() const { return m_accelMagnitude; }
    double radius() const { return m_radius; }
  
// AddPushButtonParam implementation
public:
    int id() const { return m_id; }
    const std::string& name() const { return m_name; }
    HudPushButton* generatePushButton() const;
    
private:
    void setId(int id) { m_id = id; }
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setOverMeshRef(const std::string& overMeshRef) { m_overMeshRef = overMeshRef; }
    void setAppearedPos(const Vector4& appearedPos) { m_appearedPos = appearedPos; }
    void setDisappearedPos(const Vector4& disappearedPos) { m_disappearedPos = disappearedPos; }
    void setAnimDuration(double animDuration) { m_animDuration = animDuration; }
    void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
    void setRadius(double radius) { m_radius = radius; }
    
private:
    int m_id;
    std::string m_name;
    std::string m_meshRef;
    std::string m_overMeshRef;
    Vector4 m_appearedPos;
    Vector4 m_disappearedPos;
    double m_animDuration;
    double m_accelMagnitude;
    double m_radius;
};