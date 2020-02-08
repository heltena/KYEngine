#pragma once

#include <KYEngine/Utility/EffectType.h>

#include <tinyxml.h>

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

class TiXmlNodeHelper
{
public:
    TiXmlNodeHelper();
    virtual ~TiXmlNodeHelper();
    
public:
    void load(TiXmlNode* node);
    void save(TiXmlNode* node);
    
    std::string simpleXPath(const std::string& xpath, const std::string& defaultValue = "#UNDEF") const;
    int simpleXPathAsInt(const std::string& xpath, int defaultValue = 0) const;
    double simpleXPathAsDouble(const std::string& xpath, double defaultValue = 0) const;
    bool simpleXPathAsBool(const std::string& xpath, bool defaultValue = false) const;
    EffectType simpleXPathAsEffect(const std::string& xpath, EffectType defaultValue = EFFECT_NOTHING) const;
    TiXmlNodeHelper* simpleXPathAsNode(const std::string& xpath);
    
    TiXmlNodeHelper* setSimpleXPath(const std::string& xpath);
    void setSimpleXPath(const std::string& xpath, const std::string& value);
    void setSimpleXPath(const std::string& xpath, int value);
    void setSimpleXPath(const std::string& xpath, double value);
    void setSimpleXPath(const std::string& xpath, bool value);
    void setSimpleXPath(const std::string& xpath, EffectType value);

    const std::set<std::string> childKeys(const std::string& xpath = std::string()) const;
    const std::vector<TiXmlNodeHelper*> children(const std::string& xpath = std::string()) const;
    TiXmlNodeHelper* child(const std::string& key);
    
private:
    static bool extractNameAndIndex(const std::string& from, std::string& name, int& index);

    std::map<std::string, std::string> m_attributes;
    std::map<std::string, std::vector<TiXmlNodeHelper*> > m_children;
};