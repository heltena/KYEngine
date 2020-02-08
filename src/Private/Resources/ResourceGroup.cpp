#include <KYEngine/Private/Resources/AnimMeshCollectionResource.h>
#include <KYEngine/Private/Resources/AtrezzoResource.h>
#include <KYEngine/Private/Resources/EntityResource.h>
#include <KYEngine/Private/Resources/FontResource.h>
#include <KYEngine/Private/Resources/MeshResource.h>
#include <KYEngine/Private/Resources/MusicResource.h>
#include <KYEngine/Private/Resources/PlayingHudResource.h>
#include <KYEngine/Private/Resources/RawDataResource.h>
#include <KYEngine/Private/Resources/ResourceGroup.h>
#include <KYEngine/Private/Resources/TextLayerEntityResource.h>
#include <KYEngine/Private/Resources/SoundBufferResource.h>
#include <KYEngine/Private/Resources/TextureResource.h>

#include <iostream>
#include <stdexcept>

ResourceGroup::ResourceGroup()
	: m_loaded(false)
    , m_preloaded(false)
{
}

ResourceGroup::~ResourceGroup()
{
}

void ResourceGroup::preload()
{
	if (m_isGlobal || m_loaded || m_preloaded)
		return;

    m_preloaded = true;
    
    std::for_each(m_textures.begin(), m_textures.end(), resource_preload_func<TextureResource>());
    std::for_each(m_fonts.begin(), m_fonts.end(), resource_preload_func<FontResource>());
    std::for_each(m_animMeshCollections.begin(), m_animMeshCollections.end(), resource_preload_func<AnimMeshCollectionResource>());
    std::for_each(m_atrezzos.begin(), m_atrezzos.end(), resource_preload_func<AtrezzoResource>());
    std::for_each(m_meshes.begin(), m_meshes.end(), resource_preload_func<MeshResource>());
    std::for_each(m_entities.begin(), m_entities.end(), resource_preload_func<EntityResource>());
    std::for_each(m_musics.begin(), m_musics.end(), resource_preload_func<MusicResource>());
    std::for_each(m_playingHuds.begin(), m_playingHuds.end(), resource_preload_func<PlayingHudResource>());
    std::for_each(m_rawDatas.begin(), m_rawDatas.end(), resource_preload_func<RawDataResource>());
    std::for_each(m_soundBuffers.begin(), m_soundBuffers.end(), resource_preload_func<SoundBufferResource>());
}

void ResourceGroup::unloadFromPreloaded()
{
#ifdef DEBUG
	if (m_isGlobal || m_loaded || ! m_preloaded)
		throw std::runtime_error("Cannot unload from preloaded this ResourceGroup: " + m_name);
#endif
    m_preloaded = false;
    
    std::for_each(m_textures.begin(), m_textures.end(), resource_unloadFromPreload_func<TextureResource>());
    std::for_each(m_fonts.begin(), m_fonts.end(), resource_unloadFromPreload_func<FontResource>());
    std::for_each(m_animMeshCollections.begin(), m_animMeshCollections.end(), resource_unloadFromPreload_func<AnimMeshCollectionResource>());
    std::for_each(m_atrezzos.begin(), m_atrezzos.end(), resource_unloadFromPreload_func<AtrezzoResource>());
    std::for_each(m_meshes.begin(), m_meshes.end(), resource_unloadFromPreload_func<MeshResource>());
    std::for_each(m_entities.begin(), m_entities.end(), resource_unloadFromPreload_func<EntityResource>());
    std::for_each(m_musics.begin(), m_musics.end(), resource_unloadFromPreload_func<MusicResource>());
    std::for_each(m_playingHuds.begin(), m_playingHuds.end(), resource_unloadFromPreload_func<PlayingHudResource>());
    std::for_each(m_rawDatas.begin(), m_rawDatas.end(), resource_unloadFromPreload_func<RawDataResource>());
    std::for_each(m_soundBuffers.begin(), m_soundBuffers.end(), resource_unloadFromPreload_func<SoundBufferResource>());
}

