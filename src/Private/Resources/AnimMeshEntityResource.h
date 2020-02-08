#pragma once

#include <tinyxml.h>

#include <KYEngine/AnimMeshCollection.h>
#include <KYEngine/AnimMeshExtension.h>
#include <KYEngine/AnimMeshInfo.h>
#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/Resources/EntityResource.h>
#include <KYEngine/RenderLayer.h>

#include <string>
#include <stdexcept>

class AnimMeshEntityResource
    : public EntityResource
    , public AnimMeshExtension
{
public:
	AnimMeshEntityResource();
	virtual ~AnimMeshEntityResource();
    
public:
	static const std::string XML_NODE;
	static AnimMeshEntityResource* readFromXml(TiXmlElement* node);
	
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
    virtual TextLayerExtension* textLayerInterface() { return NULL; }
    virtual AnimMeshExtension* animMeshInterface() { return this; }
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
	virtual void setAnim(const std::string& animRef, double fps = 0);
	void update(const double elapsedTime);
	virtual void drawOpaque() { if (!m_useBlending) draw(); }
    virtual void drawSemiTransparent() { if (m_useBlending) draw(); }

// AnimMeshExtension implementation
public:
    virtual Entity* entity() { return this; }
    virtual const std::string animRef() const { return m_currentAnimRef; }
    virtual double fps() const { return m_fps; }
    virtual bool isFinished() const { return m_finished; }
    virtual double loopDuration() const { return loopDuration(m_fps); }
    virtual double loopDuration(double fps) const;

private:
    void draw();
    
public:
	void setName(const std::string& name) { m_name = name; }
	void setAnimMeshCollectionRef(const std::string& animMeshCollectionRef) { m_animMeshCollectionRef = animMeshCollectionRef; }
	const std::string& animMeshCollectionRef() const { return m_animMeshCollectionRef; }
	void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
	void setInitialHPercent(double initialHPercent) { m_initialHPercent = initialHPercent; }
    
private:
    RenderLayer* m_layer;
	std::string m_animMeshCollectionRef;
	mutable Box m_screenBounds;
	Vector4 m_pos;
    double m_hpercent;
	Vector4 m_color;
    double m_angle;
    Vector4 m_scale;
    double m_alpha;
    bool m_useBlending;
	Vector4 m_initialPos;
    double m_initialHPercent;
    
	AnimMeshCollection* m_animMeshCollection;

	std::string m_currentAnimRef;
	bool m_finished;
	AnimMeshInfo* m_currentMesh;
    double m_fps;
	int m_currentFrame;
	float m_frameElapsedTime;
};


