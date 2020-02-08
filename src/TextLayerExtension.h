#pragma once

#include <KYEngine/Utility/AlignType.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class Entity;

class TextLayerExtension
{
public:
    virtual ~TextLayerExtension() { }
    virtual Entity* entity() = 0;
	virtual void setText(const std::string& text) = 0;
	virtual void setFontRef(const std::string& fontRef) = 0;
	virtual void setLineLength(double lineLength) = 0;
	virtual void setLineSpacing(double lineSpacing) = 0;
	virtual void setAlign(AlignType align) = 0;
    virtual void setBorderColor(const Vector4& borderColor) = 0;
    virtual void setPivot(const Vector4& pivot) = 0;
};