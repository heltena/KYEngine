#pragma once

#include <string>

void telemetryStartTracking(const std::string& accountID, int dispatchPeriod);
void telemetryStopTracking();
void telemetryTrackPageView(const std::string& pageURL);
void telemetryTrackEvent(const std::string& category, const std::string& action, const std::string& label, int value);
void telemetryDispatchInfo();