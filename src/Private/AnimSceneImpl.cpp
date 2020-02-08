#include <KYEngine/Core.h>

#include <KYEngine/Private/AnimSceneImpl.h>

#include <KYEngine/Private/AnimSceneActions/AddEntityAction.h>
#include <KYEngine/Private/AnimSceneActions/AddTouchEventAction.h>
#include <KYEngine/Private/AnimSceneActions/AnimSceneActionFactory.h>
#include <KYEngine/Private/AnimSceneActions/ChangeAnimAction.h>
#include <KYEngine/Private/AnimSceneActions/ChangeMusicAction.h>
#include <KYEngine/Private/AnimSceneActions/FadeAction.h>
#include <KYEngine/Private/AnimSceneActions/MoveAction.h>
#include <KYEngine/Private/AnimSceneActions/PlaySoundAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveAllTouchEventsAction.h>
#include <KYEngine/Private/AnimSceneActions/RemoveEntityAction.h>
#include <KYEngine/Private/AnimSceneActions/SetParamAction.h>
#include <KYEngine/Private/AnimSceneActions/SetLocaleAction.h>
#include <KYEngine/Private/AnimSceneActions/SetTextAction.h>
#include <KYEngine/Private/AnimSceneActions/SwitchToSceneAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForActionFinishedAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForParamChangedAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForTimeAction.h>
#include <KYEngine/Private/AnimSceneActions/WaitForTouchAction.h>

#include <KYEngine/Private/Natives/RawFileReader.h>

#include <KYEngine/Private/Resources/MeshEntityResource.h>

#include <KYEngine/Utility/TiXmlHelper.h>
#include <KYEngine/Utility/Vector4.h>

#include <CoreFoundation/CoreFoundation.h>

#include <tinyxml.h>

#include <iostream>
#include <stdexcept>

AnimSceneImpl::AnimSceneImpl(const std::string& filename)
    : m_filename(filename)
    , m_loaded(false)
{
    RawFileReader reader(filename, "xml", true);
	
	TiXmlDocument doc(filename.c_str());
	doc.Parse(reader.content());
	
	TiXmlHandle hDoc(&doc);
	
	// Get Root Handle
	TiXmlElement* pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
		throw std::runtime_error("Cannot parse resource file: " + filename);
	TiXmlHandle hRoot = TiXmlHandle(pElem);
	
	// Global info
	{
		TiXmlElement* element = hRoot.ToElement();
		std::string rootNode = element->Value();
		if (rootNode != "anim-scene")
			throw std::runtime_error("file '" + filename + "' doesn't contain 'anim-scene' root node");
		m_name = TiXmlHelper::readString(element, "name", true);
        if (m_name != filename)
            throw std::runtime_error("AnimSceneImpl: name and filename aren't equal");
	}	

    // Read preload-resource-group-ref
    {
        TiXmlElement* element = hRoot.FirstChild("preload-resource-group-ref").Element();
        while (element) {
            const std::string resourceGroupName = TiXmlHelper::readString(element, "name", true);
            m_preloadResourceGroupNames.push_back(resourceGroupName);
            element = element->NextSiblingElement("preload-resource-group-ref");
        }
    }
    
	// Read resource-group-ref
	{
		TiXmlElement* element = hRoot.FirstChild("resource-group-ref").Element();
		while (element) {
			const std::string resourceGroupName = TiXmlHelper::readString(element, "name", true);
			m_resourceGroupNames.push_back(resourceGroupName);
			element = element->NextSiblingElement("resource-group-ref");
		}
	}
    
	// Read Timeline
	{
		TiXmlElement* element = hRoot.FirstChild("timeline").Element();
		if (element) {
            const std::string motionName = TiXmlHelper::readString(element, "motion-name", false, "#UNDEF-MOTION");
			const std::string layerRef = TiXmlHelper::readString(element, "layer-ref", true);
            int layerZOrder = TiXmlHelper::readInt(element, "layer-zorder", false, 1);
            bool createLayer = TiXmlHelper::readBool(element, "create-layer", false, true);
            bool errorIfLayerExists = TiXmlHelper::readBool(element, "error-if-layer-exists", false, true);
			bool destroyLayer = TiXmlHelper::readBool(element, "destroy-layer", false, true);
            bool changeSceneIfHudTouched = TiXmlHelper::readBool(element, "change-scene-if-hud-touched", false, false);
            bool useDarkLayer = TiXmlHelper::readBool(element, "use-dark-layer", false, false);
            std::string darkMeshRef;
            if (useDarkLayer)
                darkMeshRef = TiXmlHelper::readString(element, "dark-mesh-ref", true);
            int darkLayerZOrder = TiXmlHelper::readInt(element, "dark-layer-zorder", false, layerZOrder - 1);
            std::string sceneRef;
            if (changeSceneIfHudTouched)
                sceneRef = TiXmlHelper::readString(element, "scene-ref", true);

            m_timeline.clearData();
            m_timeline.setMotionName(motionName);
			m_timeline.setLayerRef(layerRef);
            m_timeline.setLayerZOrder(layerZOrder);
			m_timeline.setCreateLayer(createLayer);
            m_timeline.setErrorIfLayerExists(errorIfLayerExists);
			m_timeline.setDestroyLayer(destroyLayer);
            m_timeline.setChangeSceneIfHudTouched(changeSceneIfHudTouched);
            m_timeline.setSceneRef(sceneRef);
            m_timeline.setUseDarkLayer(useDarkLayer);
            m_timeline.setDarkMeshRef(darkMeshRef);
            m_timeline.setDarkLayerZOrder(darkLayerZOrder);
        }
    }
}


