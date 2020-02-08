#pragma once

class Core;

#include <string>

class TelemetryManager
{
private:
	friend class Core;
	TelemetryManager();
	virtual ~TelemetryManager();
	
public:
    void startTracking(const std::string& accountID, int dispatchPeriod);
    void stopTracking();
    
    void trackPageView(const std::string& pageURL);
    void trackEvent(const std::string& category, const std::string& action, const std::string& label, int value);

    void dispatchInfo();

private:
    bool m_started;
};