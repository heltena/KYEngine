#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Box.h>
#include <KYEngine/Font.h>
#include <KYEngine/Private/Resources/EntityResource.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/TextLayerExtension.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>
#include <stdexcept>

#include <FTGL/ftgles.h>

class TextLayerEntityResource
	: public EntityResource
    , public TextLayerExtension
{
public:
	TextLayerEntityResource();
	virtual ~TextLayerEntityResource();
    
public:
	static const std::string XML_NODE;
	static TextLayerEntityResource* readFromXml(TiXmlElement* node);
	
// Resource implementation (partial in EntityImpl)
public:
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
// Entity implementation
public:
    virtual Entity* cloneEntity() { throw std::runtime_error("AtrezzoResource: Entity cannot be cloned"); }
	virtual ParticleEmitterExtension* particleEmitterInterface() { return NULL; }
    virtual TextLayerExtension* textLayerInterface() { return this; }
    virtual AnimMeshExtension* animMeshInterface() { return NULL; }
    void setLayer(RenderLayer* layer) { m_layer = layer; }
    const Vector4& pos() const { return m_pos; }
	void setPos(const Vector4& pos) { m_pos = pos; if (m_layer) m_layer->updateEntityPos(this); }
    double hpercent() const { return m_hpercent; }
    void setHpercent(double hpercent) { m_hpercent = hpercent; }
	const Box& screenBounds() const;
	Vector4& color() { return m_color; }
	void setColor(const Vector4& color) { m_color = color; }
    double angle() const { return m_angle; }
    void setAngle(double angle) { m_angle = angle; }
    Vector4& scale() { return m_scale; }
    void setScale(const Vector4& scale) { m_scale = scale; } 
    double alpha() const { return m_alpha; }
    void setAlpha(double alpha) { m_alpha = alpha; }
    bool useBlending() const { return m_useBlending; }
    void setUseBlending(bool useBlending) { m_useBlending = useBlending; }
	float fps() const { return 0; }
	void setFps(float fps) { }
	void setAnim(const std::string& animRef, double fps = 0) { }
	void update(const double elapsedTime);
	virtual void drawOpaque() { if (!m_useBlending) draw(); }
    virtual void drawSemiTransparent() { if (m_useBlending) draw(); }

private:
	void draw();
    
// TextLayerExtension implementation
public:
    virtual Entity* entity() { return this; }
	void setText(const std::string& text);
	void setFontRef(const std::string& fontRef) { m_fontRef = fontRef; m_updateData = true; }
	void setLineLength(double lineLength) { m_lineLength = lineLength; m_updateData = true; }
	void setLineSpacing(double lineSpacing) { m_lineSpacing = lineSpacing; m_updateData = true; }
	void setAlign(AlignType align) { m_align = align; m_updateData = true; }
    void setBorderColor(const Vector4& borderColor) { m_borderColor = borderColor; }
    void setPivot(const Vector4& pivot) { m_pivot = pivot; }

public:
	void setName(const std::string& name) { m_name = name; }
	void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
	void setDefaultText(const std::string& defaultText) { m_defaultText = defaultText; }
	
private:
    RenderLayer* m_layer;
	std::string m_fontRef;
	double m_lineLength;
	double m_lineSpacing;
	AlignType m_align;
	std::string m_defaultText;
    Vector4 m_pivot;
    Vector4 m_borderColor;
	Vector4 m_initialPos;
	mutable Box m_screenBounds;
	Vector4 m_pos;
    double m_hpercent;
	Vector4 m_color;
    double m_angle;
    Vector4 m_scale;
    double m_alpha;
    bool m_useBlending;
	Font* m_font;
	FTSimpleLayout* m_layout;
	std::string m_text;
    bool m_updateData;
};