AnimSceneImpl::~AnimSceneImpl()
{
}

void AnimSceneImpl::load()
{
    if (m_loaded)
        return;

    m_loaded = true;
    
    RawFileReader reader(m_filename, "xml", true);
	
	TiXmlDocument doc(m_filename.c_str());
	doc.Parse(reader.content());
	
	TiXmlHandle hDoc(&doc);
	
	// Get Root Handle
	TiXmlElement* pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
		throw std::runtime_error("Cannot parse resource file: " + m_filename);
	TiXmlHandle hRoot = TiXmlHandle(pElem);
	
	// Read Timeline
	{
		TiXmlElement* element = hRoot.FirstChild("timeline").Element();
		if (element) {
            const std::string motionName = TiXmlHelper::readString(element, "motion-name", false, "#UNDEF-MOTION");
			const std::string layerRef = TiXmlHelper::readString(element, "layer-ref", true);
            int layerZOrder = TiXmlHelper::readInt(element, "layer-zorder", false, 1);
            bool createLayer = TiXmlHelper::readBool(element, "create-layer", false, true);
            bool errorIfLayerExists = TiXmlHelper::readBool(element, "error-if-layer-exists", false, true);
			bool destroyLayer = TiXmlHelper::readBool(element, "destroy-layer", false, true);
            bool changeSceneIfHudTouched = TiXmlHelper::readBool(element, "change-scene-if-hud-touched", false, false);
            bool useDarkLayer = TiXmlHelper::readBool(element, "use-dark-layer", false, false);
            std::string darkMeshRef;
            if (useDarkLayer)
                darkMeshRef = TiXmlHelper::readString(element, "dark-mesh-ref", true);
            int darkLayerZOrder = TiXmlHelper::readInt(element, "dark-layer-zorder", false, layerZOrder - 1);
            std::string sceneRef;
            if (changeSceneIfHudTouched)
                sceneRef = TiXmlHelper::readString(element, "scene-ref", true);

            m_timeline.clearData();
            m_timeline.setMotionName(motionName);
			m_timeline.setLayerRef(layerRef);
            m_timeline.setLayerZOrder(layerZOrder);
			m_timeline.setCreateLayer(createLayer);
            m_timeline.setErrorIfLayerExists(errorIfLayerExists);
			m_timeline.setDestroyLayer(destroyLayer);
            m_timeline.setChangeSceneIfHudTouched(changeSceneIfHudTouched);
            m_timeline.setSceneRef(sceneRef);
            m_timeline.setUseDarkLayer(useDarkLayer);
            m_timeline.setDarkMeshRef(darkMeshRef);
            m_timeline.setDarkLayerZOrder(darkLayerZOrder);
            
            TiXmlElement* curr = element->FirstChildElement();
            while (curr) {
                Action* action =  Core::sceneManager().readFromXml(curr);
                m_timeline.addAction(action);
                curr = curr->NextSiblingElement();
            }
		}
	}
}

void AnimSceneImpl::unload()
{
    if (!m_loaded)
        return;
    m_timeline.clearData();
    m_loaded = false;
}

PlayingHudListener* AnimSceneImpl::playingHudListener()
{
    return m_timeline.playingHudListener();
}

void AnimSceneImpl::init()
{
}

void AnimSceneImpl::appear()
{
    load();
	m_timeline.appear();
}

void AnimSceneImpl::disappear()
{
	m_timeline.disappear();
}

void AnimSceneImpl::pushed()
{
    m_timeline.pushed();
}

void AnimSceneImpl::poped()
{
    m_timeline.poped();
}

void AnimSceneImpl::destroy()
{
	m_timeline.destroy();
    unload();
}

void AnimSceneImpl::abort()
{
    m_timeline.abort();
    unload();
}

void AnimSceneImpl::update(const double elapsedTime)
{
	m_timeline.update(elapsedTime);
}

