#include <KYEngine/KYLocale.h>

#include <stdexcept>

std::string localeToString(LocaleType locale)
{
    switch(locale) {
    case ENGLISH:
        return "EN";
    case SPANISH:
        return "ES";
    case ITALIAN:
        return "IT";
    case GERMAN:
        return "DE";
    case FRENCH:
        return "FR";
        default:
    return "EN";
    }
}

LocaleType stringToLocale(const std::string& str)
{
	/**/ if (str == "EN") return ENGLISH;
	else if (str == "ES") return SPANISH;
    else if (str == "IT") return ITALIAN;
    else if (str == "DE") return GERMAN;
    else if (str == "FR") return FRENCH;
	else return ENGLISH;
}