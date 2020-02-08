#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Private/Resources/EntityResource.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/ParticleEmitterExtension.h>
#include <KYEngine/Private/Resources/ParticleInfo.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/Private/Resources/Resource.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>
#include <stdexcept>

class ParticleEmitterEntityResource
	: public EntityResource
    , public ParticleEmitterExtension
{
public:
	ParticleEmitterEntityResource();
    ParticleEmitterEntityResource(const ParticleEmitterEntityResource& other);
	virtual ~ParticleEmitterEntityResource();
    
public:
	static const std::string XML_NODE;
	static ParticleEmitterEntityResource* readFromXml(TiXmlElement* node);
	
// Resource implementation
public:
	void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
// Entity implementation
public:
    virtual Entity* cloneEntity() { throw std::runtime_error("AtrezzoResource: Entity cannot be cloned"); }
    virtual ParticleEmitterExtension* particleEmitterInterface() { return this; }
    virtual TextLayerExtension* textLayerInterface() { return NULL; }
    virtual AnimMeshExtension* animMeshInterface() { return NULL; }
    virtual void setLayer(RenderLayer* layer) { m_layer = layer; }
	const Vector4& pos() const { return m_pos; }
	void setPos(const Vector4& pos) { m_pos = pos; if (m_layer) m_layer->updateEntityPos(this); }
    double hpercent() const { return m_hpercent; }
    void setHpercent(double hpercent) { m_hpercent = hpercent; }
	const Box& screenBounds() const { return m_box; }
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
	float fps() const { return 1; }
	void setFps(float fps) { }
	void setAnim(const std::string& animRef, double fps = 0) { }
	void update(const double elapsedTime);
	virtual void drawOpaque() { if (!m_useBlending) draw(); }
    virtual void drawSemiTransparent() { if (m_useBlending) draw(); }

private:
	void draw();
    
// ParticleEmitterExtension implementation
public:
    Entity* entity() { return this; }
    ParticleEmitterExtension* clone();
    void start();
    void start(double timeout);
    void start(const Vector4& pos);
    void start(double timeout, const Vector4& pos);
    void stop();
    virtual bool isPaused() const { return m_paused; }
    virtual void pause();
    virtual void resume();
    bool isFinished() const;

private:
	void setName(const std::string& name) { m_name = name; }
	void setMeshRef(const std::string& meshRef) { m_meshRef = meshRef; }
    void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
    void setMaxParticles(const int maxParticles) { m_maxParticles = maxParticles; }
    void setDelayBetweenParticles(const double delayBetweenParticles) { m_delayBetweenParticles = delayBetweenParticles; }
    void setNewPartVelAngle(const double newPartVelAngle) { m_newPartVelAngle = newPartVelAngle; }
    void setNewPartVelAngleOffset(const double newPartVelAngleOffset) { m_newPartVelAngleOffset = newPartVelAngleOffset; }
    void setNewPartVelMagnitude(const double newPartVelMagnitude) { m_newPartVelMagnitude = newPartVelMagnitude; }
    void setNewPartVelMagnitudeOffset(const double newPartVelMagnitudeOffset) { m_newPartVelMagnitudeOffset = newPartVelMagnitudeOffset; }
    void setNewPartScale(const double newPartScale) { m_newPartScale = newPartScale; }
    void setNewPartScaleOffset(const double newPartScaleOffset) { m_newPartScaleOffset = newPartScaleOffset; }
    void setNewPartScaleVel(const double newPartScaleVel) { m_newPartScaleVel = newPartScaleVel; }
    void setNewPartScaleVelOffset(const double newPartScaleVelOffset) { m_newPartScaleVelOffset = newPartScaleVelOffset; }
    void setNewPartAlpha(const double newPartAlpha) { m_newPartAlpha = newPartAlpha; }
    void setNewPartAlphaOffset(const double newPartAlphaOffset) { m_newPartAlphaOffset = newPartAlphaOffset; }
    void setNewPartAlphaVel(const double newPartAlphaVel) { m_newPartAlphaVel = newPartAlphaVel; }
    void setNewPartAlphaVelOffset(const double newPartAlphaVelOffset) { m_newPartAlphaVelOffset = newPartAlphaVelOffset; }
    void setNewPartTimeout(const double newPartTimeout) { m_newPartTimeout = newPartTimeout; }
    void setNewPartTimeoutOffset(const double newPartTimeoutOffset) { m_newPartTimeoutOffset = newPartTimeoutOffset; }
    void setNewPartAngle(const double newPartAngle) { m_newPartAngle = newPartAngle; }
    void setNewPartAngleOffset(const double newPartAngleOffset) { m_newPartAngleOffset = newPartAngleOffset; }
    void setNewPartAngularVel(const double newPartAngularVel) { m_newPartAngularVel = newPartAngularVel; }
    void setNewPartAngularVelOffset(const double newPartAngularVelOffset) { m_newPartAngularVelOffset = newPartAngularVelOffset; }
    
protected:
    RenderLayer* m_layer;
	bool m_loaded;
	std::string m_meshRef;
    Vector4 m_initialPos;
    
    Vector4 m_pos;
    double m_hpercent;
    Box m_box;
    Vector4 m_color;
    double m_angle;
    Vector4 m_scale;
    double m_alpha;
    bool m_useBlending;

    int m_maxParticles;
    double m_delayBetweenParticles;
    
    double m_newPartVelAngle; // Polar coordinates
    double m_newPartVelAngleOffset;
    double m_newPartVelMagnitude;
    double m_newPartVelMagnitudeOffset; // Randomized
    
    double m_newPartScale;
    double m_newPartScaleOffset;
    
    double m_newPartScaleVel;
    double m_newPartScaleVelOffset;
    
    double m_newPartAlpha;
    double m_newPartAlphaOffset;
    
    double m_newPartAlphaVel;
    double m_newPartAlphaVelOffset;
    
    double m_newPartTimeout;
    double m_newPartTimeoutOffset;
    
    double m_newPartAngle;
    double m_newPartAngleOffset;
    
    double m_newPartAngularVel;
    double m_newPartAngularVelOffset;

    Mesh* m_mesh;
    
    std::list<ParticleInfo> m_infos;
    bool m_finished;
    bool m_useTimeout;
    double m_timeout;
    double m_createTimeout;
    bool m_paused;
};
