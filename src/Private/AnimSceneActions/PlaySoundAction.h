#pragma once

#include <tinyxml.h>

#include <KYEngine/Action.h>
#include <KYEngine/Entity.h>
#include <KYEngine/Sound.h>
#include <KYEngine/SoundBuffer.h>

#include <string>

class AnimSceneFactory;

class PlaySoundAction
	: public Action
{
public:
	PlaySoundAction();
	virtual ~PlaySoundAction();
	
public:
	static const std::string XML_NODE;
	static PlaySoundAction* readFromXml(TiXmlElement* node);
	
	// Action implementation
public:
	const std::string& name() const { return m_name; }
	void start(SceneTimelineInfo* info);
    void stop(SceneTimelineInfo* info) { }
	bool isBlocking();
	bool isFinished();
    bool isUsingEntity(const std::string& name) { return false; }
	void update(const double elapsedTime, SceneTimelineInfo* info);
	
public:
	void setName(const std::string& name) { m_name = name; }

	void setSoundName(const std::string& soundName) { m_soundName = soundName; }
	const std::string& soundName() const { return m_soundName; }
	
	void setFollowEntity(bool followEntity) { m_followEntity = followEntity; }
	bool followEntity() const { return m_followEntity; }
	
	void setEntityRef(const std::string& entityRef) { m_entityRef = entityRef; }
	const std::string& entityRef() const { return m_entityRef; }

	void setInitialPos(const Vector4& initialPos) { m_initialPos = initialPos; }
	const Vector4& initialPos() const { return m_initialPos; }
	
	void setBufferRef(const std::string& bufferRef) { m_bufferRef = bufferRef; }
	const std::string& bufferRef() const { return m_bufferRef; }
	
	void setPitch(double pitch) { m_pitch = pitch; }
	double pitch() const { return m_pitch; }
	
	void setGain(double gain) { m_gain = gain; }
	double gain() const { return m_gain; }
	
	void setLoop(bool loop) { m_loop = loop; }
	bool loop() const { return m_loop; }

	void setAutorelease(bool autorelease) { m_autorelease = autorelease; }
	bool autorelease() const { return m_autorelease; }
	
    void setExecuteIf(const std::string& executeIf) { m_executeIf = executeIf; }

private:
	std::string m_name;
	std::string m_soundName;
	bool m_followEntity;
	std::string m_entityRef;
	Vector4 m_initialPos;
	std::string m_bufferRef;
	double m_pitch;
	double m_gain;
	bool m_loop;
	bool m_autorelease;
    std::string m_executeIf;
	Entity* m_entity;
	Sound* m_sound;
};