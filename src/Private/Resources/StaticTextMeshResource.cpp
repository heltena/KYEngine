#include <KYEngine/Core.h>
#include <KYEngine/Private/Resources/StaticTextMeshResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string StaticTextMeshResource::XML_NODE = "static-text-mesh";

StaticTextMeshResource* StaticTextMeshResource::readFromXml(TiXmlElement* node)
{
    StaticTextMeshResource* result = new StaticTextMeshResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string fontRef = TiXmlHelper::readString(node, "font-ref", true);
	double lineLength = TiXmlHelper::readDouble(node, "line-length", true);
    double lineSpacing = TiXmlHelper::readDouble(node, "line-spacing", true);
    AlignType align = TiXmlHelper::readAlignType(node, "align", false, ALIGN_LEFT);
	const std::string initialText = node->Attribute("text");
    const Vector4 color = TiXmlHelper::readVector(node, "r", "g", "b", "a", NO_READ, 1, 1, 1, 1);
    const Vector4 borderColor = TiXmlHelper::readVector(node, "br", "bg", "bb", "ba", NO_READ, 0, 0, 0, 1);

	result->setName(name);
	result->setFontRef(fontRef);
	result->setLineLength(lineLength);
	result->setLineSpacing(lineSpacing);
	result->setAlign(align);
	result->setInitialText(initialText);
    result->setColor(color);
    result->setBorderColor(borderColor);
    
    return result;
}

StaticTextMeshResource::StaticTextMeshResource()
	: m_lineLength(960)
	, m_lineSpacing(0)
	, m_align(ALIGN_CENTER)
	, m_layout(NULL)
{
}

StaticTextMeshResource::~StaticTextMeshResource()
{
}

void StaticTextMeshResource::preload()
{
}

void StaticTextMeshResource::unloadFromPreloaded()
{
}

void StaticTextMeshResource::load()
{
	m_font = Core::resourceManager().font(m_fontRef);
	
	m_layout = new FTSimpleLayout();
	m_layout->SetLineLength(m_lineLength);
	m_layout->SetLineSpacing(m_lineSpacing);
    m_layout->SetFont((FTFont*) m_font->internalData());
	switch(m_align) {
		case ALIGN_LEFT:
			m_layout->SetAlignment(FTGL::ALIGN_LEFT);
			break;
		case ALIGN_CENTER:
			m_layout->SetAlignment(FTGL::ALIGN_CENTER);
			break;
		case ALIGN_RIGHT:
			m_layout->SetAlignment(FTGL::ALIGN_RIGHT);
			break;
        case ALIGN_JUSTIFY:
            m_layout->SetAlignment(FTGL::ALIGN_JUSTIFY);
            break;
        default:
			m_layout->SetAlignment(FTGL::ALIGN_LEFT);
	}
    m_text = Core::infoManager().executeEL(m_initialText);
}

void StaticTextMeshResource::unload()
{
	m_font = NULL;
	delete m_layout;
}

void StaticTextMeshResource::draw(double hpercent, int frame)
{
	glPushMatrix();

    float color[4];
    glGetFloatv(GL_CURRENT_COLOR, color);
    
    if (! m_font->hasBorder()) {
        glColor4f(m_color[0], m_color[1], m_color[2], color[3]);
        m_layout->Render(m_text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
    } else {
        glColor4f(m_borderColor[0], m_borderColor[1], m_borderColor[2], color[3]);
        m_layout->SetFont((FTFont*) m_font->internalBorderData());
        m_layout->Render(m_text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
        
        glTranslatef(0, 0, 1);
        glColor4f(m_color[0], m_color[1], m_color[2], color[3]);
        m_layout->SetFont((FTFont*) m_font->internalData());
        m_layout->Render(m_text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
    }
	glPopMatrix();
}

void StaticTextMeshResource::addMeshDataTo(OptimizedMeshData& data)
{
    throw std::runtime_error("StaticTextMeshResource cannot be used in OptimizedMeshData");
}