#pragma once

#include <tinyxml.h>

#include <string>

class MapItemParam
{
public:
    MapItemParam();
    MapItemParam(const MapItemParam& other);
    virtual ~MapItemParam();
    
public:
	static const std::string XML_NODE;
	static MapItemParam* readFromXml(TiXmlElement* node);
    
public:
    int id() const { return m_id; }
    const std::string& leftMeshRef() const { return m_leftMeshRef; }
    const std::string& rightMeshRef() const { return m_rightMeshRef; }
    
private:
    void setId(int id) { m_id = id; }
    void setLeftMeshRef(const std::string& leftMeshRef) { m_leftMeshRef = leftMeshRef; }
    void setRightMeshRef(const std::string& rightMeshRef) { m_rightMeshRef = rightMeshRef; }
    
private:
    int m_id;
    std::string m_leftMeshRef;
    std::string m_rightMeshRef;
};