#pragma once

#include <KYEngine/Private/Achievement.h>
#include <KYEngine/Private/Leaderboard.h>

#include <set>

typedef void* KYEngineGameCenterData;

KYEngineGameCenterData gameCenterInit();
void gameCenterAuthenticateLocalUser(KYEngineGameCenterData data);
void gameCenterSynchronizeAchievements(KYEngineGameCenterData data, const std::set<Achievement>& achievements);
void gameCenterSynchronizeLeaderboards(KYEngineGameCenterData data, const std::set<Leaderboard>& leaderboards);