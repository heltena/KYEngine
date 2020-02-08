#pragma once

#include <tinyxml.h>

#include <string>

class FaceStateParam
{
public:
    FaceStateParam();
    FaceStateParam(const FaceStateParam& other);
    virtual ~FaceStateParam();
    
public:
	static const std::string XML_NODE;
	static FaceStateParam* readFromXml(TiXmlElement* node);
    
public:
    double forLessThan() const { return m_forLessThan; }
    const std::string& meshRef() const { return m_meshRef; }
    
private:
    void setForLessThan(double forLessThan) { m_forLessThan = forLessThan; }
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    
private:
    double m_forLessThan;
    std::string m_meshRef;
};