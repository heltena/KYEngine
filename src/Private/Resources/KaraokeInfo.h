#pragma once

#include <string>

class KaraokeInfo
{
public:
	KaraokeInfo(double startTime, double duration, const std::string& text);
    KaraokeInfo(const KaraokeInfo& other);
    virtual ~KaraokeInfo();
    
	double startTime() const { return m_startTime; }
	double duration() const { return m_duration; }
	const std::string& text() const { return m_text; }

	bool inTime(double time) const { return time >= m_startTime && time < m_startTime + m_duration; }

private:
	double m_startTime;
	double m_duration;
	std::string m_text;
};
