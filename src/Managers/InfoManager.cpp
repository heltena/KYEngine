#include <KYEngine/Core.h>
#include <KYEngine/Utility/FunctionCallStatement.h>
#include <KYEngine/Managers/InfoManager.h>
#include <KYEngine/KYLocale.h>
#include <KYEngine/Private/Natives/NativeUtils.h>
#include <KYEngine/Private/Natives/RawFileReader.h>
#include <KYEngine/Private/Natives/KYEngineGameCenterAdapter.h>

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <sstream>

const std::string InfoManager::DEFAULT_GAME_STATE_FILENAME = "default-game-state.xml";
const std::string InfoManager::GAME_STATE_FILENAME = "game-state.xml";
const std::string InfoManager::CONFIGURATION_FILENAME = "configuration.xml";

InfoManager::InfoManager(const std::string& version, const std::string& gameCenterSuffix)
    : m_version(version)
    , m_gameCenterSuffix(gameCenterSuffix)
    , m_levelUnlockedRecently(-1)
    , m_gameCenterData(NULL)
{
}

InfoManager::~InfoManager()
{
}

void InfoManager::registerLibrary(TemplateScriptFactory* factory)
{
    m_factories.insert(factory);
}

void InfoManager::load()
{
    loadConfiguration();
    loadGameState();
}

void InfoManager::loadGameState()
{
    // Read Game State
    if (! documentExists(GAME_STATE_FILENAME))
        copyFileToDocument(DEFAULT_GAME_STATE_FILENAME, GAME_STATE_FILENAME);
    
    std::string filename = documentPath(GAME_STATE_FILENAME);

	TiXmlDocument doc(filename);
	doc.LoadFile();
	
	TiXmlHandle hDoc(&doc);
	
	TiXmlElement* pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
		throw std::runtime_error("Cannot parse GameState file: " + filename);
	TiXmlHandle hRoot = TiXmlHandle(pElem);

    m_gameState.load(hRoot.ToElement());
    m_currentUserName = m_gameState.simpleXPath("current-user-name/name", "default-user");
    
    // Load current stats
    std::stringstream ss;
    ss << m_currentUserName << "/stats";
    TiXmlNodeHelper* statNode = m_gameState.simpleXPathAsNode(ss.str());
    if (statNode != NULL) {
        std::vector<TiXmlNodeHelper*> statValues = statNode->children();
        for(std::vector<TiXmlNodeHelper*>::const_iterator it = statValues.begin(); it != statValues.end(); it++) {
            TiXmlNodeHelper* curStat = *it;
            StatParamKeyType key = statParamKeyFromName(curStat->simpleXPath("name"));
            setStatParamValue(key, curStat->simpleXPathAsDouble("value"));
        }
    }
    
    // Load achievement list
    ss.str(m_currentUserName);
    TiXmlNodeHelper* achievementListNode = m_gameState.simpleXPathAsNode(ss.str());
    if (achievementListNode != NULL)
        m_achievementList.loadFromNode(achievementListNode);
        
    // Load leaderboard list
    ss.str(m_currentUserName);
    TiXmlNodeHelper* leaderboardListNode = m_gameState.simpleXPathAsNode(ss.str());
    if (leaderboardListNode != NULL)
        m_leaderboardList.loadFromNode(leaderboardListNode);
}

