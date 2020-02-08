#pragma once

#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Font.h>
#include <KYEngine/Private/Huds/HudAnimations.h>
#include <KYEngine/RenderLayer.h>

#include <string>
#include <stdexcept>

#include <FTGL/ftgles.h>

class HudTextLabel
    : public Entity
{
public:
    HudTextLabel();
    HudTextLabel(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, Font* font, const std::string& defaultText, const Vector4& color, const Vector4& borderColor, double lineLength, double lineSpacing, AlignType align);
    virtual ~HudTextLabel();
    
private:
    HudTextLabel(const HudTextLabel& other);
    
// Entity implementation
public:
    virtual Entity* cloneEntity() { throw std::runtime_error("AtrezzoResource: Entity cannot be cloned"); }
    virtual ParticleEmitterExtension* particleEmitterInterface() { return NULL; }
    virtual TextLayerExtension* textLayerInterface() { return NULL; }
    virtual AnimMeshExtension* animMeshInterface() { return NULL; }
    virtual const std::string& name() const { return m_name; }
    virtual void setLayer(RenderLayer* layer) { m_layer = layer; }
    virtual const Vector4& pos() const { return m_pos; } 
	virtual void setPos(const Vector4& pos) { m_pos = pos; if (m_layer) m_layer->updateEntityPos(this); }
    double hpercent() const { return m_hpercent; }
    void setHpercent(double hpercent) { m_hpercent = hpercent; }
	virtual const Box& screenBounds() const { return m_bounds; }
	virtual Vector4& color() { return m_color; }
	virtual void setColor(const Vector4& color) { m_color = color; }
    virtual double angle() const { return m_angle; }
    virtual void setAngle(double angle) { m_angle = angle; }
    virtual Vector4& scale() { return m_scale; }
    virtual void setScale(const Vector4& scale) { m_scale = scale; } 
    virtual double alpha() const { return m_alpha; }
    virtual void setAlpha(double alpha) { m_alpha = alpha; }
    virtual bool useBlending() const { return m_useBlending; }
    virtual void setUseBlending(bool useBlending) { m_useBlending = useBlending; }
	virtual float fps() const { return 1; }
	virtual void setFps(float fps) { }
	virtual void setAnim(const std::string& animRef, double fps = 0) { }
	virtual void update(const double elapsedTime);
	virtual void drawOpaque() { if (!m_useBlending) draw(); }
    virtual void drawSemiTransparent() { if (m_useBlending) draw(); }
    virtual void* userData() { return 0; }

private:
	virtual void draw();

public:
    int id() const { return m_id; }
    virtual void appear();
    virtual bool isAppeared() const;
    virtual void disappear();
    virtual bool isDisappeared() const; 
    void setBorderColor(const Vector4& borderColor) { m_borderColor = borderColor; }
    const Vector4& borderColor() const { return m_borderColor; }
	virtual void setText(const std::string& text) { if (m_text != text) m_text = text; }

private:
    RenderLayer* m_layer;
    Vector4 m_appearedPos;
    Vector4 m_disappearedPos;
    Vector4 m_offset;
    double m_animDuration;
    double m_accelMagnitude;
    double m_lineLength;
    double m_lineSpacing;
    AlignType m_align;
    HudAnimations m_animation;
    double m_elapsedTime;
    
    int m_id;
    std::string m_name;
    Vector4 m_pos;
    double m_hpercent;
    Box m_bounds;
    Vector4 m_color;
    Vector4 m_borderColor;
    double m_angle;
    Vector4 m_scale;
    double m_alpha;
    bool m_useBlending;
    Vector4 m_fromPos;
    Vector4 m_toPos;

    FTSimpleLayout* m_layout;
	Font* m_font;
    std::string m_text;
};