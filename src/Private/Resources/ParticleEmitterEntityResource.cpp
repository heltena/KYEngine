#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Optimizations/OptimizedMeshData.h>
#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Resources/ParticleEmitterEntityResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string ParticleEmitterEntityResource::XML_NODE = "particle-emitter-entity";

ParticleEmitterEntityResource* ParticleEmitterEntityResource::readFromXml(TiXmlElement* node)
{
    ParticleEmitterEntityResource* result = new ParticleEmitterEntityResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string meshRef = TiXmlHelper::readString(node, "mesh-ref", true);
	const Vector4 initialPos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", NO_READ, 0.0, 0.0, 0.0, 1.0);
    const Vector4 color = TiXmlHelper::readVector(node, "ir", "ig", "ib", "ia", NO_READ, 1.0, 1.0, 1.0, 1.0);
	double angle = TiXmlHelper::readDouble(node, "angle", false, 0);
    bool useBlending = TiXmlHelper::readBool(node, "use-blending", false, false);
    
    // Info for new particles
    
    int maxParticles = TiXmlHelper::readInt(node, "max-particles", true);
    double delayBetweenParticles = TiXmlHelper::readDouble(node, "delay-between-particles", false, 0.5);
    
    double newPartVelAngle = TiXmlHelper::readDouble(node, "new-vel-angle", true);
    double newPartVelAngleOffset = TiXmlHelper::readDouble(node, "new-vel-angle-offset", false, 0);
    double newPartVelMagnitude = TiXmlHelper::readDouble(node, "new-vel-magnitude", true);
    double newPartVelMagnitudeOffset = TiXmlHelper::readDouble(node, "new-vel-magnitude-offset", false, 0);
    
    double newPartScale = TiXmlHelper::readDouble(node, "new-scale", false, 0);
    double newPartScaleOffset = TiXmlHelper::readDouble(node, "new-scale-offset", false, 0);
    
    double newPartScaleVel = TiXmlHelper::readDouble(node, "new-scale-vel", false, 1);
    double newPartScaleVelOffset = TiXmlHelper::readDouble(node, "new-scale-vel-offset", false, 0);
    
    double newPartAlpha = TiXmlHelper::readDouble(node, "new-alpha", false, 1);
    double newPartAlphaOffset = TiXmlHelper::readDouble(node, "new-alpha-offset", false, 0);
    
    double newPartAlphaVel = TiXmlHelper::readDouble(node, "new-alpha-vel", false, -0.1);
    double newPartAlphaVelOffset = TiXmlHelper::readDouble(node, "new-alpha-vel-offset", false, 0);
    
    double newPartTimeout = TiXmlHelper::readDouble(node, "new-timeout", false, 1);
    double newPartTimeoutOffset = TiXmlHelper::readDouble(node, "new-timeout-offset", false, 0);
    
    double newPartAngle = TiXmlHelper::readDouble(node, "new-angle", false, 0);
    double newPartAngleOffset = TiXmlHelper::readDouble(node, "new-angle-offset", false, 0);
    
    double newPartAngularVel = TiXmlHelper::readDouble(node, "new-angular-vel", false, 0);
    double newPartAngularVelOffset = TiXmlHelper::readDouble(node, "new-angular-vel-offset", false, 0);
    
	result->setName(name);
	result->setMeshRef(meshRef);
	result->setInitialPos(initialPos);
    result->setColor(color);
    result->setAngle(angle);
    result->setUseBlending(useBlending);
    
	result->setMaxParticles(maxParticles);
    result->setDelayBetweenParticles(delayBetweenParticles);
    
    result->setNewPartVelAngle(newPartVelAngle);
    result->setNewPartVelAngleOffset(newPartVelAngleOffset);
    result->setNewPartVelMagnitude(newPartVelMagnitude);
    result->setNewPartVelMagnitudeOffset(newPartVelMagnitudeOffset);
    result->setNewPartScale(newPartScale);
    result->setNewPartScaleOffset(newPartScaleOffset);
    result->setNewPartScaleVel(newPartScaleVel);
    result->setNewPartScaleVelOffset(newPartScaleVelOffset);
    result->setNewPartAlpha(newPartAlpha);
    result->setNewPartAlphaOffset(newPartAlphaOffset);
    result->setNewPartAlphaVel(newPartAlphaVel);
    result->setNewPartAlphaVelOffset(newPartAlphaVelOffset);
    result->setNewPartTimeout(newPartTimeout);
    result->setNewPartTimeoutOffset(newPartTimeoutOffset);
    result->setNewPartAngle(newPartAngle);
    result->setNewPartAngleOffset(newPartAngleOffset);
    result->setNewPartAngularVel(newPartAngularVel);
    result->setNewPartAngularVelOffset(newPartAngularVelOffset);
    
	result->setName(name);
    
    return result;
}