void InfoManager::loadConfiguration()
{
    std::string filename = filenamePath(CONFIGURATION_FILENAME);
    TiXmlDocument doc(filename);
    doc.LoadFile();
    
    TiXmlHandle hDoc(&doc);
    
	TiXmlElement* pElem = hDoc.FirstChildElement().Element();
	if (!pElem)
		throw std::runtime_error("Cannot parse Configuration file: " + filename);
	TiXmlHandle hRoot = TiXmlHandle(pElem);
    
    m_configuration.load(hRoot.ToElement());
    
    // Load DialogInfo
    m_dialogInfo.setBorderWidth(m_configuration.simpleXPathAsDouble("dialog-info/border-width"));
    m_dialogInfo.setBorderHeight(m_configuration.simpleXPathAsDouble("dialog-info/border-height"));
    m_dialogInfo.setBackgroundEntityRef(m_configuration.simpleXPath("dialog-info/background-entity-ref"));
    m_dialogInfo.setFontRef(m_configuration.simpleXPath("dialog-info/font-ref"));
    m_dialogInfo.setZ(m_configuration.simpleXPathAsDouble("dialog-info/z"));
    m_dialogInfo.setAppearingCelerity(m_configuration.simpleXPathAsDouble("dialog-info/appearing-celerity"));
    m_dialogInfo.setDisappearingCelerity(m_configuration.simpleXPathAsDouble("dialog-info/disappearing-celerity"));
    
    TiXmlNodeHelper* base = m_configuration.simpleXPathAsNode("dialog-info/color-key");
    if (base != NULL) {
        std::set<std::string> childKeys = base->childKeys();
        for(std::set<std::string>::iterator it = childKeys.begin(); it != childKeys.end(); it++) {
            TiXmlNodeHelper* node = base->child(*it);
            double r = node->simpleXPathAsDouble("r");
            double g = node->simpleXPathAsDouble("g");
            double b = node->simpleXPathAsDouble("b");
            double a = node->simpleXPathAsDouble("a");
            m_dialogInfo.addColor(*it, Vector4(r, g, b, a));
        }
    }
    
    // Load PopupInfo
    m_popupInfo.setBorderWidth(m_configuration.simpleXPathAsDouble("popup-info/border-width"));
    m_popupInfo.setBorderHeight(m_configuration.simpleXPathAsDouble("popup-info/border-height"));
    m_popupInfo.setBackgroundEntityRef(m_configuration.simpleXPath("popup-info/background-entity-ref"));
    m_popupInfo.setFontRef(m_configuration.simpleXPath("popup-info/font-ref"));
    Vector4 pos;
    pos[0] = m_configuration.simpleXPathAsDouble("popup-info/pos/x");
    pos[1] = m_configuration.simpleXPathAsDouble("popup-info/pos/y");
    pos[2] = m_configuration.simpleXPathAsDouble("popup-info/pos/z");
    m_popupInfo.setPos(pos);
    m_popupInfo.setAppearDuration(m_configuration.simpleXPathAsDouble("popup-info/appear-duration"));
    m_popupInfo.setAppearEffect(m_configuration.simpleXPathAsEffect("popup-info/appear-effect"));
    m_popupInfo.setAppearAccelMagnitude(m_configuration.simpleXPathAsDouble("popup-info/appear-accel-magnitude"));
    m_popupInfo.setDisappearDuration(m_configuration.simpleXPathAsDouble("popup-info/disappear-duration"));
    m_popupInfo.setDisappearEffect(m_configuration.simpleXPathAsEffect("popup-info/disappear-effect"));
    m_popupInfo.setDisappearAccelMagnitude(m_configuration.simpleXPathAsDouble("popup-info/disappear-accel-magnitude"));
    TiXmlNodeHelper* node = m_configuration.simpleXPathAsNode("popup-info/color");
    double r = node->simpleXPathAsDouble("r");
    double g = node->simpleXPathAsDouble("g");
    double b = node->simpleXPathAsDouble("b");
    double a = node->simpleXPathAsDouble("a");
    m_popupInfo.setColor(Vector4(r, g, b, a));
    
    // Load RatingInfo
    m_ratingInfo.setOpenTimes(m_configuration.simpleXPathAsInt("rating-info/max-open-times"));
    m_ratingInfo.setUrl(m_configuration.simpleXPath("rating-info/url"));
    
    // Load stat params
    int nextStatParamKey = 0;
    std::vector<TiXmlNodeHelper*> statParams = m_configuration.simpleXPathAsNode("stat-params")->children();
    for(std::vector<TiXmlNodeHelper*>::const_iterator it = statParams.begin(); it != statParams.end(); it++) {
        TiXmlNodeHelper* curStatParam = *it;
        
        StatParam statParam;
        statParam.setName(curStatParam->simpleXPath("name"));
        statParam.setDescription(curStatParam->simpleXPath("description"));
        statParam.setDefaultValue(curStatParam->simpleXPathAsDouble("default-value"));
        statParam.setIsLevelStat(curStatParam->simpleXPathAsBool("level-stat", false));
        int newKey = nextStatParamKey++;
        m_statParamKeyRelation[statParam.name()] = newKey;
        m_statParamValues[newKey] = statParam;
    }
}

