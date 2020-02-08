#include <KYEngine/Private/Resources/AddFaceViewParamImpl.h>
#include <KYEngine/Private/Resources/AddJoystickButtonParamImpl.h>
#include <KYEngine/Private/Resources/AddMapViewParamImpl.h>
#include <KYEngine/Private/Resources/AddProgressViewParamImpl.h>
#include <KYEngine/Private/Resources/AddPushButtonParamImpl.h>
#include <KYEngine/Private/Resources/AddTextLabelParamImpl.h>

#include <KYEngine/Private/Resources/AnimMeshCollectionResource.h>
#include <KYEngine/Private/Resources/AnimMeshEntityResource.h>
#include <KYEngine/Private/Resources/AnimRectangleFrameResource.h>
#include <KYEngine/Private/Resources/AnimRectangleMeshResource.h>
#include <KYEngine/Private/Resources/ColoredRectangleMeshResource.h>
#include <KYEngine/Private/Resources/FontResource.h>
#include <KYEngine/Private/Resources/GradientRectangleMeshResource.h>
#include <KYEngine/Private/Resources/GroupedMeshResource.h>
#include <KYEngine/Private/Resources/KaraokeMeshResource.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Private/Resources/MeshEntityResource.h>
#include <KYEngine/Private/Resources/MusicResource.h>
#include <KYEngine/Private/Resources/ParallaxAtrezzoResource.h>
#include <KYEngine/Private/Resources/ParticleEmitterEntityResource.h>
#include <KYEngine/Private/Resources/PlayingHudResource.h>
#include <KYEngine/Private/Resources/RectangleMeshResource.h>
#include <KYEngine/Private/Resources/ResourceGroup.h>
#include <KYEngine/Private/Resources/ResourceGroupFactory.h>
#include <KYEngine/Private/Resources/SoundBufferResource.h>
#include <KYEngine/Private/Resources/SoundBufferSingleResource.h>
#include <KYEngine/Private/Resources/SoundBufferGroupResource.h>
#include <KYEngine/Private/Resources/StaticTextMeshResource.h>
#include <KYEngine/Private/Resources/TextLayerEntityResource.h>
#include <KYEngine/Private/Resources/TextureResource.h>

#include <KYEngine/ResourceGroupFactoryListener.h>

#include <KYEngine/Utility/TiXmlHelper.h>

#include <iostream>
#include <stdexcept>