ParticleEmitterEntityResource::ParticleEmitterEntityResource()
	: m_loaded(false)
    , m_layer(NULL)
    , m_hpercent(1)
    , m_color(1.0, 1.0, 1.0, 1.0)
    , m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
    , m_useTimeout(false)
    , m_finished(false)
    , m_paused(false)
{
}

ParticleEmitterEntityResource::ParticleEmitterEntityResource(const ParticleEmitterEntityResource& other)
    : EntityResource(other)
    , m_layer(other.m_layer)
    , m_loaded(other.m_loaded)
    , m_meshRef(other.m_meshRef)
    , m_initialPos(other.m_initialPos)
    
    , m_pos(other.m_pos)
    , m_hpercent(other.m_hpercent)
    , m_box(other.m_box)
    , m_color(other.m_color)
    , m_angle(other.m_angle)
    , m_scale(other.m_scale)
    , m_alpha(other.m_alpha)
    , m_useBlending(other.m_useBlending)
    
    , m_maxParticles(other.m_maxParticles)
    , m_delayBetweenParticles(other.m_delayBetweenParticles)
    
    , m_newPartVelAngle(other.m_newPartVelAngle)
    , m_newPartVelAngleOffset(other.m_newPartVelAngleOffset)
    , m_newPartVelMagnitude(other.m_newPartVelMagnitude)
    , m_newPartVelMagnitudeOffset(other.m_newPartVelMagnitudeOffset)
        
    , m_newPartScale(other.m_newPartScale)
    , m_newPartScaleOffset(other.m_newPartScaleOffset)
    
    , m_newPartScaleVel(other.m_newPartScaleVel)
    , m_newPartScaleVelOffset(other.m_newPartScaleVelOffset)
    
    , m_newPartAlpha(other.m_newPartAlpha)
    , m_newPartAlphaOffset(other.m_newPartAlphaOffset)
    
    , m_newPartAlphaVel(other.m_newPartAlphaVel)
    , m_newPartAlphaVelOffset(other.m_newPartAlphaVelOffset)

    , m_newPartTimeout(other.m_newPartTimeout)
    , m_newPartTimeoutOffset(other.m_newPartTimeoutOffset)
    
    , m_newPartAngle(other.m_newPartAngle)
    , m_newPartAngleOffset(other.m_newPartAngleOffset)
    
    , m_newPartAngularVel(other.m_newPartAngularVel)
    , m_newPartAngularVelOffset(other.m_newPartAngularVelOffset)

    , m_mesh(other.m_mesh)
    
    , m_infos(other.m_infos)
    , m_finished(other.m_finished)
    , m_useTimeout(other.m_useTimeout)
    , m_timeout(other.m_timeout)
    , m_createTimeout(other.m_createTimeout)
    , m_paused(other.m_paused)
{
}

ParticleEmitterEntityResource::~ParticleEmitterEntityResource()
{
}

void ParticleEmitterEntityResource::preload()
{
}

void ParticleEmitterEntityResource::unloadFromPreloaded()
{
}

void ParticleEmitterEntityResource::load()
{
	m_mesh = Core::resourceManager().mesh(m_meshRef);
}