void InfoManager::storeGameState()
{
    // Update stat values
    std::stringstream ss;
    ss << m_currentUserName << "/stats/stat";
    std::string base = ss.str();
    int index = 0;
    for(std::map<StatParamKeyType, StatParam>::const_iterator it = m_statParamValues.begin(); it != m_statParamValues.end(); it++) {
        if (! it->second.isLevelStat()) {
            ss.str("");
            ss << base << "[" << index << "]";
            m_gameState.setSimpleXPath(ss.str() + "/name", it->second.name());
            m_gameState.setSimpleXPath(ss.str() + "/value", it->second.currentValue());
            index++;
        }
    }

    // Update achievement values
    ss.str(m_currentUserName);
    TiXmlNodeHelper* achievementNode = m_gameState.simpleXPathAsNode(ss.str());
    m_achievementList.saveToNode(achievementNode);

    // Update leaderboard values
    ss.str(m_currentUserName);
    TiXmlNodeHelper* leaderboardNode = m_gameState.simpleXPathAsNode(ss.str());
    m_leaderboardList.saveToNode(leaderboardNode);
    
    // Save
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");  
	doc.LinkEndChild(decl);
    TiXmlElement* root = new TiXmlElement("game-state");  
	doc.LinkEndChild(root);

    m_gameState.save(root);
    doc.SaveFile(documentPath(GAME_STATE_FILENAME));
}

LocaleType InfoManager::userLocale(LocaleType defaultValue)
{
    std::stringstream ss;
    ss << m_currentUserName << "/locale";
    return stringToLocale(m_gameState.simpleXPath(ss.str(), localeToString(defaultValue)));
}

void InfoManager::setUserLocale(LocaleType newValue)
{
    std::stringstream ss;
    ss << m_currentUserName << "/locale";
    m_gameState.setSimpleXPath(ss.str(), localeToString(newValue));
    storeGameState();
}

std::string InfoManager::userCountry()
{
    return ::currentCountry();
}

void InfoManager::lockLevel(int levelId)
{
    std::stringstream ss;
    ss << m_currentUserName << "/levels/level";
    if (levelId < 10)
        ss << "0";
    ss << levelId << "/locked";
    m_gameState.setSimpleXPath(ss.str(), true);
    storeGameState();
}

void InfoManager::unlockLevel(int levelId)
{
    std::stringstream ss;
    ss << m_currentUserName << "/levels/level";
    if (levelId < 10)
        ss << "0";
    ss << levelId << "/locked";
    if (m_gameState.simpleXPathAsBool(ss.str(), true)) {
        m_gameState.setSimpleXPath(ss.str(), false);
        storeGameState();
        m_levelUnlockedRecently = levelId;
    }
}

bool InfoManager::isLevelLocked(int levelId)
{
    std::stringstream ss;
    ss << m_currentUserName << "/levels/level";
    if (levelId < 10)
        ss << "0";
    ss << levelId << "/locked";
    return m_gameState.simpleXPathAsBool(ss.str(), true);
}

bool InfoManager::isLevelUnlockedRecently(int levelId)
{
    return m_levelUnlockedRecently == levelId;
}

bool InfoManager::isLevelUnlockedRecentlyRange(int from, int to)
{
    return m_levelUnlockedRecently >= from && m_levelUnlockedRecently <= to;
}

void InfoManager::clearLevelUnlockedRecentlyRange(int from, int to)
{
    if (m_levelUnlockedRecently >= from && m_levelUnlockedRecently <= to)
        m_levelUnlockedRecently = -1;
}

void InfoManager::lockHelp(int levelId)
{
    std::stringstream ss;
    ss << m_currentUserName << "/helps/help";
    if (levelId < 10)
        ss << "0";
    ss << levelId << "/shown";
    m_gameState.setSimpleXPath(ss.str(), true);
    storeGameState();
}