void ResourceGroupFactory::readFromXml(const std::string& prefix, TiXmlElement* node, ResourceGroupFactoryListener* listener)
{
    const std::string& nodeValue = node->Value();
    
    std::string value;
    if (prefix.length() == 0) {
        value = nodeValue;
    } else {
        size_t dots = nodeValue.find_first_of(':');
        if (dots == std::string::npos)
            throw std::runtime_error("ResourceGroupFactory::readFromXml: not in namespace '" + nodeValue + "' prefix: " + prefix);
        if (nodeValue.substr(0, dots) != prefix)
            throw std::runtime_error("ResourceGroupFactory::readFromXml: not in namespace '" + nodeValue + "' prefix: " + prefix);
        value = nodeValue.substr(dots + 1);
    }
    
    if (value == "group-dependence") {
        const std::string groupRef = TiXmlHelper::readString(node, "group-ref", true);
        listener->addGroupDependence(groupRef);
    } else if (value == AnimMeshCollectionResource::XML_NODE) {
        AnimMeshCollectionResource* newAnimMeshCollection = AnimMeshCollectionResource::readFromXml(node);
        listener->addAnimMeshCollection(newAnimMeshCollection);
    } else if (value == AnimMeshEntityResource::XML_NODE) {
        AnimMeshEntityResource* newAnimMeshEntity = AnimMeshEntityResource::readFromXml(node);
        listener->addEntity(newAnimMeshEntity);
    } else if (value == AnimRectangleMeshResource::XML_NODE) {
        AnimRectangleMeshResource* newMesh = AnimRectangleMeshResource::readFromXml(node);
        listener->addMesh(newMesh);
    } else if (value == ColoredRectangleMeshResource::XML_NODE) {
        ColoredRectangleMeshResource* newMesh = ColoredRectangleMeshResource::readFromXml(node);
        listener->addMesh(newMesh);
    } else if (value == FontResource::XML_NODE) {
        FontResource* newFont = FontResource::readFromXml(node);
        listener->addFont(newFont);
    } else if (value == GradientRectangleMeshResource::XML_NODE) {
        GradientRectangleMeshResource* newMesh = GradientRectangleMeshResource::readFromXml(node);
        listener->addMesh(newMesh);
    } else if (value == GroupedMeshResource::XML_NODE) {
        GroupedMeshResource* newGroupedMesh = GroupedMeshResource::readFromXml(node);
        listener->addMesh(newGroupedMesh);
    } else if (value == KaraokeMeshResource::XML_NODE) {
        KaraokeMeshResource* newMesh = KaraokeMeshResource::readFromXml(node);
        listener->addMesh(newMesh);
    } else if (value == MeshEntityResource::XML_NODE) {
        MeshEntityResource* newEntity = MeshEntityResource::readFromXml(node);
        listener->addEntity(newEntity);
    } else if (value == MusicResource::XML_NODE) {
        MusicResource* newMusic = MusicResource::readFromXml(node);
        listener->addMusic(newMusic);
    } else if (value == ParallaxAtrezzoResource::XML_NODE) {
        ParallaxAtrezzoResource* newAtrezzo = ParallaxAtrezzoResource::readFromXml(node);
        listener->addAtrezzo(newAtrezzo);
    } else if (value == ParticleEmitterEntityResource::XML_NODE) {
        ParticleEmitterEntityResource* newEntity = ParticleEmitterEntityResource::readFromXml(node);
        listener->addEntity(newEntity);
    } else if (value == PlayingHudResource::XML_NODE) {
        PlayingHudResource* newPlayingHud = PlayingHudResource::readFromXml(node);
        listener->addPlayingHud(newPlayingHud);
    } else if (value == RectangleMeshResource::XML_NODE) {
        RectangleMeshResource* newMesh = RectangleMeshResource::readFromXml(node);
        listener->addMesh(newMesh);
    } else if (value == SoundBufferSingleResource::XML_NODE) {
        SoundBufferResource* newSoundBuffer = SoundBufferSingleResource::readFromXml(node);
        listener->addSoundBuffer(newSoundBuffer);
    } else if (value == SoundBufferGroupResource::XML_NODE) {
        SoundBufferGroupResource* newSoundBuffer = SoundBufferGroupResource::readFromXml(node);
        listener->addSoundBuffer(newSoundBuffer);
    } else if (value == StaticTextMeshResource::XML_NODE) {
        StaticTextMeshResource* newStaticTextMesh = StaticTextMeshResource::readFromXml(node);
        listener->addMesh(newStaticTextMesh);
    } else if (value == TextLayerEntityResource::XML_NODE) {
        TextLayerEntityResource* newEntity = TextLayerEntityResource::readFromXml(node);
        listener->addEntity(newEntity);
    } else if (value == TextureResource::XML_NODE) {
        TextureResource* newTexture = TextureResource::readFromXml(node);
        listener->addTexture(newTexture);
    } else
        throw std::runtime_error("ResourceGroupFactory::Resource tag error: " + value);
}

void ResourceGroupFactory::readFromXml(const std::string& prefix, TiXmlElement* node, PlayingHudFactoryListener* listener)
{
    const std::string& nodeValue = node->Value();
    
    std::string value;
    if (prefix.length() == 0) {
        value = nodeValue;
    } else {
        size_t dots = nodeValue.find_first_of(':');
        if (dots == std::string::npos)
            throw std::runtime_error("ResourceGroupFactory::readFromXml: not in namespace '" + nodeValue + "' prefix: " + prefix);
        if (nodeValue.substr(0, dots) != prefix)
            throw std::runtime_error("ResourceGroupFactory::readFromXml: not in namespace '" + nodeValue + "' prefix: " + prefix);
        value = nodeValue.substr(dots + 1);
    }
    
    if (value == AddFaceViewParamImpl::XML_NODE) {
        AddFaceViewParam* param = AddFaceViewParamImpl::readFromXml(node);
        listener->addFaceViewParam(param);
    } else if (value == AddMapViewParamImpl::XML_NODE) {
        AddMapViewParam* param = AddMapViewParamImpl::readFromXml(node);
        listener->addMapViewParam(param);
    } else if (value == AddProgressViewParamImpl::XML_NODE) {
        AddProgressViewParam* param = AddProgressViewParamImpl::readFromXml(node);
        listener->addProgressViewParam(param);
    } else if (value == AddJoystickButtonParamImpl::XML_NODE) {
        AddJoystickButtonParam* param = AddJoystickButtonParamImpl::readFromXml(node);
        listener->addJoystickButtonParam(param);
    } else if (value == AddPushButtonParamImpl::XML_NODE) {
        AddPushButtonParam* param = AddPushButtonParamImpl::readFromXml(node);
        listener->addPushButtonParam(param);
    } else if (value == AddTextLabelParamImpl::XML_NODE) {
        AddTextLabelParam* param = AddTextLabelParamImpl::readFromXml(node);
        listener->addTextLabelParam(param);
    } else 
        throw std::runtime_error("ResourceGroupFactory::Hud tag error: " + value);
    
}

