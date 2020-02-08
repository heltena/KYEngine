#include <KYEngine/Core.h>
#include <KYEngine/Private/Huds/HudTextLabel.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

HudTextLabel::HudTextLabel()
    : m_layer(NULL)
{
}

HudTextLabel::HudTextLabel(int id, const std::string& name, const Vector4& appearedPos, const Vector4& disappearedPos, double animDuration, double accelMagnitude, Font* font, const std::string& defaultText, const Vector4& color, const Vector4& borderColor, double lineLength, double lineSpacing, AlignType align)
    : m_layer(NULL)
    , m_id(id)
    , m_name(name)
    , m_appearedPos(appearedPos)
    , m_disappearedPos(disappearedPos)
    , m_pos(disappearedPos)
    , m_animDuration(animDuration)
    , m_accelMagnitude(accelMagnitude)
    , m_animation(HUD_HIDE)
    , m_elapsedTime(0)
    , m_hpercent(1)
    , m_color(color)
    , m_angle(0)
    , m_scale(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
    , m_font(font)
    , m_text(defaultText)
    , m_borderColor(borderColor)
    , m_lineLength(lineLength)
    , m_lineSpacing(lineSpacing)
    , m_align(align)
    , m_layout(NULL)
{
}

HudTextLabel::HudTextLabel(const HudTextLabel& other)
    : m_layer(other.m_layer)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_offset(other.m_offset)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_animation(other.m_animation)
    , m_elapsedTime(other.m_elapsedTime)
    , m_id(other.m_id)
    , m_name(other.m_name)
    , m_pos(other.m_pos)
    , m_bounds(other.m_bounds)
    , m_color(other.m_color)
    , m_angle(other.m_angle)
    , m_scale(other.m_scale)
    , m_alpha(other.m_alpha)
    , m_useBlending(other.m_useBlending)
    , m_font(other.m_font)
    , m_text(other.m_text)
    , m_borderColor(other.m_borderColor)
    , m_lineLength(other.m_lineLength)
    , m_lineSpacing(other.m_lineSpacing)
    , m_fromPos(other.m_fromPos)
    , m_toPos(other.m_toPos)
    , m_layout(NULL)
{
}

HudTextLabel::~HudTextLabel()
{
    if (m_layout)
        delete m_layout;
}

void HudTextLabel::appear()
{
    m_fromPos = m_pos;
    m_toPos = m_appearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_APPEARING;
    
    if (m_layout == NULL) {
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
                break;
        }
    }

}

bool HudTextLabel::isAppeared() const
{
    return m_animation == HUD_SHOWING;
}

void HudTextLabel::disappear()
{
    m_fromPos = m_pos;
    m_toPos = m_disappearedPos;
    m_elapsedTime = 0.0;
    m_animation = HUD_DISAPPEARING;
}

bool HudTextLabel::isDisappeared() const
{
    return m_animation == HUD_HIDE;
}

void HudTextLabel::update(const double elapsedTime)
{
    if (m_animation == HUD_HIDE || m_animation == HUD_SHOWING)
        return;
    
    m_elapsedTime += elapsedTime;
    m_pos = Vector4::interpolate(m_fromPos, m_toPos, m_elapsedTime / m_animDuration, m_accelMagnitude);
    
    if (m_elapsedTime > m_animDuration) {
        if (m_animation == HUD_APPEARING)
            m_animation = HUD_SHOWING;
        else {
            m_animation = HUD_HIDE;
            if (m_layout) {
                delete m_layout;
                m_layout = NULL;
            }
        }
        m_pos = m_toPos;
    }
}

void HudTextLabel::draw()
{
    if (m_animation == HUD_HIDE || m_layout == NULL)
        return;

	glPushMatrix();
	glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
	glRotatef(m_angle, 0, 0, 1);
    glScalef(m_scale[0], m_scale[1], m_scale[2]);
    
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
