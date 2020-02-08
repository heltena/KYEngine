#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

bool TiXmlHelper::containsAttribute(TiXmlElement* node, const std::string& name)
{
    const char* tmp = node->Attribute(name.c_str());
    return tmp != NULL;
}

bool TiXmlHelper::readBool(TiXmlElement* node, const std::string& name, bool required, bool defaultValue)
{
	bool result = defaultValue;
	
	const char* tmp = node->Attribute(name.c_str());
	if (! tmp) {
		if (required) {
			const std::string& value = node->Value();
			throw std::runtime_error("readBool missing attribute: at node '" + value + "' attribute '" + name + "'");
		} else
			return result;
	}
	
	const std::string& strTmp = tmp;
	if (strTmp == "true")
		result = true;
	else if (strTmp == "false")
		result = false;
	else {
		const std::string& value = node->Value();
		throw std::runtime_error("readBool error at node '" + value + "' attribute '" + name + "'");
	}
	return result;
}

std::string TiXmlHelper::readString(TiXmlElement* node, const std::string& name, bool required, const std::string& defaultValue)
{
	const char* tmp = node->Attribute(name.c_str());
	if (required && ! tmp) {
		const std::string& value = node->Value();
		throw std::runtime_error("readString missing attribute: at node '" + value + "' attribute '" + name + "'");
	}
	
	return tmp ? std::string(tmp) : defaultValue;
}

Vector4 TiXmlHelper::readVector(TiXmlElement* node,
                                const std::string& nameX, const std::string& nameY, const std::string& nameZ, const std::string& nameW,
                                int requiredMask,
                                const Vector4& defaultValue)
{
    return readVector(node, nameX, nameY, nameZ, nameW, requiredMask, defaultValue[0], defaultValue[1], defaultValue[2], defaultValue[3]);
}

Vector4 TiXmlHelper::readVector(TiXmlElement* node,
								const std::string& nameX, const std::string& nameY, const std::string& nameZ, const std::string& nameW,
								int requiredMask,
								double defaultX, double defaultY, double defaultZ, double defaultW)
{
	const std::string& value = node->Value();
	double x = defaultX;
	double y = defaultY;
	double z = defaultZ;
	double w = defaultW;
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameX.c_str(), &x) && (requiredMask & READ_X)) throw std::runtime_error("readVector missing attribute: at node '" + value + "' attribute '" + nameX + "'");
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameY.c_str(), &y) && (requiredMask & READ_Y)) throw std::runtime_error("readVector missing attribute: at node '" + value + "' attribute '" + nameY + "'");
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameZ.c_str(), &z) && (requiredMask & READ_Z)) throw std::runtime_error("readVector missing attribute: at node '" + value + "' attribute '" + nameZ + "'");
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameW.c_str(), &w) && (requiredMask & READ_W)) throw std::runtime_error("readVector missing attribute: at node '" + value + "' attribute '" + nameW + "'");
	return Vector4(x, y, z, w);
}

Box TiXmlHelper::readBox(TiXmlElement* node,
                         const std::string& nameX, const std::string& nameY, const std::string& nameW, const std::string& nameH,
                         int requiredMask,
                         double defaultX, double defaultY, double defaultW, double defaultH)
{
    const std::string& value = node->Value();
	double x = defaultX;
	double y = defaultY;
	double w = defaultW;
	double h = defaultH;
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameX.c_str(), &x) && (requiredMask & READ_X)) throw std::runtime_error("readBox missing attribute: at node '" + value + "' attribute '" + nameX + "'");
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameY.c_str(), &y) && (requiredMask & READ_Y)) throw std::runtime_error("readBox missing attribute: at node '" + value + "' attribute '" + nameY + "'");
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameW.c_str(), &w) && (requiredMask & READ_W)) throw std::runtime_error("readBox missing attribute: at node '" + value + "' attribute '" + nameW + "'");
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(nameH.c_str(), &h) && (requiredMask & READ_H)) throw std::runtime_error("readBox missing attribute: at node '" + value + "' attribute '" + nameH + "'");
	return Box(x, y, w, h);
    
}

double TiXmlHelper::readDouble(TiXmlElement* node, const std::string& name, bool required, double defaultValue)
{
	const std::string& value = node->Value();
	double result = defaultValue;
	if (TIXML_SUCCESS != node->QueryDoubleAttribute(name.c_str(), &result) && required) throw std::runtime_error("readDouble missing attribute: at node '" + value + "' attribute '" + name + "'");
	return result;
}

int TiXmlHelper::readInt(TiXmlElement* node, const std::string& name, bool required, int defaultValue)
{
	const std::string& value = node->Value();
	int result = defaultValue;
	if (TIXML_SUCCESS != node->QueryIntAttribute(name.c_str(), &result) && required) throw std::runtime_error("readInt missing attribute: at node '" + value + "' attribute '" + name + "'");
	return result;
}

AlignType TiXmlHelper::readAlignType(TiXmlElement* node, const std::string& name, bool required, AlignType defaultValue)
{
    AlignType result = defaultValue;
    const char* tmp = node->Attribute(name.c_str());
    if (! tmp) {
        if (required) {
            const std::string& value = node->Value();
            throw std::runtime_error("readAlignType missing attribute: at node '" + value + "' attribute '" + name + "'");
        } else 
            return result;
    }
    
    const std::string& strTmp = tmp;
    if (strTmp == "left")
        result = ALIGN_LEFT;
    else if (strTmp == "right")
        result = ALIGN_RIGHT;
    else if (strTmp == "top")
        result = ALIGN_TOP;
    else if (strTmp == "bottom")
        result = ALIGN_BOTTOM;
    else if (strTmp == "center")
        result = ALIGN_CENTER;
    else if (strTmp == "justify")
        result = ALIGN_JUSTIFY;
    else {
        const std::string& value = node->Value();
        throw std::runtime_error("readAlignType error at node '" + value + "' attribute '" + name + "'");        
    }
	return result;
}

DirectionEnum TiXmlHelper::readDirection(TiXmlElement* node, const std::string& name, bool required, DirectionEnum defaultValue)
{
    DirectionEnum result = defaultValue;
    const char* tmp = node->Attribute(name.c_str());
    if (! tmp) {
        if (required) {
            const std::string& value = node->Value();
            throw std::runtime_error("readDirection missing attribute: at node '" + value + "' attribute '" + name + "'");
        } else
            return result;
    }

    try {
        result = stringToDirection(tmp);
    } catch(...) {
        const std::string& value = node->Value();
        throw std::runtime_error("readDirection error at node '" + value + "' attribute '" + name + "'");
    }
    return result;
}

EffectType TiXmlHelper::readEffect(TiXmlElement* node, const std::string& name, bool required, EffectType defaultValue)
{
    EffectType result = defaultValue;
    const char* tmp = node->Attribute(name.c_str());
    if (! tmp) {
        if (required) {
            const std::string& value = node->Value();
            throw std::runtime_error("readEffect missing attribute: at node '" + value + "' attribute '" + name + "'");
        } else
            return result;
    }
    
    try {
        result = stringToEffect(tmp);
    } catch(...) {
        const std::string& value = node->Value();
        throw std::runtime_error("readEffect error at node '" + value + "' attribute '" + name + "'");
    }
    return result;
}