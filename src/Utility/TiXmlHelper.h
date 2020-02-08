#pragma once

#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/DirectionEnum.h>
#include <KYEngine/Utility/EffectType.h>
#include <KYEngine/Utility/Vector4.h>

#include <tinyxml.h>

#include <string>

enum TiXmlHelperVector4 {
	NO_READ = 0x0000,
	READ_X = 0x0001,
	READ_Y = 0x0002,
	READ_Z = 0x0004,
	READ_W = 0x0008,
    READ_H = 0x0010,
    READ_ALL_VECTOR = READ_X | READ_Y | READ_Z | READ_W,
    READ_ALL_BOX = READ_X | READ_Y | READ_W | READ_H
};

class TiXmlHelper
{
private:
    TiXmlHelper() { }

public:
    static bool containsAttribute(TiXmlElement* node, const std::string& name);
	static bool readBool(TiXmlElement* node, const std::string& name, bool required, bool defaultValue = false);
	static std::string readString(TiXmlElement* node, const std::string& name, bool required, const std::string& defaultValue = "");
    static Vector4 readVector(TiXmlElement* node,
                              const std::string& nameX, const std::string& nameY, const std::string& nameZ, const std::string& nameW,
                              int requiredMask,
                              const Vector4& defaultValue);
	static Vector4 readVector(TiXmlElement* node,
							  const std::string& nameX, const std::string& nameY, const std::string& nameZ, const std::string& nameW,
							  int requiredMask,
							  double defaultX = 0.0, double defaultY = 0.0, double defaultZ = 0.0, double defaultW = 1.0);
    static Box readBox(TiXmlElement* node,
                       const std::string& nameX, const std::string& nameY, const std::string& nameW, const std::string& nameH,
                       int requiredMask,
                       double defaultX = 0.0, double defaultY = 0.0, double defaultW = 1.0, double defaultH = 1.0);
	static double readDouble(TiXmlElement* node, const std::string& name, bool required, double defaultValue = 0.0);
	static int readInt(TiXmlElement* node, const std::string& name, bool required, int defaultValue = 0);
    static AlignType readAlignType(TiXmlElement* node, const std::string& name, bool required, AlignType defaultValue = ALIGN_CENTER);
    static DirectionEnum readDirection(TiXmlElement* node, const std::string& name, bool required, DirectionEnum defaultValue = DIRECTION_LEFT);
    static EffectType readEffect(TiXmlElement* node, const std::string& name, bool required, EffectType defaultValue = EFFECT_NOTHING);
};
