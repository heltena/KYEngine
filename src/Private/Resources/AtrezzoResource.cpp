#include <KYEngine/Private/Resources/AtrezzoResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

AtrezzoResource::AtrezzoResource()
    : m_layer(NULL)
    , m_hpercent(1)
    , m_angle(0)
    , m_color(1, 1, 1, 1)
    , m_alpha(1)
    , m_useBlending(false)
    , m_scale(1, 1, 1)
{
}

AtrezzoResource::~AtrezzoResource()
{
}