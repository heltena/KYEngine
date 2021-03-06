#pragma once

#include <KYEngine/AddProgressViewParam.h>
#include <KYEngine/Private/Huds/HudProgressView.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <string>

class AddProgressViewParamImpl
    : public AddProgressViewParam
{
public:
    AddProgressViewParamImpl();
    AddProgressViewParamImpl(const AddProgressViewParamImpl& other);
    virtual ~AddProgressViewParamImpl();
    
public:
	static const std::string XML_NODE;
	static AddProgressViewParamImpl* readFromXml(TiXmlElement* node);
    
public:
    const std::string& backgroundMeshRef() const { return m_backgroundMeshRef; }
    const std::string& meshRef() const { return m_meshRef; }
    const Vector4& appearedPos() const { return m_appearedPos; }
    const Vector4& disappearedPos() const { return m_disappearedPos; }
    const Vector4& offset() const { return m_offset; }
    double animDuration() const { return m_animDuration; }
    double accelMagnitude() const { return m_accelMagnitude; }
    double minValue() const { return m_minValue; }
    double maxValue() const { return m_maxValue; }
    double initialValue() const { return m_initialValue; }
    bool ltr() const { return m_ltr; }
    double angle() const { return m_angle; }
    
// AddProgressViewParam implementation
public:
    int id() const { return m_id; }
    const std::string& name() const { return m_name; }
    HudProgressView* generateProgressView() const;
    
private:
    void setId(int id) { m_id = id; }
    void setBackgroundMeshRef(const std::string& backgroundMeshRef) { m_backgroundMeshRef = backgroundMeshRef; }
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setAppearedPos(const Vector4& appearedPos) { m_appearedPos = appearedPos; }
    void setDisappearedPos(const Vector4& disappearedPos) { m_disappearedPos = disappearedPos; }
    void setOffset(const Vector4& offset) { m_offset = offset; }
    void setAnimDuration(double animDuration) { m_animDuration = animDuration; }
    void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
    void setMinValue(double minValue) { m_minValue = minValue; }
    void setMaxValue(double maxValue) { m_maxValue = maxValue; }
    void setInitialValue(double initialValue) { m_initialValue = initialValue; }
    void setLtr(bool ltr) { m_ltr = ltr; }
    void setAngle(double angle) { m_angle = angle; }
    
private:
    int m_id;
    std::string m_name;
    std::string m_backgroundMeshRef;
    std::string m_meshRef;
    Vector4 m_appearedPos;
    Vector4 m_disappearedPos;
    Vector4 m_offset;
    double m_animDuration;
    double m_accelMagnitude;
    double m_minValue;
    double m_maxValue;
    double m_initialValue;
    bool m_ltr;
    double m_angle;
};