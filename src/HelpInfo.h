#pragma once

#include <string>

class HelpInfo
{
public:
    HelpInfo();
    virtual ~HelpInfo();
    
public:
    void setSceneRef(const std::string& sceneRef) { m_sceneRef = sceneRef; }
    void setLevel(int level) { m_level = level; }
    void setUseMusicRef(bool useMusicRef) { m_useMusicRef = useMusicRef; }
    void setMusicRef(const std::string& musicRef) { m_musicRef = musicRef; }
    void setFromPause(bool fromPause) { m_fromPause = fromPause; }
    void setUsingMusic(bool usingMusic) { m_usingMusic = usingMusic; }

public:
    const std::string& sceneRef() const { return m_sceneRef; }
    int level() const { return m_level; }
    bool useMusicRef() const { return m_useMusicRef; }
    const std::string& musicRef() const { return m_musicRef; }
    bool usingMusic() const { return m_usingMusic; }
    bool fromPause() const { return m_fromPause; }
    
private:
    std::string m_sceneRef;
    int m_level;
    bool m_useMusicRef;
    std::string m_musicRef;
    bool m_usingMusic;
    bool m_fromPause;
};