#pragma once

#include <string>

class RawFileReader
{
public:
    RawFileReader(const std::string& filename, const std::string& suffix, bool simple = false);
    virtual ~RawFileReader();

public:
    const std::string& resFilename() const { return m_resFilename; }
    const char* content() { return m_content; }
    
private:
    std::string m_resFilename;
    void const * m_resourceData;
    const char* m_content;
};