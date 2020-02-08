#include <KYEngine/Utility/TiXmlNodeHelper.h>

#include <stdexcept>

TiXmlNodeHelper::TiXmlNodeHelper()
{
}

TiXmlNodeHelper::~TiXmlNodeHelper()
{
    for(std::map<std::string, std::vector<TiXmlNodeHelper*> >::iterator it = m_children.begin(); it != m_children.end(); it++)
        for(std::vector<TiXmlNodeHelper*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
            delete *it2;
}

void TiXmlNodeHelper::load(TiXmlNode* node)
{
    TiXmlElement* element = node->ToElement();
    
    if (element == NULL)
        return;
    
    TiXmlAttribute* attr = element->FirstAttribute();
    while (attr) {
        m_attributes[attr->Name()] = attr->Value();
        attr = attr->Next();
    }
    
    TiXmlNode* child = node->FirstChild();
    while (child) {
        std::string name = child->Value();
        std::map<std::string, std::vector<TiXmlNodeHelper*> >::iterator found = m_children.find(name);

        TiXmlNodeHelper* newChild = new TiXmlNodeHelper();
        newChild->load(child);

        if (found == m_children.end()) {
            std::vector<TiXmlNodeHelper*> newVector;
            newVector.push_back(newChild);
            m_children[name] = newVector;
        } else
            found->second.push_back(newChild);
            
        child = child->NextSibling();
    }
}

void TiXmlNodeHelper::save(TiXmlNode* node)
{
    if (m_attributes.size() > 0) {
        TiXmlElement* element = node->ToElement();
        for(std::map<std::string, std::string>::iterator it = m_attributes.begin(); it != m_attributes.end(); it++)
            element->SetAttribute(it->first, it->second);
    }
    
    for(std::map<std::string, std::vector<TiXmlNodeHelper*> >::iterator it = m_children.begin(); it != m_children.end(); it++) {
        for(std::vector<TiXmlNodeHelper*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            TiXmlElement* newElement = new TiXmlElement(it->first);
            (*it2)->save(newElement);
            node->LinkEndChild(newElement);
        }
    }
}

bool TiXmlNodeHelper::extractNameAndIndex(const std::string& from, std::string& name, int& index)
{
    size_t pb = from.find_first_of("[");
    size_t pe = from.find_first_of("]", pb + 1);
    if (pb == std::string::npos && pe == std::string::npos) {
        name = from;
        index = 0;
        return true;
    }
    
    if (pb == std::string::npos || pe == std::string::npos)
        return false;
    
    name = from.substr(0, pb);
    std::stringstream ss(from.substr(pb + 1, pe));
    return ss >> index;
}

std::string TiXmlNodeHelper::simpleXPath(const std::string& xpath, const std::string& defaultValue) const
{
    size_t p = xpath.find_first_of("/");
    if (p == std::string::npos) {
        std::map<std::string, std::string>::const_iterator found = m_attributes.find(xpath);
        if (found != m_attributes.end())
            return found->second;
        else
            return defaultValue;
    } else {
        std::string nodeInfo = xpath.substr(0, p);
        std::string nextXPath = xpath.substr(p + 1);
        std::string nodeName;
        int index;
        if (! extractNameAndIndex(nodeInfo, nodeName, index))
            throw std::runtime_error("TiXmlNodeHelper::simpleXPath: cannot find xpath: " + xpath);
        
        std::map<std::string, std::vector<TiXmlNodeHelper*> >::const_iterator found = m_children.find(nodeName);
        if (found != m_children.end())
            return found->second[index]->simpleXPath(nextXPath, defaultValue);
        else
            return defaultValue;
    }
}

int TiXmlNodeHelper::simpleXPathAsInt(const std::string& xpath, int defaultValue) const
{
    std::string result = simpleXPath(xpath);
    if (result == "#UNDEF")
        return defaultValue;
    
    int i;
    std::stringstream ss;
    ss << result;
    ss >> i;
    return i;
}

double TiXmlNodeHelper::simpleXPathAsDouble(const std::string& xpath, double defaultValue) const
{
    std::string result = simpleXPath(xpath);
    if (result == "#UNDEF")
        return defaultValue;
    
    double d;
    std::stringstream ss;
    ss << result;
    ss >> d;
    return d;
}

bool TiXmlNodeHelper::simpleXPathAsBool(const std::string& xpath, bool defaultValue) const
{
    std::string result = simpleXPath(xpath);
    if (result == "#UNDEF")
        return defaultValue;
    else if (result == "true")
        return true;
    else
        return false;
}

EffectType TiXmlNodeHelper::simpleXPathAsEffect(const std::string& xpath, EffectType defaultValue) const
{
    std::string result = simpleXPath(xpath);
    if (result == "#UNDEF")
        return defaultValue;
    else try {
        return stringToEffect(result);
    } catch(...) {
        return defaultValue;
    }
}

TiXmlNodeHelper* TiXmlNodeHelper::simpleXPathAsNode(const std::string& xpath)
{
    size_t p = xpath.find_first_of("/");
    if (p == std::string::npos && xpath.length() == 0)
        return this;
    else if (p == std::string::npos) {
        std::string nodeName;
        int index;
        if (! extractNameAndIndex(xpath, nodeName, index))
            throw std::runtime_error("TiXmlNodeHelper:simpleXPathAsNode: cannot find xpath: " + xpath);
        std::map<std::string, std::vector<TiXmlNodeHelper*> >::iterator found = m_children.find(nodeName);
        if (found != m_children.end())
            return found->second[index];
        else
            return NULL;
    } else {
        std::string nodeInfo = xpath.substr(0, p);
        std::string nextXPath = xpath.substr(p + 1);
        std::string nodeName;
        int index;
        if (! extractNameAndIndex(nodeInfo, nodeName, index))
            throw std::runtime_error("TiXmlNodeHelper::simpleXPathAsNode(2): cannot find xpath: " + xpath);
        std::map<std::string, std::vector<TiXmlNodeHelper*> >::iterator found = m_children.find(nodeName);
        if (found != m_children.end())
            return found->second[index]->simpleXPathAsNode(nextXPath);
        else
            return NULL;
    }
}

TiXmlNodeHelper* TiXmlNodeHelper::setSimpleXPath(const std::string& xpath)
{
    size_t p = xpath.find_first_of("/");
    if (p == std::string::npos) 
        return this;
    else {
        std::string nodeInfo = xpath.substr(0, p);
        std::string nextXPath = xpath.substr(p + 1);
        std::string nodeName;
        int index;
        if (! extractNameAndIndex(nodeInfo, nodeName, index))
            throw std::runtime_error("TiXmlNodeHelper::setSimpleXPath: cannot set xpath: " + xpath);
        std::map<std::string, std::vector<TiXmlNodeHelper*> >::iterator found = m_children.find(nodeName);
        if (found != m_children.end()) {
            if (index >= 0 && index < found->second.size())
                return found->second[index]->setSimpleXPath(nextXPath);
            else if (found->second.size() == index) {
                TiXmlNodeHelper* newNode = new TiXmlNodeHelper();
                found->second.push_back(newNode);
                return newNode->setSimpleXPath(nextXPath);
            } else
                throw std::runtime_error("TiXmlNodeHelper::setSimpleXPath: cannot create multiple node at index " + index);
        } else {
            TiXmlNodeHelper* newNode = new TiXmlNodeHelper();
            std::vector<TiXmlNodeHelper*> newVector;
            newVector.push_back(newNode);
            m_children[nodeName] = newVector;
            return newNode->setSimpleXPath(nextXPath);
        }
    }
}

void TiXmlNodeHelper::setSimpleXPath(const std::string& xpath, const std::string& value)
{
    size_t p = xpath.find_first_of("/");
    if (p == std::string::npos) {
        std::map<std::string, std::string>::iterator found = m_attributes.find(xpath);
        if (found != m_attributes.end())
            found->second = value;
        else
            m_attributes[xpath] = value;
    } else {
        std::string nodeInfo = xpath.substr(0, p);
        std::string nextXPath = xpath.substr(p + 1);
        std::string nodeName;
        int index;
        if (! extractNameAndIndex(nodeInfo, nodeName, index))
            throw std::runtime_error("TiXmlNodeHelper::setSimpleXPath: cannot set xpath: " + xpath);
        std::map<std::string, std::vector<TiXmlNodeHelper*> >::iterator found = m_children.find(nodeName);
        if (found != m_children.end()) {
            if (index >= 0 && index < found->second.size())
                return found->second[index]->setSimpleXPath(nextXPath, value);
            else if (found->second.size() == index) {
                TiXmlNodeHelper* newNode = new TiXmlNodeHelper();
                found->second.push_back(newNode);
                return newNode->setSimpleXPath(nextXPath, value);
            } else
                throw std::runtime_error("TiXmlNodeHelper::setSimpleXPath: cannot create multiple node at index " + index);
        } else {
            TiXmlNodeHelper* newNode = new TiXmlNodeHelper();
            std::vector<TiXmlNodeHelper*> newVector;
            newVector.push_back(newNode);
            m_children[nodeName] = newVector;
            newNode->setSimpleXPath(nextXPath, value);
        }
    }
}

void TiXmlNodeHelper::setSimpleXPath(const std::string& xpath, int value)
{
    std::stringstream ss;
    ss << value;
    setSimpleXPath(xpath, ss.str());
}

void TiXmlNodeHelper::setSimpleXPath(const std::string& xpath, double value)
{
    std::stringstream ss;
    ss << value;
    setSimpleXPath(xpath, ss.str());
}

void TiXmlNodeHelper::setSimpleXPath(const std::string& xpath, bool value)
{
    std::string svalue = value ? "true" : "false";
    setSimpleXPath(xpath, svalue);
}

const std::set<std::string> TiXmlNodeHelper::childKeys(const std::string& xpath) const
{
    if (xpath.length() == 0) {
        std::set<std::string> result;
        for(std::map<std::string, std::vector<TiXmlNodeHelper*> >::const_iterator it = m_children.begin(); it != m_children.end(); it++) {
            const std::vector<TiXmlNodeHelper*>& vector = it->second;
            if (vector.size() <= 1)
                result.insert(it->first);
            else {
                for(int i = 0; i < vector.size(); i++) {
                    std::stringstream ss;
                    ss << it->first << "[" << i << "]";
                    result.insert(ss.str());
                }
            }
        }
        return result;
    }
    
    size_t p = xpath.find_first_of("/");
    std::string nodeName;
    if (p == std::string::npos)
        nodeName = xpath;
    else
        std::string nodeName = xpath.substr(0, p);
    
    std::map<std::string, std::vector<TiXmlNodeHelper*> >::const_iterator found = m_children.find(nodeName);
    if (found == m_children.end())
        return std::set<std::string>();
    
    if (p == std::string::npos)
        return found->second[0]->childKeys();
    else {
        std::string nextXPath = xpath.substr(p + 1);
        return found->second[0]->childKeys(nextXPath);
    }
}

const std::vector<TiXmlNodeHelper*> TiXmlNodeHelper::children(const std::string& xpath) const
{
    if (xpath.length() == 0) {
        std::vector<TiXmlNodeHelper*> result;
        for(std::map<std::string, std::vector<TiXmlNodeHelper*> >::const_iterator it = m_children.begin(); it != m_children.end(); it++) {
            const std::vector<TiXmlNodeHelper*>& vector = it->second;
            result.insert(result.end(), vector.begin(), vector.end());
        }
        return result;
    }
    
    size_t p = xpath.find_first_of("/");
    std::string nodeName;
    std::string nextXPath;
    int index;
    if (p == std::string::npos) {
        nodeName = xpath;
        index = 0;
    } else {
        std::string nodeInfo = xpath.substr(0, p);
        if (! extractNameAndIndex(nodeInfo, nodeName, index))
            throw std::runtime_error("TiXmlNodeHelper::setSimpleXPath: cannot set xpath: " + xpath);
        nextXPath = xpath.substr(p + 1);
    } 
    
    std::map<std::string, std::vector<TiXmlNodeHelper*> >::const_iterator found = m_children.find(nodeName);
    if (found == m_children.end())
        return std::vector<TiXmlNodeHelper*>();
    
    if (p == std::string::npos)
        return found->second[index]->children();
    else {
        return found->second[index]->children(nextXPath);
    }
}


TiXmlNodeHelper* TiXmlNodeHelper::child(const std::string& key)
{
    std::string nodeName;
    int index;
    if (! extractNameAndIndex(key, nodeName, index))
        throw std::runtime_error("TiXmlNodeHelper::child: key not found: " + key);
    std::map<std::string, std::vector<TiXmlNodeHelper*> >::const_iterator found = m_children.find(nodeName);
    if (found == m_children.end())
        return NULL;
    else
        return found->second[index];
}