void InfoManager::unlockHelp(int levelId)
{
    std::stringstream ss;
    ss << m_currentUserName << "/helps/help";
    if (levelId < 10)
        ss << "0";
    ss << levelId << "/shown";
    m_gameState.setSimpleXPath(ss.str(), false);
    storeGameState();
}

bool InfoManager::isHelpLocked(int levelId)
{
    std::stringstream ss;
    ss << m_currentUserName << "/helps/help";
    if (levelId < 10)
        ss << "0";
    ss << levelId << "/shown";
    return m_gameState.simpleXPathAsBool(ss.str(), true);
}

void InfoManager::lockMotion(const std::string& name)
{
    std::stringstream ss;
    ss << m_currentUserName << "/motion/" << name << "/locked";
    m_gameState.setSimpleXPath(ss.str(), true);
    storeGameState();
}

void InfoManager::unlockMotion(const std::string& name)
{
    std::stringstream ss;
    ss << m_currentUserName << "/motion/" << name << "/locked";
    m_gameState.setSimpleXPath(ss.str(), false);
    storeGameState();
}

bool InfoManager::isMotionLocked(const std::string& name)
{
    std::stringstream ss;
    ss << m_currentUserName << "/motion/" << name << "/locked";
    return m_gameState.simpleXPathAsBool(ss.str(), true);
}

bool InfoManager::currentUserHasRatedApp()
{
    std::stringstream ss;
    ss << m_currentUserName << "/rate/app-rated";
    return m_gameState.simpleXPathAsBool(ss.str(), false);
}

bool InfoManager::rateDialogMustAppearInMenu()
{
    std::stringstream ss;
    
    ss << m_currentUserName << "/rate/open-times";
    int openTimes = m_gameState.simpleXPathAsInt(ss.str(), 0);
    if (openTimes < m_ratingInfo.openTimes())
        return false;

    ss.str("");
    ss << m_currentUserName << "/rate/app-rated";
    bool appRated = m_gameState.simpleXPathAsBool(ss.str(), false);
    
    ss.str("");
    ss << m_currentUserName << "/rate/no-thanks";
    bool noThanks = m_gameState.simpleXPathAsBool(ss.str(), false);

    return ! (appRated || noThanks);
}

bool InfoManager::rateDialogMustAppearInLevels()
{
    std::stringstream ss;
    
    ss << m_currentUserName << "/rate/app-rated";
    bool appRated = m_gameState.simpleXPathAsBool(ss.str(), false);
    
    ss.str("");
    ss << m_currentUserName << "/rate/no-thanks";
    bool noThanks = m_gameState.simpleXPathAsBool(ss.str(), false);

    return ! (appRated || noThanks);
}

void InfoManager::rateIncrementOpenTimes()
{
    std::stringstream ss;
    ss << m_currentUserName << "/rate/open-times";
    int openTimes = m_gameState.simpleXPathAsInt(ss.str(), 0);
    m_gameState.setSimpleXPath(ss.str(), openTimes + 1);
}

void InfoManager::markAppRated()
{
    std::stringstream ss;
    ss << m_currentUserName << "/rate/app-rated";
    m_gameState.setSimpleXPath(ss.str(), true);
}

void InfoManager::ratedNoThanks()
{
    std::stringstream ss;
    ss << m_currentUserName << "/rate/no-thanks";
    m_gameState.setSimpleXPath(ss.str(), true);
}

void InfoManager::remindForRatingApp()
{
    std::stringstream ss;
    ss << m_currentUserName << "/rate/open-times";
    m_gameState.setSimpleXPath(ss.str(), 0);
}

StatParamKeyType InfoManager::statParamKeyFromName(const std::string& name) const
{
    std::map<std::string, StatParamKeyType>::const_iterator found = m_statParamKeyRelation.find(name);
    if (found == m_statParamKeyRelation.end())
        throw std::runtime_error("InfoManager::statParamKeyFromName name not found " + name);
    return found->second;
}

