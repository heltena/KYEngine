#include <KYEngine/Managers/TelemetryManager.h>
#include <KYEngine/Private/Natives/TelemetryNatives.h>

#include <sstream>

TelemetryManager::TelemetryManager()
    : m_started(false)
{
}

TelemetryManager::~TelemetryManager()
{
}

void TelemetryManager::startTracking(const std::string& accountID, int dispatchPeriod)
{
    if (m_started)
        return;

    telemetryStartTracking(accountID, dispatchPeriod);
    m_started = true;
}

void TelemetryManager::stopTracking()
{
    if (!m_started)
        return;
        
    telemetryStopTracking();
    m_started = false;
}

void TelemetryManager::trackPageView(const std::string& pageURL)
{
    if (m_started)
        telemetryTrackPageView(pageURL);
}

void TelemetryManager::trackEvent(const std::string& category, const std::string& action, const std::string& label, int value)
{
    std::stringstream ss;
    ss << category << "/" << action << "/" << label;
    if (value != 0)
        ss << "?value=" << value;
        
    if (m_started) {
        trackPageView(ss.str());
        telemetryTrackEvent(category, action, label, value);
    }
}

void TelemetryManager::dispatchInfo()
{
    if (m_started)
        telemetryDispatchInfo();
}
