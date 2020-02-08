#include <KYEngine/Private/Resources/KaraokeInfo.h>

KaraokeInfo::KaraokeInfo(double startTime, double duration, const std::string& text)
    : m_startTime(startTime)
    , m_duration(duration)
    , m_text(text)
{
}

KaraokeInfo::KaraokeInfo(const KaraokeInfo& other)
    : m_startTime(other.m_startTime)
    , m_duration(other.m_duration)
    , m_text(other.m_text)
{
}

KaraokeInfo::~KaraokeInfo()
{
}