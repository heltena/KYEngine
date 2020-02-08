#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/Resources/EntityResource.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/RenderLayer.h>

#include <string>
#include <stdexcept>

class MeshEntityResource
	: public EntityResource
{
public:
	MeshEntityResource();
	virtual ~MeshEntityResource();
    
public:
	static const std::string XML_NODE;
	static MeshEntityResource* readFromXml(TiXmlElement* node);
	
// Resource implementation (partial in EntityImpl)
public:
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return m_mesh->userData(); }

// Entity implementation
public:
    virtual Entity* cloneEntity() { throw std::runtime_error("AtrezzoResource: Entity cannot be cloned"); }
    virtual ParticleEmitterExtension* particleEmitterInterface() { return NULL; }
	virtual TextLayerExtension* textLayerInterface() { return NULL; }
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
	float fps() const { return m_fps; }
	void setFps(float fps) { m_fps = fps; }
	void setAnim(const std::string& animRef, double fps = 0) { }
	void update(const double elapsedTime);
	virtual void drawOpaque() { if (!m_useBlending) draw(); }
    virtual void drawSemiTransparent() { if (m_useBlending) draw(); }
    
private:
	void draw();
    
public:
	void setName(const std::string& name) { m_name = name; }
	void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
	const std::string& meshName() const { return m_meshRef; }
	void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
	void setInitialHPercent(double initialHPercent) { m_initialHPercent = initialHPercent; }
    
private:
    RenderLayer* m_layer;
	std::string m_meshRef;
	float m_fps;
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
	Mesh* m_mesh;
};