void ResourceGroup::load()
{
#ifdef DEBUG
	if (m_loaded)
		throw std::runtime_error("Cannot load again this ResourceGroup " + m_name);
#endif

    m_loaded = true;
    m_preloaded = false;
    
	// Put Texture before, because Mesh uses Texture! and Font before Mesh!
    std::for_each(m_textures.begin(), m_textures.end(), resource_load_func<TextureResource>());
    std::for_each(m_fonts.begin(), m_fonts.end(), resource_load_func<FontResource>());
    std::for_each(m_animMeshCollections.begin(), m_animMeshCollections.end(), resource_load_func<AnimMeshCollectionResource>());
    std::for_each(m_atrezzos.begin(), m_atrezzos.end(), resource_load_func<AtrezzoResource>());
    std::for_each(m_meshes.begin(), m_meshes.end(), resource_load_func<MeshResource>());
    std::for_each(m_entities.begin(), m_entities.end(), resource_load_func<EntityResource>());
    std::for_each(m_musics.begin(), m_musics.end(), resource_load_func<MusicResource>());
    std::for_each(m_playingHuds.begin(), m_playingHuds.end(), resource_load_func<PlayingHudResource>());
    std::for_each(m_rawDatas.begin(), m_rawDatas.end(), resource_load_func<RawDataResource>());
    std::for_each(m_soundBuffers.begin(), m_soundBuffers.end(), resource_load_func<SoundBufferResource>());
}

void ResourceGroup::unload()
{
#ifdef DEBUG
	if (m_isGlobal || !m_loaded)
		throw std::runtime_error("Cannot unload again this ResourceGroup " + m_name);
#endif
        
	m_loaded = false;
    m_preloaded = false;

    std::for_each(m_textures.begin(), m_textures.end(), resource_unload_func<TextureResource>());
    std::for_each(m_fonts.begin(), m_fonts.end(), resource_unload_func<FontResource>());
    std::for_each(m_animMeshCollections.begin(), m_animMeshCollections.end(), resource_unload_func<AnimMeshCollectionResource>());
    std::for_each(m_atrezzos.begin(), m_atrezzos.end(), resource_unload_func<AtrezzoResource>());
    std::for_each(m_meshes.begin(), m_meshes.end(), resource_unload_func<MeshResource>());
    std::for_each(m_entities.begin(), m_entities.end(), resource_unload_func<EntityResource>());
    std::for_each(m_musics.begin(), m_musics.end(), resource_unload_func<MusicResource>());
    std::for_each(m_playingHuds.begin(), m_playingHuds.end(), resource_unload_func<PlayingHudResource>());
    std::for_each(m_rawDatas.begin(), m_rawDatas.end(), resource_unload_func<RawDataResource>());
    std::for_each(m_soundBuffers.begin(), m_soundBuffers.end(), resource_unload_func<SoundBufferResource>());
}

void ResourceGroup::addGroupDependence(const std::string& groupRef)
{
    m_groupDependences.push_back(groupRef);
}
    
void ResourceGroup::addAnimMeshCollection(AnimMeshCollectionResource* animMeshCollection)
{
#ifdef DEBUG
    if (m_animMeshCollections.find(animMeshCollection->name()) != m_animMeshCollections.end())
        throw std::runtime_error("ResourceGroup::addAnimMeshCollection duplicated: " + animMeshCollection->name());
#endif
	m_animMeshCollections[animMeshCollection->name()] = animMeshCollection;
}

void ResourceGroup::addAtrezzo(AtrezzoResource* atrezzo)
{
#ifdef DEBUG
    if (m_atrezzos.find(atrezzo->name()) != m_atrezzos.end())
        throw std::runtime_error("ResourceGroup::addAtrezzo duplicated: " + atrezzo->name());
#endif
    m_atrezzos[atrezzo->name()] = atrezzo;
}

void ResourceGroup::addEntity(EntityResource* entity)
{
#ifdef DEBUG
    if (m_entities.find(entity->name()) != m_entities.end())
        throw std::runtime_error("ResourceGroup::addEntity duplicated: " + entity->name());
#endif
	m_entities[entity->name()] = entity;
}

void ResourceGroup::addFont(FontResource* font)
{
#ifdef DEBUG
    if (m_fonts.find(font->name()) != m_fonts.end())
        throw std::runtime_error("ResourceGroup::addFont duplicated: " + font->name());
#endif
	m_fonts[font->name()] = font;
}

void ResourceGroup::addMesh(MeshResource* mesh)
{
#ifdef DEBUG
    if (m_meshes.find(mesh->name()) != m_meshes.end())
        throw std::runtime_error("ResourceGroup::addMesh duplicated: " + mesh->name());
#endif
    m_meshes[mesh->name()] = mesh;
}