float InfoManager::statParamValue(StatParamKeyType key) const
{
    std::map<StatParamKeyType, StatParam>::const_iterator found = m_statParamValues.find(key);
    if (found == m_statParamValues.end())
        throw std::runtime_error("InfoManager::statParamValue: key not found " + key);
    return found->second.currentValue();
}

void InfoManager::setStatParamValue(StatParamKeyType key, float value)
{
    std::map<StatParamKeyType, StatParam>::iterator found = m_statParamValues.find(key);
    if (found == m_statParamValues.end())
        throw std::runtime_error("InfoManager::setStatParamValue: key not found " + key);
    return found->second.setCurrentValue(value);
}

void InfoManager::incrStatParamValue(StatParamKeyType key, float incr)
{
    std::map<StatParamKeyType, StatParam>::iterator found = m_statParamValues.find(key);
    if (found == m_statParamValues.end())
        throw std::runtime_error("InfoManager::setStatParamValue: key not found " + key);
    found->second.incrCurrentValue(incr);
}

void InfoManager::initGameCenter()
{
    if (m_gameCenterData != NULL)
        throw std::runtime_error("InfoManager::initGameCenter: cannot init GameCenter again");
    m_gameCenterData = gameCenterInit();
}

void InfoManager::authenticateLocalUser()
{
    gameCenterAuthenticateLocalUser(m_gameCenterData);
}

void InfoManager::updateAchievementPercentage(const std::string& achievementName, float percentage)
{
    if (m_gameCenterData == NULL)
        return;
    bool advice = m_achievementList.updateAchievementPercentage(achievementName + m_gameCenterSuffix, percentage);
    if (advice) {
        std::stringstream ss;
        ss << achievementName << "_TITLE";
        MessageKeyType key = Core::i18nManager().keyFromString(ss.str());
        Core::renderManager().showAchievementPage(Core::i18nManager().message(key));
    }
}

void InfoManager::receiveAchievementStatusFromGameCenter(const std::string& id, float percentage)
{
    if (m_gameCenterData == NULL)
        return;
    m_achievementList.receiveAchievementStatusFromGameCenter(id, percentage);
}

void InfoManager::updateLeaderboard(const std::string& leaderboardName, int value)
{
    if (m_gameCenterData == NULL)
        return;
    m_leaderboardList.updateLeaderboard(leaderboardName + m_gameCenterSuffix, value);
}

void InfoManager::synchronizeGameCenterInfo()
{
    if (m_gameCenterData == NULL)
        return;
    gameCenterSynchronizeAchievements(m_gameCenterData, m_achievementList.achievements());
    gameCenterSynchronizeLeaderboards(m_gameCenterData, m_leaderboardList.leaderboards());
}

void InfoManager::setHelpInfo(const std::string& sceneRef, int level, bool useMusicRef, const std::string& musicRef)
{
    m_helpInfo.setSceneRef(sceneRef);
    m_helpInfo.setLevel(level);
    m_helpInfo.setUseMusicRef(useMusicRef);
    m_helpInfo.setMusicRef(musicRef);
    m_helpInfo.setFromPause(false);
}

void InfoManager::setHelpUsingMusic(bool usingMusic)
{
    m_helpInfo.setUsingMusic(usingMusic);
}

std::string InfoManager::executeEL(const std::string& el, InfoScriptListener* listener)
{
    if (el[0] == '$') {
        const std::string paramName = el.substr(1);
        if (listener)
            return listener->infoParam(paramName);
        else
            return "";
    }
    
    if (el[0] == '@') {
        const std::string messageKey = el.substr(1);
        MessageKeyType key = Core::i18nManager().keyFromString(messageKey);
        return Core::i18nManager().message(key);
    }
    
    if (el[0] == '!') {
        const std::string script = el.substr(1);
        return executeScript(script, listener);
    }

    return el;
}

