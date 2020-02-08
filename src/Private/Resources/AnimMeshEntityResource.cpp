#include <KYEngine/Private/Resources/AnimMeshEntityResource.h>
#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Utility/Vector4.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>

const std::string AnimMeshEntityResource::XML_NODE = "anim-mesh-entity";

AnimMeshEntityResource* AnimMeshEntityResource::readFromXml(TiXmlElement* node)
{
    AnimMeshEntityResource* result = new AnimMeshEntityResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string animMeshCollectionRef = TiXmlHelper::readString(node, "anim-mesh-collection-ref", true);
	const Vector4 initialPos = TiXmlHelper::readVector(node, "ix", "iy", "iz", "", NO_READ, 0.0, 0.0, 0.0, 1.0);
    const double initialHPercent = TiXmlHelper::readDouble(node, "ihpercent", false, 1);
    const Vector4 color = TiXmlHelper::readVector(node, "ir", "ig", "ib", "ia", NO_READ, 1.0, 1.0, 1.0, 1.0);
    const Vector4 scale = TiXmlHelper::readVector(node, "sx", "sy", "sz", "", NO_READ, 1.0, 1.0, 1.0, 1.0);
    const bool useBlending = TiXmlHelper::readBool(node, "use-blending", false, false);
    
	result->setName(name);
	result->setAnimMeshCollectionRef(animMeshCollectionRef);
	result->setInitialPos(initialPos);
    result->setInitialHPercent(initialHPercent);
    result->setColor(color);
    result->setScale(scale);
    result->setUseBlending(useBlending);
    
    return result;
}

AnimMeshEntityResource::AnimMeshEntityResource()
    : m_layer(NULL)
    , m_hpercent(1)
    , m_color(1.0, 1.0, 1.0, 1.0)
    , m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
{
}

AnimMeshEntityResource::~AnimMeshEntityResource()
{
}

void AnimMeshEntityResource::preload()
{    
}

void AnimMeshEntityResource::unloadFromPreloaded()
{
    m_animMeshCollection = NULL;
}

void AnimMeshEntityResource::load()
{
	m_animMeshCollection = Core::resourceManager().animMeshCollection(m_animMeshCollectionRef);
	m_currentAnimRef = m_animMeshCollection->defaultAnimRef();
	m_currentMesh = m_animMeshCollection->animMesh(m_currentAnimRef);
    m_layer = NULL;
    m_pos = m_initialPos;
    m_hpercent = m_initialHPercent;
	m_currentFrame = 0;
	m_frameElapsedTime = 0;
	m_finished = false;
}

void AnimMeshEntityResource::unload()
{
    m_layer = NULL;
	m_animMeshCollection = NULL;
}

const Box& AnimMeshEntityResource::screenBounds() const
{
	m_screenBounds = m_currentMesh->mesh()->boundingBox();
	m_screenBounds.translate(m_pos);
	return m_screenBounds;
}


void AnimMeshEntityResource::setAnim(const std::string& animRef, double fps)
{
    AnimMeshInfo* newMesh = m_animMeshCollection->animMesh(animRef);
    if (newMesh != m_currentMesh) {
        m_currentMesh = newMesh;
        if (fps >= 0)
            m_currentFrame = 0;
        else
            m_currentFrame = newMesh->mesh()->frameCount() - 1;
        m_currentAnimRef = animRef;
        m_frameElapsedTime = 0;
        m_finished = false;
    }
    if (fps != 0)
        m_fps = fps;
    else
        m_fps = newMesh->fps();
}

void AnimMeshEntityResource::update(const double elapsedTime)
{
    if (m_finished)
        return;
    
    double absFps = Math::abs(m_fps);
    m_frameElapsedTime += elapsedTime;
    if (m_frameElapsedTime < 1.0 / absFps)
        return;
        
    int frames = (int) (m_frameElapsedTime * absFps);
    if (m_fps >= 0) {
        m_currentFrame += frames;
        int frameCount = m_currentMesh->mesh()->frameCount();
        if (m_currentMesh->loop())
            m_currentFrame %= frameCount;
        else if (m_currentFrame >= frameCount) {
            m_currentFrame = frameCount - 1;
            m_finished = true;
        }
    } else {
        m_currentFrame -= frames;
        if (m_currentMesh->loop()) {
            int frameCount = m_currentMesh->mesh()->frameCount();
            m_currentFrame %= frameCount;
            while (m_currentFrame < 0)
                m_currentFrame += frameCount;
        } else if (m_currentFrame <= 0) {
            m_currentFrame = 0;
            m_finished = true;
        }
    }
    m_frameElapsedTime -= frames * 1.0f / absFps;
}

void AnimMeshEntityResource::draw()
{
    if (!m_currentMesh || !m_currentMesh->mesh())
        return;

    glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
	m_currentMesh->mesh()->draw(m_hpercent, m_currentFrame);
	glPopMatrix();
}

double AnimMeshEntityResource::loopDuration(double fps) const
{
    if (m_currentMesh == NULL || m_currentMesh->mesh() == NULL || m_fps == 0)
        return 0;
    return m_currentMesh->mesh()->frameCount() / Math::abs(m_fps);
} 

