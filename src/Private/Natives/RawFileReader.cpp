#include <CoreFoundation/CoreFoundation.h>

#include <KYEngine/Core.h>
#include <KYEngine/Private/Natives/RawFileReader.h>

#include <stdexcept>

RawFileReader::RawFileReader(const std::string& filename, const std::string& suffix, bool simple)
{
    if (simple)
        m_resFilename = filename;
    else
        m_resFilename = filename + Core::currentPlatform().suffix();
    
    CFStringRef name = CFStringCreateWithCString(NULL, m_resFilename.c_str(), kCFStringEncodingASCII);
    CFStringRef suff = CFStringCreateWithCString(NULL, suffix.c_str(), kCFStringEncodingASCII);
    CFURLRef url = CFBundleCopyResourceURL(CFBundleGetMainBundle(), name, suff, nil);
    if (url == nil && ! simple) {
        m_resFilename = filename;
        CFRelease(name);
        name = CFStringCreateWithCString(NULL, m_resFilename.c_str(), kCFStringEncodingASCII);
        url = CFBundleCopyResourceURL(CFBundleGetMainBundle(), name, suff, nil);
    }
    if (url == nil)
        throw std::runtime_error("Cannot load " + filename);

    CFDataRef resourceData;
    if (! CFURLCreateDataAndPropertiesFromResource(NULL, url, &resourceData, NULL, 0, NULL))
        throw std::runtime_error("Cannot read resource file: " + m_resFilename);

    m_content = (const char *) CFDataGetBytePtr(resourceData);
    CFRelease(name);
    CFRelease(suff);
    CFRelease(url);
    
    m_resourceData = static_cast<void const *>(resourceData);
}

RawFileReader::~RawFileReader()
{
    CFDataRef resourceData = (CFDataRef) m_resourceData;
    CFRelease(resourceData);
}