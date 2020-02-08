#include <KYEngine/Core.h>
#include <KYEngine/RatingInfo.h>

RatingInfo::RatingInfo()
    : m_openTimes(0)
    , m_url("")
{
}

RatingInfo::~RatingInfo()
{
}

const std::string RatingInfo::traslatedUrl() const
{
    std::string result = m_url;
    replace(result, "COUNTRY", Core::infoManager().userCountry());
    replace(result, "KYENGINE_APPID", Core::infoManager().appId());
    return result;
}

const std::string RatingInfo::traslatedBuyFullUrl() const
{
    std::string result = m_url;
    replace(result, "COUNTRY", Core::infoManager().userCountry());
    replace(result, "KYENGINE_APPID", Core::infoManager().buyFullAppId());
    return result;
}

const std::string RatingInfo::traslatedBuyLiteUrl() const
{
    std::string result = m_url;
    replace(result, "COUNTRY", Core::infoManager().userCountry());
    replace(result, "KYENGINE_APPID", Core::infoManager().buyLiteAppId());
    return result;
}

void RatingInfo::replace(std::string& from, const std::string& pattern, const std::string& newValue) const
{
    int patternSize = pattern.size();
    int pos;
    while ( (pos = from.find(pattern)) != -1)
        from.replace(pos, patternSize, newValue);
}