#pragma once

#include <KYEngine/AddFaceViewParam.h>
#include <KYEngine/Private/AnimSceneActions/FaceStateParam.h>
#include <KYEngine/Private/Huds/HudFaceView.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <list>
#include <string>

class AddFaceViewParamImpl
    : public AddFaceViewParam
{
public:
    AddFaceViewParamImpl();
    AddFaceViewParamImpl(const AddFaceViewParamImpl& other);
    virtual ~AddFaceViewParamImpl();
    
public:
	static const std::string XML_NODE;
	static AddFaceViewParamImpl* readFromXml(TiXmlElement* node);
    
public:
    const Vector4& appearedPos() const { return m_appearedPos; }
    const Vector4& disappearedPos() const { return m_disappearedPos; }
    double animDuration() const { return m_animDuration; }
    double accelMagnitude() const { return m_accelMagnitude; }
    double minValue() const { return m_minValue; }
    double maxValue() const { return m_maxValue; }
    double initialValue() const { return m_initialValue; }

// AddFaceViewParam implementation
public:
    int id() const { return m_id; }
    const std::string& name() const { return m_name; }
    HudFaceView* generateFaceView() const;
    
private:
    void setId(int id) { m_id = id; }
    void setName(const std::string& name) { m_name = name; }
    void setAppearedPos(const Vector4& appearedPos) { m_appearedPos = appearedPos; }
    void setDisappearedPos(const Vector4& disappearedPos) { m_disappearedPos = disappearedPos; }
    void setAnimDuration(double animDuration) { m_animDuration = animDuration; }
    void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
    void setMinValue(double minValue) { m_minValue = minValue; }
    void setMaxValue(double maxValue) { m_maxValue = maxValue; }
    void setInitialValue(double initialValue) { m_initialValue = initialValue; }
    void addFaceState(const FaceStateParam& faceState) { m_states.push_back(faceState); }

private:
    int m_id;
    std::string m_name;
    Vector4 m_appearedPos;
    Vector4 m_disappearedPos;
    double m_animDuration;
    double m_accelMagnitude;
    double m_minValue;
    double m_maxValue;
    double m_initialValue;
    std::list<FaceStateParam> m_states;
};