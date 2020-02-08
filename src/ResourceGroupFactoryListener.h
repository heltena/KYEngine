#pragma once

#include <string>

class AnimMeshCollectionResource;
class AtrezzoResource;
class EntityResource;
class FontResource;
class MeshResource;
class MusicResource;
class PlayingHudResource;
class RawDataResource;
class SoundBufferResource;
class TextureResource;

class ResourceGroupFactoryListener
{
public:
    virtual void addGroupDependence(const std::string& groupRef) = 0;
    virtual void addAnimMeshCollection(AnimMeshCollectionResource* animMeshCollection) = 0;
    virtual void addAtrezzo(AtrezzoResource* atrezzoResource) = 0;
    virtual void addEntity(EntityResource* entity) = 0;
	virtual void addFont(FontResource* font) = 0;
	virtual void addMesh(MeshResource* mesh) = 0;
	virtual void addMusic(MusicResource* music) = 0;
    virtual void addPlayingHud(PlayingHudResource* playingHud) = 0;
    virtual void addRawData(RawDataResource* rawData) = 0;
	virtual void addSoundBuffer(SoundBufferResource* soundSource) = 0;
	virtual void addTexture(TextureResource* texture) = 0;
};