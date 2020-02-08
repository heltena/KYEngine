#pragma once

#include <KYEngine/ResourceGroupFactoryListener.h>

#include <tinyxml.h>

#include <list>
#include <map>
#include <string>

class AnimMeshCollection;
class AnimMeshCollectionResource;
class Atrezzo;
class AtrezzoResource;
class Entity;
class EntityResource;
class Font;
class FontResource;
class Mesh;
class MeshResource;
class Music;
class MusicResource;
class PlayingHud;
class PlayingHudResource;
class RawData;
class RawDataResource;
class ResourceGroupFactory;
class ResourceManager;
class SoundBuffer;
class SoundBufferResource;
class Texture;
class TextureResource;

class ResourceGroup
    : public ResourceGroupFactoryListener
{
private:
	friend class ResourceManager;
	friend class ResourceGroupFactory;
	ResourceGroup();
	virtual ~ResourceGroup();
	
    const std::list<std::string>& groupDependences() const { return m_groupDependences; }
    void preload();
    void unloadFromPreloaded();
    void load();
    void unload();
    bool isGlobal() const { return m_isGlobal; }
    bool isLoaded() const { return m_loaded; }
    bool isPreloaded() const { return m_preloaded; }
	void setName(const std::string& name) { m_name = name; }
    void setIsGlobal(bool isGlobal) { m_isGlobal = isGlobal; }

// ResourceGroupFactoryListener implementation
public:
    void addGroupDependence(const std::string& groupRef);
    void addAnimMeshCollection(AnimMeshCollectionResource* animMeshCollection);
    void addAtrezzo(AtrezzoResource* atrezzo);
    void addEntity(EntityResource* entity);
	void addFont(FontResource* font);
	void addMesh(MeshResource* mesh);
	void addMusic(MusicResource* music);
    void addPlayingHud(PlayingHudResource* playingHud);
    void addRawData(RawDataResource* rawData);
	void addSoundBuffer(SoundBufferResource* soundSource);
	void addTexture(TextureResource* texture);
	
public:
	const std::string& name() const { return m_name; }
    AnimMeshCollection* animMeshCollection(const std::string& name);
    Atrezzo* atrezzo(const std::string& name);
    Entity* entity(const std::string& name);
	Font* font(const std::string& name);
	Mesh* mesh(const std::string& name);
	Music* music(const std::string& name);
    PlayingHud* playingHud(const std::string& name);
    RawData* rawData(const std::string& name);
	SoundBuffer* soundBuffer(const std::string& name);
	Texture* texture(const std::string& name);
	
    std::string debugInfo() const;

private:
	std::string m_name;
    bool m_isGlobal;
    bool m_preloaded;
    bool m_loaded;
    std::list<std::string> m_groupDependences;
    std::map<std::string, AnimMeshCollectionResource*> m_animMeshCollections;
    std::map<std::string, AtrezzoResource*> m_atrezzos;
    std::map<std::string, EntityResource*> m_entities;
	std::map<std::string, FontResource*> m_fonts;
	std::map<std::string, MeshResource*> m_meshes;
	std::map<std::string, MusicResource*> m_musics;
    std::map<std::string, PlayingHudResource*> m_playingHuds;
    std::map<std::string, RawDataResource*> m_rawDatas;
	std::map<std::string, SoundBufferResource*> m_soundBuffers;
	std::map<std::string, TextureResource*> m_textures;
    
private:
    template<class V> struct resource_preload_func {
        void operator()(const std::pair<std::string, V*>& p) { p.second->preload(); }
    };
    template<class V> struct resource_unloadFromPreload_func {
        void operator()(const std::pair<std::string, V*>& p) { p.second->unloadFromPreloaded(); }
    };
    
    template<class V> struct resource_load_func {
        void operator()(const std::pair<std::string, V*>& p) { p.second->load(); }
    };
    template<class V> struct resource_unload_func {
        void operator()(const std::pair<std::string, V*>& p) { p.second->unload(); }
    };
    
private:
};