#pragma once

#include <string>

enum LocaleType
{
	ENGLISH,
	SPANISH,
    ITALIAN,
    GERMAN,
    FRENCH
};

std::string localeToString(LocaleType locale);
LocaleType stringToLocale(const std::string& str);