#include <KYEngine/Private/Resources/AddFaceViewParamImpl.h>
#include <KYEngine/Core.h>

#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>

const std::string AddFaceViewParamImpl::XML_NODE = "add-face-view";

AddFaceViewParamImpl::AddFaceViewParamImpl()
{
}

AddFaceViewParamImpl::AddFaceViewParamImpl(const AddFaceViewParamImpl& other)
    : m_id(other.m_id)
    , m_name(other.m_name)
    , m_appearedPos(other.m_appearedPos)
    , m_disappearedPos(other.m_disappearedPos)
    , m_animDuration(other.m_animDuration)
    , m_accelMagnitude(other.m_accelMagnitude)
    , m_minValue(other.m_minValue)
    , m_maxValue(other.m_maxValue)
    , m_initialValue(other.m_initialValue)
    , m_states(other.m_states)
{
}

AddFaceViewParamImpl::~AddFaceViewParamImpl()
{
}

AddFaceViewParamImpl* AddFaceViewParamImpl::readFromXml(TiXmlElement* node)
{
    AddFaceViewParamImpl* result = new AddFaceViewParamImpl();
    
    const std::string name = TiXmlHelper::readString(node, "name", false, "<<undefined>>");
    const int id = TiXmlHelper::readInt(node, "id", true);
    const Vector4& appearedPos = TiXmlHelper::readVector(node, "ax", "ay", "az", "", READ_X | READ_Y | READ_Z);
    const Vector4& disappearedPos = TiXmlHelper::readVector(node, "dx", "dy", "dz", "", READ_X | READ_Y | READ_Z);
    const double animDuration = TiXmlHelper::readDouble(node, "anim-duration", true);
    const double accelMagnitude = TiXmlHelper::readDouble(node, "accel-magnitude", true);
    const double minValue = TiXmlHelper::readDouble(node, "min-value", true);
    const double maxValue = TiXmlHelper::readDouble(node, "max-value", true);
    const double initialValue = TiXmlHelper::readDouble(node, "initial-value", true);
    
    result->setId(id);
    result->setName(name);
    result->setAppearedPos(appearedPos);
    result->setDisappearedPos(disappearedPos);
    result->setAnimDuration(animDuration);
    result->setAccelMagnitude(accelMagnitude);
    result->setMinValue(minValue);
    result->setMaxValue(maxValue);
    result->setInitialValue(initialValue);
    
    TiXmlElement* curr = node->FirstChildElement();
	while (curr) {
		const std::string& value = curr->Value();
        if (value == FaceStateParam::XML_NODE) {
            FaceStateParam* param = FaceStateParam::readFromXml(curr);
            result->addFaceState(*param);
            delete param;
		} else 
			throw std::runtime_error("AddFaceViewParam tag error: " + value);
		
		curr = curr->NextSiblingElement();
	}

    return result;
}

HudFaceView* AddFaceViewParamImpl::generateFaceView() const
{
    HudFaceView* result = new HudFaceView(m_id, m_name, m_appearedPos, m_disappearedPos, m_animDuration, m_accelMagnitude, m_minValue, m_maxValue, m_initialValue);
    for (std::list<FaceStateParam>::const_iterator it = m_states.begin(); it != m_states.end(); it++) {
        Mesh* mesh = Core::resourceManager().mesh(it->meshRef());
        result->addState(it->forLessThan(), mesh);
    }
    return result;
}