const std::string InfoManager::executeScript(const std::string& script, InfoScriptListener* listener)
{
    FunctionCallStatement functionCall;
    functionCall.init(script);
    if (functionCall.hasErrors())
        throw std::runtime_error("SceneTimeline::executeScript error at '" + script + "'");
    
    if (functionCall.matchWith("setParam", 2)) {
        if (listener)
            listener->infoScriptSetParam(functionCall.param(0), functionCall.param(1));
        return "";
    }

// SIMPLE

    if (functionCall.matchWith("none", 0))
        return "";

    if (functionCall.matchWith("not", 1)) {
        std::string result = executeEL(functionCall.param(0), listener);
        return result == "true" ? "false" : "true";
    }
    
    if (functionCall.matchWith("version", 0)) {
        return m_version;
    }
    
    if (functionCall.matchWith("longVersion", 0)) {
        std::stringstream ss;
        ss << "Version " << m_version;
        return ss.str();
    }

    if (functionCall.matchWith("equals", 2)) {
        std::string param1 = executeEL(functionCall.param(0), listener);
        std::string param2 = executeEL(functionCall.param(1), listener);
        return param1 == param2 ? "true" : "false";
    }
    
    if (functionCall.matchWith("concat", 2)) {
        std::string param1 = executeEL(functionCall.param(0), listener);
        std::string param2 = executeEL(functionCall.param(1), listener);
        return param1 + param2;
    }
    
// BUCLES

    if (functionCall.matchWith("if", 3)) {
        std::string condition = executeEL(functionCall.param(0), listener);
        if (condition == "true")
            return executeEL(functionCall.param(1), listener);
        else
            return executeEL(functionCall.param(2), listener);
    }
    
    if (functionCall.matchWith("combine", 2)) {
        std::string result = executeEL(functionCall.param(0), listener);
        return executeEL(functionCall.param(1), listener);
    }

// LEVEL INFO
    
    if (functionCall.matchWith("lockLevel", 1)) {
        Core::infoManager().lockLevel(functionCall.paramAsInt(0));
        return "";
    }
    
    if (functionCall.matchWith("unlockLevel", 1)) {
        Core::infoManager().unlockLevel(functionCall.paramAsInt(0));
        return "";
    }
    
    if (functionCall.matchWith("isLevelLocked", 1)) {
        bool result = Core::infoManager().isLevelLocked(functionCall.paramAsInt(0));
        return result ? "true" : "false";
    }

    if (functionCall.matchWith("isLevelUnlockedRecently", 1)) {
        bool result = Core::infoManager().isLevelUnlockedRecently(functionCall.paramAsInt(0));
        return result ? "true" : "false";
    }
    
    if (functionCall.matchWith("isLevelUnlockedRecentlyRange", 2)) {
        bool result = Core::infoManager().isLevelUnlockedRecentlyRange(functionCall.paramAsInt(0), functionCall.paramAsInt(1));
        return result ? "true" : "false";
    }
    
    if (functionCall.matchWith("clearLevelUnlockedRecentlyRange", 2)) {
        Core::infoManager().clearLevelUnlockedRecentlyRange(functionCall.paramAsInt(0), functionCall.paramAsInt(1));
        return "";
    }
    
// HELP INFO

    if (functionCall.matchWith("lockHelp", 1)) {
        Core::infoManager().lockHelp(functionCall.paramAsInt(0));
        return "";
    }
    
    if (functionCall.matchWith("unlockHelp", 1)) {
        Core::infoManager().unlockHelp(functionCall.paramAsInt(0));
        return "";
    }
    
    if (functionCall.matchWith("isHelpLocked", 1)) {
        bool result = Core::infoManager().isHelpLocked(functionCall.paramAsInt(0));
        return result ? "true" : "false";
    }
    
    if (functionCall.matchWith("setHelpFromPause", 1)) {
        m_helpInfo.setFromPause(functionCall.paramAsBool(0));
        return "";
    }
    
    if (functionCall.matchWith("currentHelpScene", 0))
        return m_helpInfo.sceneRef();
    
// I18N

    if (functionCall.matchWith("locale", 0))
        return localeToString(Core::i18nManager().locale());
        
    if (functionCall.matchWith("setLocale", 1)) {
        Core::i18nManager().setLocale(stringToLocale(functionCall.param(0)));
        return "";
    }

// SCENES
    
    if (functionCall.matchWith("switchToScene", 1)) {
        Core::sceneManager().switchToScene(functionCall.param(0));
        return "";
    }
    
    if (functionCall.matchWith("switchToScene", 2)) {
        Core::sceneManager().switchToScene(functionCall.param(0), functionCall.paramAsBool(1));
        return "";
    }
    
    if (functionCall.matchWith("switchToPopedScene", 0)) {
        Core::sceneManager().switchToPopedScene();
        return "";
    }
    
    if (functionCall.matchWith("switchToCurrentHelpScene", 0)) {
        Core::sceneManager().switchToScene(m_helpInfo.sceneRef(), false);
        return "";
    }
    
    if (functionCall.matchWith("pushAndSwitchToScene", 1)) {
        Core::sceneManager().pushAndSwitchToScene(functionCall.param(0));
        return "";
    }
    
    if (functionCall.matchWith("switchToPopedScene", 0)) {
        Core::sceneManager().switchToPopedScene();
        return "";
    }
    
// SOUND
    
    if (functionCall.matchWith("soundIsActive", 0)) {
        float volume = Core::soundManager().volume();
        return volume == 0 ? "false" : "true";
    }
    
    if (functionCall.matchWith("soundMute", 0)) {
        Core::soundManager().mute();
        return "";
    }
    
    if (functionCall.matchWith("soundUnmute", 0)) {
        Core::soundManager().unmute();
        return "";
    }
    
// URL

    if (functionCall.matchWith("openURL", 1)) {
        openURL(executeEL(functionCall.param(0), listener));
        return "";
    }

    if (functionCall.matchWith("openRateURL", 0)) {
        openURL(m_ratingInfo.traslatedUrl());
        return "";
    }
    
    if (functionCall.matchWith("buyButtonPressed", 0)) {
        return executeEL(m_buyButtonPressedScript);
    }
    
    if (functionCall.matchWith("openAppStoreFull", 0)) {
        openURL(m_ratingInfo.traslatedBuyFullUrl());
        return "";
    }
    
    if (functionCall.matchWith("openAppStoreLite", 0)) {
        openURL(m_ratingInfo.traslatedBuyLiteUrl());
        return "";
    }
    
// RATE APP

    if (functionCall.matchWith("currentUserHasRatedApp", 0))
        return currentUserHasRatedApp() ? "true" : "false";
    
    if (functionCall.matchWith("rateDialogMustAppearInMenu", 0))
        return rateDialogMustAppearInMenu() ? "true" : "false";
        
    if (functionCall.matchWith("rateDialogMustAppearInLevels", 0))
        return rateDialogMustAppearInLevels() ? "true" : "false";
        
    if (functionCall.matchWith("rateIncrementOpenTimes", 0)) {
        rateIncrementOpenTimes();
        return "";
    }

    if (functionCall.matchWith("markAppRated", 0)) {
        markAppRated();
        storeGameState();
        return "";
    }
    
    if (functionCall.matchWith("ratedNoThanks", 0)) {
        ratedNoThanks();
        storeGameState();
        return "";
    }
    
    if (functionCall.matchWith("remindForRatingApp", 0)) {
        remindForRatingApp();
        storeGameState();
        return "";
    }

// ERROR
    
    for(std::set<TemplateScriptFactory*>::const_iterator it = m_factories.begin(); it != m_factories.end(); it++) {
        TemplateScriptFactory* factory = *it;
        if (factory->canExecuteScript(functionCall, listener))
            return factory->executeScript(functionCall, listener);
    }
    
    throw std::runtime_error("SceneTimeline::executeScript error at '" + script + "'");
}

void InfoManager::debugResetRatingInfo()
{
    std::stringstream ss;
    
    ss << m_currentUserName << "/rate/open-times";
    m_gameState.setSimpleXPath(ss.str(), 0);
    
    ss.str("");
    ss << m_currentUserName << "/rate/app-rated";
    m_gameState.setSimpleXPath(ss.str(), false);
    
    ss.str("");
    ss << m_currentUserName << "/rate/no-thanks";
    m_gameState.setSimpleXPath(ss.str(), false);
}

