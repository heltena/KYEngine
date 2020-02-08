#pragma once

#include <KYEngine/Atrezzo.h>
#include <KYEngine/Entity.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/Private/Resources/Resource.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>
#include <stdexcept>

class AtrezzoResource
	: public Atrezzo
    , public Entity
    , public Resource
{
public:
	AtrezzoResource();
	virtual ~AtrezzoResource();
	
// Resource partial implementation
public:
	const std::string& name() const { return m_name; }
    virtual void preload() = 0;
    virtual void unloadFromPreloaded() = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
	void* userData() = 0;

// Entity partial implementation
public:
    virtual Entity* cloneEntity() { throw std::runtime_error("AtrezzoResource: Entity cannot be cloned"); }
    virtual ParticleEmitterExtension* particleEmitterInterface() { return NULL; }
    virtual TextLayerExtension* textLayerInterface() { return NULL; }
    virtual AnimMeshExtension* animMeshInterface() { return NULL; }
    virtual void setLayer(RenderLayer* layer) { m_layer = layer; }
    virtual const Vector4& pos() const { return m_pos; }
	virtual void setPos(const Vector4& pos) { m_pos = pos; if (m_layer) m_layer->updateEntityPos(this); setCameraPos(m_cameraPos); }
    virtual double hpercent() const { return m_hpercent; }
    virtual void setHpercent(double hpercent) { m_hpercent = hpercent; }
	virtual const Box& screenBounds() const = 0;
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
	virtual void setAnim(const std::string& animRef, double fps = 0) { }
	virtual void update(const double elapsedTime) = 0;
	virtual void drawOpaque() = 0;
    virtual void drawSemiTransparent() = 0;
    
// Atrezzo partial implementation
public:
    virtual Entity* asEntity() { return this; }
    virtual void setCameraPos(const Vector4& cameraPos) { m_cameraPos = cameraPos; }
    virtual const Vector4& cameraPos() const { return m_cameraPos; }

protected:
	void setName(const std::string& name) { m_name = name; }
	
protected:
    RenderLayer* m_layer;
	bool m_loaded;
	std::string m_name;
    Vector4 m_cameraPos;
    
    Vector4 m_pos;
    double m_hpercent;
    Vector4 m_color;
    double m_angle;
    Vector4 m_scale;
    double m_alpha;
    bool m_useBlending;
};
