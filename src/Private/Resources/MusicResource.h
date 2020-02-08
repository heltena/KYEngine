#pragma once

#include <tinyxml.h>

#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Music.h>
#include <KYEngine/Private/Resources/Resource.h>

#include <string>

class MusicResource
	: public Resource
	, public Music
{
public:
	MusicResource();
	virtual ~MusicResource();
    
public:
	static const std::string XML_NODE;
	static MusicResource* readFromXml(TiXmlElement* node);
	
// Resource implementation
public:
	const std::string& name() const { return m_name; }
    void preload();
    void unloadFromPreloaded();
	void load();
	void unload();
	void* userData() { return 0; }
	
// Music implementation
public:
	void play(float volume, double atTime = 0);
    void continuePlay(float volume);
	void stop();
    bool isPlaying() const;
    void setVolume(float volume);
    void setLoop(bool loop);
    bool loop() const;
	double currentTime();
    double duration();

private:
	void setName(const std::string& name) { m_name = name; }
	void setFilename(const std::string& filename) { m_filename = filename; }
    void setInitialLoop(bool initialLoop) { m_initialLoop = initialLoop; }
	
protected:
	bool m_loaded;
	std::string m_name;
	std::string m_filename;
    bool m_initialLoop;
	MusicData m_musicData;
    double m_lastTime;
};


