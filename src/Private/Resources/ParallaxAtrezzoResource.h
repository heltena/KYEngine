#pragma once

#include <tinyxml.h>

#include <KYEngine/Private/Resources/AtrezzoResource.h>
#include <KYEngine/Private/Resources/ParallaxLayer.h>
#include <KYEngine/Utility/Box.h>

#include <list>
#include <string>

class ParallaxAtrezzoResource
	: public AtrezzoResource
{
public:
	ParallaxAtrezzoResource();
	virtual ~ParallaxAtrezzoResource();
    
public:
	static const std::string XML_NODE;
	static ParallaxAtrezzoResource* readFromXml(TiXmlElement* node);
	
// Resource implementation (partial in AtrezzoResource)
public:
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }

// Entity implementation (partial in AtrezzoResource)
public:
    virtual void setLayer(RenderLayer* layer);
	virtual const Box& screenBounds() const { return m_screenBounds; }
    virtual void setScale(const Vector4& scale);
	virtual void update(const double elapsedTime);
	virtual void drawOpaque();
	virtual void drawSemiTransparent();

// Atrezzo implementation (partial in AtrezzoResource)
public:
    virtual void setCameraPos(const Vector4& cameraPos);
    virtual Vector4 atrezzoToScreen(const Vector4& atrezzoPos, double extraInfo = 0); // extraInfo = layerWidth

public:
	void setName(const std::string& name) { m_name = name; }
    void setWidth(double width) { m_width = width; }
    void addLayer(ParallaxLayer* layer) { m_layers.push_back(layer); }
	
private:
    Box m_screenBounds;
    double m_width;
	std::list<ParallaxLayer*> m_layers;
};


