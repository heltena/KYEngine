#include <CoreFoundation/CoreFoundation.h>

#include <KYEngine/Core.h>
#include <KYEngine/Managers/I18nManager.h>
#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Natives/RawFileReader.h>

#include <tinyxml.h>

#include <iostream>
#include <stdexcept>

I18nManager::I18nManager()
{
}

I18nManager::~I18nManager()
{
}

void I18nManager::init(const std::string& prefix)
{
	m_prefix = prefix;
    LocaleType locale = currentLocale();
    locale = Core::infoManager().userLocale(locale);
	setLocale(locale);
}

void I18nManager::setLocale(LocaleType locale)
{
    m_locale = locale;
	std::string filename;
	switch(locale) {
		case SPANISH:
			filename = m_prefix + "_ES";
			break;
		case ENGLISH:
			filename = m_prefix + "_EN";
			break;
        case ITALIAN:
            filename = m_prefix + "_IT";
            break;
        case GERMAN:
            filename = m_prefix + "_DE";
            break;
        case FRENCH:
            filename = m_prefix + "_FR";
            break;
	}
	
    RawFileReader reader(filename, "xml", true);

	TiXmlDocument doc(filename.c_str());
	doc.Parse(reader.content());
	
	TiXmlHandle hDoc(&doc);
	
	// Get Root Handle
	TiXmlElement* pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
		throw std::runtime_error("Cannot parse message file: " + filename);
	TiXmlHandle hRoot = TiXmlHandle(pElem);

	// Global info
	{
		TiXmlElement* element = hRoot.ToElement();
		std::string rootNode = element->Value();
		if (rootNode != "messages")
			throw std::runtime_error("file '" + filename + "' doesn't contain 'messages' root node");
	}
	
    m_messages.clear();
    
	// Read messages
	{
		TiXmlElement* element = hRoot.FirstChild("message").Element();
		while (element) {
			const std::string& skey = element->Attribute("key");
			const std::string& text = element->Attribute("text");
			MessageKeyType key = registerMessageKey(skey);
			
			m_messages[key].push_back(text);

			element = element->NextSiblingElement("message");
		}
	}
	
    // Read message arrays
    {
        TiXmlElement* element = hRoot.FirstChild("message-list").Element();
        while (element) {
            const std::string& skey = element->Attribute("key");
			MessageKeyType key = registerMessageKey(skey);
            std::vector<std::string>& array = m_messages[key];
            
            TiXmlElement* item = element->FirstChild("item")->ToElement();
            while (item) {
                const std::string& text = item->Attribute("text");
                array.push_back(text);
                item = item->NextSiblingElement("item");
            }
            element = element->NextSiblingElement("message-list");
        }
    }
    Core::infoManager().setUserLocale(locale);
}

MessageKeyType I18nManager::keyFromString(const std::string& message)
{
    std::map<std::string, MessageKeyType>::const_iterator it = m_keyRelation.find(message);
    if (it == m_keyRelation.end())
        throw std::runtime_error("I18nManager::keyFromString: Message " + message + " doesn't found");
    return it->second;
}

MessageKeyType I18nManager::registerMessageKey(const std::string& message)
{
    MessageKeyType key = (MessageKeyType) m_nextKey++;
    m_keyRelation[message] = key;
    return key;
}
