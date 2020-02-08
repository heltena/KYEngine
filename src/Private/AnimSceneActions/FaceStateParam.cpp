#include <KYEngine/Private/AnimSceneActions/FaceStateParam.h>

#include <KYEngine/Utility/TiXmlHelper.h>

const std::string FaceStateParam::XML_NODE = "face-state";

FaceStateParam::FaceStateParam()
{
}

FaceStateParam::FaceStateParam(const FaceStateParam& other)
    : m_forLessThan(other.m_forLessThan)
    , m_meshRef(other.m_meshRef)
{
}

FaceStateParam::~FaceStateParam()
{
}

FaceStateParam* FaceStateParam::readFromXml(TiXmlElement* node)
{
    FaceStateParam* result = new FaceStateParam();

    const double forLessThan = TiXmlHelper::readDouble(node, "for-less-than", true);
    const std::string& meshRef = TiXmlHelper::readString(node, "mesh-ref", true);

    result->setForLessThan(forLessThan);
    result->setMeshRef(meshRef);
    
    return result;
}
