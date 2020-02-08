#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Font.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

#include <FTGL/ftgles.h>

class StaticTextMeshResource
	: public MeshResource
{
public:
	StaticTextMeshResource();
	virtual ~StaticTextMeshResource();
    
public:
	static const std::string XML_NODE;
	static StaticTextMeshResource* readFromXml(TiXmlElement* node);
	
// Resource implementation (partial in EntityImpl)
public:
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
// Mesh implementation
public:
	int frameCount() const { return 1; }
	void draw(double hpercent, int frame = 0);
	const Box& boundingBox() const { return m_boundingBox; }
    void addMeshDataTo(OptimizedMeshData& data);
	
public:
	void setName(const std::string& name) { m_name = name; }
	void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; }
	void setLineLength(double lineLength) { m_lineLength = lineLength; }
	void setLineSpacing(double lineSpacing) { m_lineSpacing = lineSpacing; }
	void setAlign(AlignType align) { m_align = align; }
	void setInitialText(const std::string& initialText) { m_initialText = initialText; }
    void setColor(const Vector4& color) { m_color = color; }
    void setBorderColor(const Vector4& borderColor) { m_borderColor = borderColor; }
	
private:
	std::string m_fontRef;
	double m_lineLength;
	double m_lineSpacing;
	AlignType m_align;
    Vector4 m_color;
	Vector4 m_borderColor;
	mutable Box m_boundingBox;
	Font* m_font;
	FTSimpleLayout* m_layout;
    std::string m_initialText;
	std::string m_text;
};


