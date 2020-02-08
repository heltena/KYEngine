#pragma once

#include <KYEngine/Mesh.h>
#include <KYEngine/PlayingHud.h>
#include <KYEngine/RenderLayer.h>
#include <KYEngine/Touch.h>
#include <KYEngine/Utility/Vector4.h>

#include <string>

class Core;

class HudManager
{
private:
	friend class Core;
	HudManager();
	virtual ~HudManager();
	
public:
    void usePlayingHud(const std::string& name, bool appear = false, PlayingHudListener* listener = NULL);

    bool isPlayingHudActive() const;
    bool isPlayingHudDisappeared() const;
    PlayingHud& playingHud();
    void abortPlayingHud();
    void disappearPlayingHud();
    
	void update(const double elapsedTime);
    
private:
    std::string m_playingHudName;
    PlayingHud* m_playingHud;
    PlayingHud* m_nextPlayingHud;
};