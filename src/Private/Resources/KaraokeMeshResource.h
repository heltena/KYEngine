#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Font.h>
#include <KYEngine/Private/Resources/KaraokeInfo.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <list>
#include <string>
#include <vector>

#include <cstdio>
#include <FTGL/ftgles.h>

class KaraokeMeshResource
	: public MeshResource
{
public:
	KaraokeMeshResource();
	virtual ~KaraokeMeshResource();
    
public:
	static const std::string XML_NODE;
	static KaraokeMeshResource* readFromXml(TiXmlElement* node);
	
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
    void setColor(const Vector4& color) { m_color = color; }
    void setBorderColor(const Vector4& borderColor) { m_borderColor = borderColor; }
    void setAnimDuration(double animDuration) { m_animDuration = animDuration; }
    void setAnimOffset(const Vector4& animOffset) { m_animOffset = animOffset; }
    void addPhrase(const KaraokeInfo& phrase) { m_initialPhrases.push_back(phrase); }

private:
    int findTextIndex(double time, int begin, int end);
    
private:
	std::string m_fontRef;
	double m_lineLength;
	double m_lineSpacing;
	AlignType m_align;
    Vector4 m_color;
	Vector4 m_borderColor;
    double m_animDuration;
    Vector4 m_animOffset;
    std::list<KaraokeInfo> m_initialPhrases;
    std::vector<KaraokeInfo> m_phrases;
	mutable Box m_boundingBox;
	Font* m_font;
	FTSimpleLayout* m_layout;
	std::string m_text;
    std::string m_renderText;
    int m_currentIndex;
};


