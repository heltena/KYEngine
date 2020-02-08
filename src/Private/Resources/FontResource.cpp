#include <KYEngine/Private/Resources/FontResource.h>
#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

const std::string FontResource::XML_NODE = "font";

FontResource* FontResource::readFromXml(TiXmlElement* node)
{
    FontResource* result = new FontResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string filename = TiXmlHelper::readString(node, "filename", true);
    double faceSize = TiXmlHelper::readDouble(node, "face-size", true);
    bool hasBorder = TiXmlHelper::readBool(node, "has-border", false, false);
    float borderOutset = TiXmlHelper::readDouble(node, "border-outset", false, 1);
	
	result->setName(name);
    result->setFilename(filename);
    result->setFaceSize(faceSize);
    result->setHasBorder(hasBorder);
    result->setBorderOutset(borderOutset);
    
    return result;
}

FontResource::FontResource()
	: m_loaded(false)
	, m_data(NULL)
    , m_borderData(NULL)
{
}

FontResource::~FontResource()
{
}

void FontResource::preload()
{
    // TODO: preload!
}

void FontResource::unloadFromPreloaded()
{
}

void FontResource::load()
{
    if (m_data != NULL)
        throw std::runtime_error("FontResource: cannot reuse m_data");
    m_data = new FTTextureFont(filenamePath(m_filename).c_str());
	if (m_data->Error())
		throw std::runtime_error("FontResource could not load font " + m_filename);
	m_data->FaceSize(m_faceSize);

    if (m_hasBorder) {
        if (m_borderData != NULL)
            throw std::runtime_error("FontResource: cannot reuse m_borderData");
        m_borderData = new FTPolygonFont(filenamePath(m_filename).c_str()); 
        if (m_borderData->Error()) {
            std::stringstream ss;
            ss << "FontResource could not load border font " << m_filename << " Error: " << m_borderData->Error();
            throw std::runtime_error(ss.str());
        }
        m_borderData->Outset(m_borderOutset);
        m_borderData->FaceSize(m_faceSize);
    }
}

void FontResource::unload()
{
	if (m_data) {
        delete m_data;
        m_data = NULL;
    }
    if (m_borderData) {
        delete m_borderData;
        m_borderData = NULL;
    }
}
