#pragma once

#include <KYEngine/DialogInfo.h>
#include <KYEngine/HelpInfo.h>
#include <KYEngine/InfoScriptListener.h>
#include <KYEngine/PopupInfo.h>
#include <KYEngine/RatingInfo.h>
#include <KYEngine/StatParam.h>
#include <KYEngine/TemplateScriptFactory.h>

#include <KYEngine/Managers/AchievementList.h>
#include <KYEngine/Managers/LeaderboardList.h>

#include <KYEngine/Utility/TiXmlNodeHelper.h>

#include <map>
#include <set>
#include <string>

typedef int StatParamKeyType;
typedef void* KYEngineGameCenterData;

class Core;

class InfoManager
{
private:
    static const std::string DEFAULT_GAME_STATE_FILENAME;
    static const std::string GAME_STATE_FILENAME;
    static const std::string CONFIGURATION_FILENAME;
    
private:
	friend class Core;
	InfoManager(const std::string& version, const std::string& gameCenterSuffix);
	virtual ~InfoManager();

public:
	void registerLibrary(TemplateScriptFactory* factory);

private:
    void load();
    void loadGameState();
    void loadConfiguration();

    void setAppId(const std::string& appId) { m_appId = appId; } 
    void setBuyFullAppId(const std::string& buyFullAppId) { m_buyFullAppId = buyFullAppId; }
    void setBuyLiteAppId(const std::string& buyLiteAppId) { m_buyLiteAppId = buyLiteAppId; }
    void setBuyButtonPressedScript(const std::string& buyButtonPressedScript) { m_buyButtonPressedScript = buyButtonPressedScript; }

public:
    void storeGameState();

public:
    const std::string& currentUserName() const { return m_currentUserName; }
    void setUserName(const std::string& userName);
    const std::string& appId() const { return m_appId; }
    const std::string& buyFullAppId() const { return m_buyFullAppId; }
    const std::string& buyLiteAppId() const { return m_buyLiteAppId; }
    const std::string& buyButtonPressedScript() const { return m_buyButtonPressedScript; }

public:
    const std::string& version() const { return m_version; }
    
    LocaleType userLocale(LocaleType defaultValue);
    void setUserLocale(LocaleType newValue);
    
    std::string userCountry();

    void lockLevel(int levelId);
    void unlockLevel(int levelId);
    bool isLevelLocked(int levelId);
    bool isLevelUnlockedRecently(int levelId);
    bool isLevelUnlockedRecentlyRange(int from = 1, int to = 32);
    void clearLevelUnlockedRecentlyRange(int from = 1, int to = 32);
    
    void lockHelp(int levelId);
    void unlockHelp(int levelId);
    bool isHelpLocked(int levelId);
    
    void lockMotion(const std::string& name);
    void unlockMotion(const std::string& name);
    bool isMotionLocked(const std::string& name);

    bool currentUserHasRatedApp();
    bool rateDialogMustAppearInMenu();
    bool rateDialogMustAppearInLevels();
    void rateIncrementOpenTimes();
    void markAppRated();
    void ratedNoThanks();
    void remindForRatingApp();

    StatParamKeyType statParamKeyFromName(const std::string& name) const;
    float statParamValue(StatParamKeyType key) const;
    void setStatParamValue(StatParamKeyType key, float value);
    void incrStatParamValue(StatParamKeyType key, float incr = 1.0f);

    void initGameCenter();
    void authenticateLocalUser();
    void updateAchievementPercentage(const std::string& achievementName, float percentage = 100.0f);
    void receiveAchievementStatusFromGameCenter(const std::string& id, float percentage);
    void updateLeaderboard(const std::string& leaderboardName, int value);
    void synchronizeGameCenterInfo();

    
public:
    void setHelpInfo(const std::string& sceneRef, int level, bool useMusicRef, const std::string& musicRef);
    void setHelpUsingMusic(bool usingMusic);
    std::string executeEL(const std::string& el, InfoScriptListener* listener = NULL);

public:
    const DialogInfo& dialogInfo() const { return m_dialogInfo; }
    const HelpInfo& helpInfo() const { return m_helpInfo; }
    const PopupInfo& popupInfo() const { return m_popupInfo; }
    const RatingInfo& ratingInfo() const { return m_ratingInfo; }

private:
    const std::string executeScript(const std::string& script, InfoScriptListener* listener = NULL);

    void debugResetRatingInfo();
    
private:
    std::set<TemplateScriptFactory*> m_factories;
    std::string m_version;
    std::string m_gameCenterSuffix;
    std::string m_currentUserName;
    std::string m_appId;
    std::string m_buyFullAppId;
    std::string m_buyLiteAppId;
    std::string m_buyButtonPressedScript;
    DialogInfo m_dialogInfo;
    HelpInfo m_helpInfo;
    PopupInfo m_popupInfo;
    RatingInfo m_ratingInfo;
    AchievementList m_achievementList;
    LeaderboardList m_leaderboardList;
    TiXmlNodeHelper m_gameState;
    TiXmlNodeHelper m_configuration;
    int m_levelUnlockedRecently;
    
    // Stats
    std::map<std::string, StatParamKeyType> m_statParamKeyRelation;
	std::map<StatParamKeyType, StatParam> m_statParamValues;
    
    // GameCenter
    KYEngineGameCenterData m_gameCenterData;
};
