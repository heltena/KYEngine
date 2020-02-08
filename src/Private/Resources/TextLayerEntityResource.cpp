#include <KYEngine/Core.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Private/Resources/TextLayerEntityResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string TextLayerEntityResource::XML_NODE = "text-layer-entity";

TextLayerEntityResource* TextLayerEntityResource::readFromXml(TiXmlElement* node)
{
    TextLayerEntityResource* result = new TextLayerEntityResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string fontRef = TiXmlHelper::readString(node, "font-ref", true);
	double lineLength = TiXmlHelper::readDouble(node, "line-length", true);
    double lineSpacing = TiXmlHelper::readDouble(node, "line-spacing", true);
    AlignType align = TiXmlHelper::readAlignType(node, "align", false, ALIGN_LEFT);
	const std::string defaultText = TiXmlHelper::readString(node, "default-text", true);
    const Vector4 pivot = TiXmlHelper::readVector(node, "px", "py", "", "", NO_READ, 0, 0, 0, 0);
    
    const Vector4 borderColor = TiXmlHelper::readVector(node, "br", "bg", "bb", "ba", NO_READ, 0, 0, 0, 1);
	const bool useBlending = TiXmlHelper::readBool(node, "use-blending", false, false);
    
	result->setName(name);
	result->setFontRef(fontRef);
	result->setLineLength(lineLength);
	result->setLineSpacing(lineSpacing);
	result->setAlign(align);
	result->setDefaultText(defaultText);
    result->setPivot(pivot);
    result->setBorderColor(borderColor);
	result->setInitialPos(Vector4());
    result->setUseBlending(useBlending);
    
    return result;
}

TextLayerEntityResource::TextLayerEntityResource()
	: m_layer(NULL)
    , m_lineLength(960)
	, m_lineSpacing(0)
	, m_align(ALIGN_CENTER)
    , m_hpercent(1)
	, m_color(1.0, 1.0, 1.0, 1.0)
    , m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
	, m_layout(NULL)
    , m_updateData(true)
{
}

TextLayerEntityResource::~TextLayerEntityResource()
{
}

void TextLayerEntityResource::preload()
{
}

void TextLayerEntityResource::unloadFromPreloaded()
{
}

void TextLayerEntityResource::load()
{
	m_font = Core::resourceManager().font(m_fontRef);
	
    if (m_layout)
        std::cout << "TextLayerEntityResource layout not NULL!" << std::endl;
        
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
    m_pos = m_initialPos;
    setText(m_defaultText); // updating screenBounds!
}

void TextLayerEntityResource::unload()
{
	m_font = NULL;
	delete m_layout;
    m_layout = NULL;
}

const Box& TextLayerEntityResource::screenBounds() const
{
	// TODO: unfinished
	return m_screenBounds;
}

void TextLayerEntityResource::update(const double elapsedTime)
{
    if (m_updateData) {
        if (m_layout)
            delete m_layout;
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
            default:
                m_layout->SetAlignment(FTGL::ALIGN_CENTER);
        }
        
        m_updateData = false;
    }
}

void TextLayerEntityResource::draw()
{
	glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);

    glTranslatef(- m_pivot[0], m_pivot[1] - m_font->faceSize(), 0);
    if (! m_font->hasBorder()) {
        glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
        m_layout->Render(m_text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
    } else {
        glColor4f(m_borderColor[0], m_borderColor[1], m_borderColor[2], m_borderColor[3]);
        m_layout->SetFont((FTFont*) m_font->internalBorderData());
        m_layout->Render(m_text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
        
        glTranslatef(0, 0, 1);
        glColor4f(m_color[0], m_color[1], m_color[2], m_color[3]);
        m_layout->SetFont((FTFont*) m_font->internalData());
        m_layout->Render(m_text.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
    }
	glPopMatrix();
}


void TextLayerEntityResource::setText(const std::string& text)
{
    if (m_text == text)
        return;
    m_text = text;
    FTBBox box = m_layout->BBox(m_text.c_str(), -1, FTPoint());
    FTFont* font = (FTFont*) m_font->internalData();
    
    m_screenBounds = Box(box.Lower().X(), box.Lower().Y(),
                         box.Upper().X() - box.Lower().X(), box.Upper().Y() - box.Lower().Y());
    m_screenBounds.addSize(0, Math::abs(font->Descender()));
}
