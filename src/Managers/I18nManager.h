#pragma once

#include <KYEngine/KYLocale.h>

#include <map>
#include <string>
#include <vector>

class Core;

typedef int MessageKeyType;

class I18nManager
{
private:
	friend class Core;
	I18nManager();
	virtual ~I18nManager();
	
public:
	void init(const std::string& prefix);
	
public:
	void setLocale(LocaleType locale);
	LocaleType locale() { return m_locale; }
    MessageKeyType keyFromString(const std::string& message);
    int messageCount(MessageKeyType key) { return m_messages[key].size(); }
	const std::string& message(MessageKeyType key, int index = 0) { return m_messages[key][index]; }
	
private:
    MessageKeyType registerMessageKey(const std::string& message);
    
private:
	std::string m_prefix;
	LocaleType m_locale;
    std::map<std::string, MessageKeyType> m_keyRelation;
    int m_nextKey;
	std::map<MessageKeyType, std::vector<std::string> > m_messages;
};
