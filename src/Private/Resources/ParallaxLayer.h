#pragma once

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/AnimSceneActions/FaceStateParam.h>
#include <KYEngine/Private/Huds/HudMapView.h>
#include <KYEngine/Private/AnimSceneActions/MapItemParam.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <map>
#include <string>
#include <stdexcept>

class ParallaxLayer
    : public Entity
{
public:
    ParallaxLayer();
    ParallaxLayer(const ParallaxLayer& other);
    virtual ~ParallaxLayer();
    
public:
	static const std::string XML_NODE;
	static ParallaxLayer* readFromXml(TiXmlElement* node);
    
public:
    void load();
    void unload();

// Entity implementation
public:
    virtual Entity* cloneEntity() { throw std::runtime_error("AtrezzoResource: Entity cannot be cloned"); }
    virtual ParticleEmitterExtension* particleEmitterInterface() { return NULL; }
	virtual TextLayerExtension* textLayerInterface() { return NULL; }
    virtual AnimMeshExtension* animMeshInterface() { return NULL; }
    virtual const std::string& name() const { return m_name; }
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
    virtual void* userData() { return NULL; }

private:
	void draw();
       
public:
    double z() const { return m_z; }
    const std::string& meshRef() const { return m_meshRef; }
    Mesh* mesh() { return m_mesh; }
    double width() const { return m_width; }
    
private:
    void setName(const std::string name) { m_name = name; }
    void setZ(double z) { m_z = z; }
    void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setWidth(double width) { m_width = width; }
    
private:
    std::string m_name;
    double m_z;
    std::string m_meshRef;
    Mesh* m_mesh;
    mutable Box m_screenBounds;
    double m_width;
    RenderLayer* m_layer;
    Vector4 m_pos;
    Vector4 m_color;
    double m_angle;
    Vector4 m_scale;
    double m_alpha;
    double m_hpercent;
    bool m_useBlending;
    double m_fps;
};