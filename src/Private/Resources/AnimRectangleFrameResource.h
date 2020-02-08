#pragma once

#include <tinyxml.h>

#include <KYEngine/Utility/Box.h>
#include <KYEngine/Utility/Vector4.h>

class AnimRectangleFrameResource
{
public:
	AnimRectangleFrameResource();
	AnimRectangleFrameResource(const AnimRectangleFrameResource& other);
	virtual ~AnimRectangleFrameResource();
	
public:
	static const std::string XML_NODE;
	static AnimRectangleFrameResource* readFromXml(TiXmlElement* node);
    
public:
	const Box& box() const { return m_box; }
	const Vector4& size() const { return m_size; }
    const Vector4& pivot() const { return m_pivot; }
	const Box& boundingBox() const { return m_boundingBox; }
	
private:
	void setBox(const Box& box) { m_box = box; }
	void setSize(const Vector4& size);
    void setPivot(const Vector4& pivot);
	
private:
	Box m_box;
	Vector4 m_size;
    Vector4 m_pivot;
	Box m_boundingBox;
};
