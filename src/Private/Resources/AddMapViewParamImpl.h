#pragma once

#include <KYEngine/AddMapViewParam.h>
#include <KYEngine/Private/AnimSceneActions/FaceStateParam.h>
#include <KYEngine/Private/Huds/HudMapView.h>
#include <KYEngine/Private/AnimSceneActions/MapItemParam.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <map>
#include <string>

class AddMapViewParamImpl
    : public AddMapViewParam
{
public:
    AddMapViewParamImpl();
    AddMapViewParamImpl(const AddMapViewParamImpl& other);
    virtual ~AddMapViewParamImpl();
    
public:
	static const std::string XML_NODE;
	static AddMapViewParamImpl* readFromXml(TiXmlElement* node);
    
public:
    const std::string& backgroundMeshRef() const { return m_backgroundMeshRef; }
    const std::string& meshRef() const { return m_meshRef; }
    const std::string& centerMeshRef() const { return m_centerMeshRef; }
    const Vector4& appearedPos() const { return m_appearedPos; }
    const Vector4& disappearedPos() const { return m_disappearedPos; }
    const Vector4& offset() const { return m_offset; }
    double animDuration() const { return m_animDuration; }
    double accelMagnitude() const { return m_accelMagnitude; }
    double width() const { return m_width; }
    double minValue() const { return m_minValue; }
    double maxValue() const { return m_maxValue; }
    
// AddMapViewParam implementation
public:
    int id() const { return m_id; }
    const std::string& name() const { return m_name; }
    HudMapView* generateMapView() const;
    
private:
    void setId(int id) { m_id = id; }
    void setName(const std::string& name) { m_name = name; }
    void setBackgroundMeshRef(const std::string& backgroundMeshRef) { m_backgroundMeshRef = backgroundMeshRef; }
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setHasCenterMeshRef(bool hasCenterMeshRef) { m_hasCenterMeshRef = hasCenterMeshRef; }
    void setCenterMeshRef(const std::string& centerMeshRef) { m_centerMeshRef = centerMeshRef; }
    void setAppearedPos(const Vector4& appearedPos) { m_appearedPos = appearedPos; }
    void setDisappearedPos(const Vector4& disappearedPos) { m_disappearedPos = disappearedPos; }
    void setOffset(const Vector4& offset) { m_offset = offset; }
    void setAnimDuration(double animDuration) { m_animDuration = animDuration; }
    void setAccelMagnitude(double accelMagnitude) { m_accelMagnitude = accelMagnitude; }
    void setWidth(double width) { m_width = width; }
    void setMinValue(double minValue) { m_minValue = minValue; }
    void setMaxValue(double maxValue) { m_maxValue = maxValue; }
    void addMapItem(const MapItemParam& mapItem) { m_items[mapItem.id()] = mapItem; }
    
private:
    std::string m_name;
    int m_id;
    std::string m_backgroundMeshRef;
    std::string m_meshRef;
    bool m_hasCenterMeshRef;
    std::string m_centerMeshRef;
    Vector4 m_appearedPos;
    Vector4 m_disappearedPos;
    Vector4 m_offset;
    double m_animDuration;
    double m_accelMagnitude;
    double m_width;
    double m_minValue;
    double m_maxValue;
    
    std::map<int, MapItemParam> m_items;
};