#include <KYEngine/Private/Resources/AnimRectangleFrameResource.h>
#include <KYEngine/Utility/TiXmlHelper.h>

#include <stdexcept>

const std::string AnimRectangleFrameResource::XML_NODE = "frame";

AnimRectangleFrameResource* AnimRectangleFrameResource::readFromXml(TiXmlElement* node)
{
    AnimRectangleFrameResource* result = new AnimRectangleFrameResource();
    const Box box = TiXmlHelper::readBox(node, "tx", "ty", "tw", "th", READ_ALL_BOX);
    const Vector4 size = TiXmlHelper::readVector(node, "w", "h", "", "", NO_READ, box.width(), box.height());
    const Vector4 pivot = TiXmlHelper::readVector(node, "px", "py", "", "", NO_READ, 0, 0);
    
    result->setBox(box);
    result->setSize(size);	
    result->setPivot(pivot);
    
    return result;
}

AnimRectangleFrameResource::AnimRectangleFrameResource()
	: m_box(0.0f, 0.0f, 1.0f, 1.0f)
	, m_size(1.0f, 1.0f)
    , m_pivot(0.0f, 0.0f)
	, m_boundingBox(-0.5f, -0.5f, 1.0f, 1.0f)
{
}

AnimRectangleFrameResource::AnimRectangleFrameResource(const AnimRectangleFrameResource& other)
	: m_box(other.m_box)
	, m_size(other.m_size) 
    , m_pivot(other.m_pivot)
	, m_boundingBox(other.m_boundingBox)
{
}

AnimRectangleFrameResource::~AnimRectangleFrameResource()
{
}

void AnimRectangleFrameResource::setSize(const Vector4& size)
{
	m_size = size;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}

void AnimRectangleFrameResource::setPivot(const Vector4& pivot)
{
    m_pivot = pivot;
	m_boundingBox = Box(- m_size[0] / 2 - m_pivot[0], - m_size[1] / 2 - m_pivot[1], m_size[0], m_size[1]);
}