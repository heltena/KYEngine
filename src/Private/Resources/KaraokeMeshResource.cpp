#include <KYEngine/Core.h>
#include <KYEngine/Private/Resources/KaraokeMeshResource.h>
#include <KYEngine/Utility/KYMath.h>
#include <KYEngine/Music.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

const std::string KaraokeMeshResource::XML_NODE = "karaoke-mesh";

KaraokeMeshResource* KaraokeMeshResource::readFromXml(TiXmlElement* node)
{
    KaraokeMeshResource* result = new KaraokeMeshResource();
	const std::string name = TiXmlHelper::readString(node, "name", true);
	const std::string fontRef = TiXmlHelper::readString(node, "font-ref", true);
	double lineLength = TiXmlHelper::readDouble(node, "line-length", true);
    double lineSpacing = TiXmlHelper::readDouble(node, "line-spacing", true);
    AlignType align = TiXmlHelper::readAlignType(node, "align", false, ALIGN_LEFT);
    const Vector4 color = TiXmlHelper::readVector(node, "r", "g", "b", "a", NO_READ, 1, 1, 1, 1);
    const Vector4 borderColor = TiXmlHelper::readVector(node, "br", "bg", "bb", "ba", NO_READ, 0, 0, 0, 1);
    double animDuration = TiXmlHelper::readDouble(node, "anim-duration", true);
    const Vector4 animOffset = TiXmlHelper::readVector(node, "ax", "ay", "az", "", NO_READ, 0, 0, 0, 0);
    
	result->setName(name);
	result->setFontRef(fontRef);
	result->setLineLength(lineLength);
	result->setLineSpacing(lineSpacing);
	result->setAlign(align);
    result->setColor(color);
    result->setBorderColor(borderColor);
    result->setAnimDuration(animDuration);
    result->setAnimOffset(animOffset);
    
    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
        if (value == "phrase") {
            double startTime = TiXmlHelper::readDouble(curr, "start-time", true);
            double duration = TiXmlHelper::readDouble(curr, "duration", true);
            const std::string text = TiXmlHelper::readString(curr, "text", true);
            result->addPhrase(KaraokeInfo(startTime, duration, text));
        } else
			throw std::runtime_error("KaraokeMeshResource: (" + name + ") tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}
    return result;
}

KaraokeMeshResource::KaraokeMeshResource()
	: m_lineLength(960)
	, m_lineSpacing(0)
	, m_align(ALIGN_CENTER)
	, m_layout(NULL)
    , m_currentIndex(-1)
{
}

KaraokeMeshResource::~KaraokeMeshResource()
{
}

void KaraokeMeshResource::preload()
{
}

void KaraokeMeshResource::unloadFromPreloaded()
{
}

void KaraokeMeshResource::load()
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

    for(std::list<KaraokeInfo>::const_iterator it = m_initialPhrases.begin(); it != m_initialPhrases.end(); it++)
        m_phrases.push_back(KaraokeInfo(it->startTime(), it->duration(), Core::infoManager().executeEL(it->text(), NULL)));

    m_text = "";
    m_currentIndex = -1;
}

void KaraokeMeshResource::unload()
{
	m_font = NULL;
	delete m_layout;
}

void KaraokeMeshResource::draw(double hpercent, int frame)
{
    Music* music = Core::soundManager().currentMusic();
    if (music == NULL)
        return;
    double time = music->currentTime();
    
    // finding info...
    if (m_currentIndex < 0 || m_currentIndex >= m_phrases.size()) {
        int index = findTextIndex(time, 0, m_phrases.size() - 1);
        if (index < 0 || index >= m_phrases.size())
            return;
        m_currentIndex = index;
        m_text = m_phrases[index].text();
    } else {
        if (m_phrases[m_currentIndex].startTime() > time) {
            // Decrease
            m_currentIndex--;
            while (m_currentIndex >= 0 && m_phrases[m_currentIndex].startTime() > time)
                m_currentIndex--;
            if (m_currentIndex == -1)
                return;
        } else {
            // Increase
            while (m_currentIndex < m_phrases.size() && ! m_phrases[m_currentIndex].inTime(time))
                m_currentIndex++;
            if (m_currentIndex >= m_phrases.size())
                return;
        }
        m_text = m_phrases[m_currentIndex].text();
    }
        
    if (m_renderText != m_text)
        m_renderText = m_text;
        
    double startTime = m_phrases[m_currentIndex].startTime();
    double duration = m_phrases[m_currentIndex].duration();
	double appearPercentage = (time - startTime) / m_animDuration;
	if (appearPercentage > 1)
		appearPercentage = 1;	
	else if (appearPercentage < 0)
		appearPercentage = 0;

	double disappearPercentage = (startTime + duration - time) / m_animDuration;
	if (disappearPercentage > 1)
		disappearPercentage = 1;
	else if (disappearPercentage < 0)
		disappearPercentage = 0;

    Vector4 offset;
	double percentage = appearPercentage - 1 + (1 - disappearPercentage);
    offset = m_animOffset * percentage;
    
	glPushMatrix();
    glTranslatef(offset[0], offset[1], offset[2]);
    
    float color[4];
    glGetFloatv(GL_CURRENT_COLOR, color);
    
    color[3] *= 1 - Math::abs(percentage);
    if (! m_font->hasBorder()) {
        glColor4f(m_color[0], m_color[1], m_color[2], color[3]);
        m_layout->Render(m_renderText.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
    } else {
        glColor4f(m_borderColor[0], m_borderColor[1], m_borderColor[2], m_borderColor[3] * color[3]);
        m_layout->SetFont((FTFont*) m_font->internalBorderData());
        m_layout->Render(m_renderText.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
        
        glTranslatef(0, 0, 1);
        glColor4f(m_color[0], m_color[1], m_color[2], color[3]);
        m_layout->SetFont((FTFont*) m_font->internalData());
        m_layout->Render(m_renderText.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT | FTGL::RENDER_BACK);
    }
	glPopMatrix();
}

void KaraokeMeshResource::addMeshDataTo(OptimizedMeshData& data)
{
    throw std::runtime_error("KaraokeMeshResource cannot be used in OptimizedMeshData");
}

int KaraokeMeshResource::findTextIndex(double time, int begin, int end)
{
	if (begin > end)
		return -1;

	if (begin == end) {
		if (m_phrases[begin].inTime(time))
			return begin;
		else
			return -1;
	}

	int middle = (begin + end + 1) / 2;
	if (m_phrases[middle].inTime(time))
		return middle;
	else if (time < m_phrases[middle].startTime())
		return findTextIndex(time, begin, middle - 1);
	else
		return findTextIndex(time, middle + 1, end);
}