void ParticleEmitterEntityResource::unload()
{
    m_mesh = NULL;
}

void ParticleEmitterEntityResource::update(const double elapsedTime)
{
    if (m_paused)
        return;

    if (m_useTimeout)
        m_timeout -= elapsedTime;
    
    m_createTimeout -= elapsedTime;
    if ((!m_useTimeout || m_timeout >= 0) && m_createTimeout < 0 && m_infos.size() < m_maxParticles) {
        m_createTimeout = m_delayBetweenParticles;
        
        double degrees = Math::randomWithOffset(m_newPartVelAngle, m_newPartVelAngleOffset);
        double radians = degrees * M_PI / 180.0;
        double magnitude = Math::randomWithOffset(m_newPartVelMagnitude, m_newPartVelMagnitudeOffset);
        Vector4 vel = Vector4::fromPolar2D(radians, magnitude);
        double scale = Math::randomWithOffset(m_newPartScale, m_newPartScaleVel);
        double scaleVel = Math::randomWithOffset(m_newPartScaleVel, m_newPartScaleVelOffset);
        double alpha = Math::randomWithOffset(m_newPartAlpha, m_newPartAlphaOffset);
        double alphaVel = Math::randomWithOffset(m_newPartAlphaVel, m_newPartAlphaVelOffset);
        double timeout = Math::randomWithOffset(m_newPartTimeout, m_newPartTimeoutOffset);
        double angle = Math::randomWithOffset(m_newPartAngle, m_newPartAngleOffset) + degrees;
        double angularVel = Math::randomWithOffset(m_newPartAngularVel, m_newPartAngularVelOffset);
        
        ParticleInfo info;
        info.init(m_pos, vel, scale, scaleVel, alpha, alphaVel, timeout, angle, angularVel);
        m_infos.push_back(info);
    }

    std::list<ParticleInfo>::iterator it = m_infos.begin();
    while (it != m_infos.end()) {
        it->update(elapsedTime);
        if (it->isFinished()) {
            std::list<ParticleInfo>::iterator toKill = it++;
            m_infos.erase(toKill);
        } else
            it++;
    }
}

void ParticleEmitterEntityResource::draw()
{
    for(std::list<ParticleInfo>::iterator it = m_infos.begin(); it != m_infos.end(); it++) {
        const ParticleInfo& info = *it;
        glPushMatrix();
        glTranslatef(info.pos()[0], info.pos()[1], info.pos()[2]);
        glRotatef(info.angle(), 0, 0, 1);
        glColor4f(m_color[0], m_color[1], m_color[2], m_color[3] * info.alpha());
        glScalef(info.scale(), info.scale(), 1);
        m_mesh->draw(1);
        glPopMatrix();
    }
}

ParticleEmitterExtension* ParticleEmitterEntityResource::clone()
{
    ParticleEmitterEntityResource* newEmitter = new ParticleEmitterEntityResource(*this);
    return newEmitter;
}

void ParticleEmitterEntityResource::start()
{
    start(m_initialPos);
}

void ParticleEmitterEntityResource::start(double timeout)
{
    start(timeout, m_initialPos);
}

void ParticleEmitterEntityResource::start(const Vector4& pos)
{
    m_useTimeout = false;
    m_pos = pos;
    m_infos.clear();
    m_createTimeout = 0;
    m_finished = false;
    m_paused = false;
}

void ParticleEmitterEntityResource::start(double timeout, const Vector4& pos)
{
    m_useTimeout = true;
    m_timeout = timeout;
    m_pos = pos;
    m_infos.clear();
    m_createTimeout = 0;
    m_finished = false;
    m_paused = false;
}

void ParticleEmitterEntityResource::stop()
{
    m_finished = true;
}

void ParticleEmitterEntityResource::pause()
{
    m_paused = true;
}

void ParticleEmitterEntityResource::resume()
{
    m_paused = false;
}

bool ParticleEmitterEntityResource::isFinished() const
{
    return (m_useTimeout && m_timeout <= 0) || m_finished;
}
