#pragma once

#include <string>

class RatingInfo
{
public:
    RatingInfo();
    virtual ~RatingInfo();
    
public:
    void setOpenTimes(int openTimes) { m_openTimes = openTimes; }
    void setUrl(const std::string& url) { m_url = url; }

public:
    int openTimes() const { return m_openTimes; }
    const std::string& url() const { return m_url; }
    const std::string traslatedUrl() const;
    const std::string traslatedBuyFullUrl() const;
    const std::string traslatedBuyLiteUrl() const;

private:
    void replace(std::string& from, const std::string& pattern, const std::string& newValue) const;

private:
    int m_openTimes;
    std::string m_url;
};