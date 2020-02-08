#include <KYEngine/Core.h>
#include <KYEngine/Mesh.h>
#include <KYEngine/Private/Resources/ParallaxAtrezzoResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <tinyxml.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

const std::string ParallaxAtrezzoResource::XML_NODE = "parallax-atrezzo";

ParallaxAtrezzoResource* ParallaxAtrezzoResource::readFromXml(TiXmlElement* node)
{
    ParallaxAtrezzoResource* result = new ParallaxAtrezzoResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
    const double width = TiXmlHelper::readDouble(node, "width", true);
    const bool useBlending = TiXmlHelper::readBool(node, "use-blending", false, false);
    
	result->setName(name);
    result->setWidth(width);
    result->setUseBlending(useBlending);
    
    TiXmlElement* curr = node->FirstChildElement();
    while (curr) {
        const std::string& value = curr->Value();
        if (value == ParallaxLayer::XML_NODE) {
            ParallaxLayer* param = ParallaxLayer::readFromXml(curr);
            result->addLayer(param);
        } else 
            throw std::runtime_error("ParallaxEntityResource tag error: " + value);
        
        curr = curr->NextSiblingElement();
    }

    return result;
}

ParallaxAtrezzoResource::ParallaxAtrezzoResource()
{
}

ParallaxAtrezzoResource::~ParallaxAtrezzoResource()
{
    for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++)
        delete *it;
    m_layers.clear();
}

void ParallaxAtrezzoResource::preload()
{
}

void ParallaxAtrezzoResource::unloadFromPreloaded()
{
}

void ParallaxAtrezzoResource::load()
{
    for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++)
        (*it)->load();
}

void ParallaxAtrezzoResource::unload()
{
    for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++)
        (*it)->unload();
}

void ParallaxAtrezzoResource::setLayer(RenderLayer* layer)
{
    if (layer != NULL) {
        for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++)
            layer->addEntity(*it);
    } else if (m_layer != NULL) {
        for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++)
            m_layer->removeEntity(*it);
    }
    AtrezzoResource::setLayer(layer);
}

void ParallaxAtrezzoResource::setScale(const Vector4& scale)
{
    AtrezzoResource::setScale(scale);
    for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++) {
        ParallaxLayer* layer = *it;
        layer->setScale(scale);
    }
}

void ParallaxAtrezzoResource::update(const double elapsedTime)
{
}

void ParallaxAtrezzoResource::drawOpaque()
{
/*	glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);

    double xc = m_cameraPos[0] / m_width - 0.5;
    for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++) {
        ParallaxLayer* layer = *it;
        if (! layer->useBlending()) {
            glPushMatrix();
            int v = xc * (it->width() - Core::renderManager().width());
            glTranslatef(-v, 0, it->z());
            ->mesh()->draw(1);
            glPopMatrix();
        }
    }
    
    glPopMatrix();
*/}

void ParallaxAtrezzoResource::drawSemiTransparent()
{
/*	glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
    glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);

    double xc = m_cameraPos[0] / m_width - 0.5;
    for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++) {
        if (it->useBlending()) {
            glPushMatrix();
            int v = xc * (it->width() - Core::renderManager().width());
            glTranslatef(-v, 0, it->z());
            it->mesh()->draw(1);
            glPopMatrix();
        }
    }
    
    glPopMatrix();
*/
}

void ParallaxAtrezzoResource::setCameraPos(const Vector4& cameraPos)
{
    AtrezzoResource::setCameraPos(cameraPos);
    
    double xc = m_cameraPos[0] / m_width - 0.5;
    for(std::list<ParallaxLayer*>::iterator it = m_layers.begin(); it != m_layers.end(); it++) {
        ParallaxLayer* layer = *it;
        int v = xc * (layer->width() - Core::renderManager().width());
        Vector4 pos = m_pos + Vector4(-v, 0, layer->z(), 0);
        layer->setPos(pos);
    }
}

Vector4 ParallaxAtrezzoResource::atrezzoToScreen(const Vector4& atrezzoPos, double layerWidth)
{
	double xc = (m_cameraPos[0] / m_width);
    double sp = xc * (Core::renderManager().width() - layerWidth) + atrezzoPos[0];
    return Vector4(sp, atrezzoPos[1], atrezzoPos[2]);
}

