#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Font.h>
#include <KYEngine/Private/Resources/Resource.h>

#include <string>

#include <cstdio>
#include <FTGL/ftgles.h>

class FontResource
	: public Resource
	, public Font
{
public:
	FontResource();
	virtual ~FontResource();
    
public:
	static const std::string XML_NODE;
	static FontResource* readFromXml(TiXmlElement* node);
	
// Resource implementation
public:
	const std::string& name() const { return m_name; }
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }

// Font implementation
public:
	const void* internalData() const { return m_data; }
    const void* internalBorderData() const { return m_borderData; }
	double faceSize() const { return m_faceSize; }
	bool hasBorder() const { return m_hasBorder; }
    double borderOutset() const { return m_borderOutset; }
    
private:
	void setName(const std::string& name) { m_name = name; }
	void setFilename(const std::string& filename) { m_filename = filename; }
	void setFaceSize(double faceSize) { m_faceSize = faceSize; }
	void setHasBorder(bool hasBorder) { m_hasBorder = hasBorder; }
    void setBorderOutset(double borderOutset) { m_borderOutset = borderOutset; }
    
protected:
	bool m_loaded;
	std::string m_name;
	std::string m_filename;
	double m_faceSize;
    bool m_hasBorder;
    double m_borderOutset;
    
	FTFont *m_data;
    FTFont *m_borderData;
};