void ResourceGroup::addMusic(MusicResource* music)
{
#ifdef DEBUG
    if (m_musics.find(music->name()) != m_musics.end())
        throw std::runtime_error("ResourceGroup::addMusic duplicated: " + music->name());
#endif
	m_musics[music->name()] = music;
}

void ResourceGroup::addPlayingHud(PlayingHudResource* playingHud)
{
#ifdef DEBUG
    if (m_playingHuds.find(playingHud->name()) != m_playingHuds.end())
        throw std::runtime_error("ResourceGroup::addPlayingHud duplicated: " + playingHud->name());
#endif
    m_playingHuds[playingHud->name()] = playingHud;
}

void ResourceGroup::addRawData(RawDataResource* rawData)
{
#ifdef DEBUG
    if (m_rawDatas.find(rawData->name()) != m_rawDatas.end())
        throw std::runtime_error("ResourceGroup::addRawData duplicated: " + rawData->name());
#endif
    m_rawDatas[rawData->name()] = rawData;
}

void ResourceGroup::addSoundBuffer(SoundBufferResource* soundBuffer)
{
#ifdef DEBUG
    if (m_soundBuffers.find(soundBuffer->name()) != m_soundBuffers.end())
        throw std::runtime_error("ResourceGroup::addSoundBuffer duplicated: " + soundBuffer->name());
#endif
	m_soundBuffers[soundBuffer->name()] = soundBuffer;
}

void ResourceGroup::addTexture(TextureResource* texture)
{
#ifdef DEBUG
    if (m_textures.find(texture->name()) != m_textures.end())
        throw std::runtime_error("ResourceGroup::addTexture duplicated: " + texture->name());
#endif
	m_textures[texture->name()] = texture;
}

AnimMeshCollection* ResourceGroup::animMeshCollection(const std::string& name)
{
    if (!m_loaded || m_animMeshCollections.find(name) == m_animMeshCollections.end())
        return NULL;
    else
        return m_animMeshCollections[name];
}

Atrezzo* ResourceGroup::atrezzo(const std::string& name)
{
    if (!m_loaded || m_atrezzos.find(name) == m_atrezzos.end())
        return NULL;
    else
        return m_atrezzos[name];
}

Entity* ResourceGroup::entity(const std::string& name)
{
	if (!m_loaded || m_entities.find(name) == m_entities.end())
		return NULL;
	else
		return m_entities[name];
}

Font* ResourceGroup::font(const std::string& name)
{
	if (!m_loaded || m_fonts.find(name) == m_fonts.end())
		return NULL;
	else
		return m_fonts[name];
}

Mesh* ResourceGroup::mesh(const std::string& name)
{
	if (!m_loaded || m_meshes.find(name) == m_meshes.end())
		return NULL;
	else
		return m_meshes[name];
}

Music* ResourceGroup::music(const std::string& name)
{
	if (!m_loaded || m_musics.find(name) == m_musics.end())
		return NULL;
	else
		return m_musics[name];
}

PlayingHud* ResourceGroup::playingHud(const std::string& name)
{
    if (!m_loaded || m_playingHuds.find(name) == m_playingHuds.end())
        return NULL;
    else
        return m_playingHuds[name];
}

RawData* ResourceGroup::rawData(const std::string& name)
{
    if (!m_loaded || m_rawDatas.find(name) == m_rawDatas.end())
        return NULL;
    else
        return m_rawDatas[name];
}

SoundBuffer* ResourceGroup::soundBuffer(const std::string& name)
{
	if (!m_loaded || m_soundBuffers.find(name) == m_soundBuffers.end())
		return NULL;
	else
		return m_soundBuffers[name];
}

Texture* ResourceGroup::texture(const std::string& name)
{
	if (!m_loaded || m_textures.find(name) == m_textures.end())
		return NULL;
	else
		return m_textures[name];
}

std::string ResourceGroup::debugInfo() const
{
    std::stringstream ss;
    ss << "(Group: '" << m_name << "'"
        << " isGlobal=" << (m_isGlobal ? "True" : "False")
        << " preloaded=" << (m_preloaded ? "True" : "False")
        << " loaded=" << (m_loaded ? "True" : "False")
        << ")";
    return ss.str();
}

