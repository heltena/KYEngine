#include <KYEngine/Private/Natives/KYEngineGameCenterAdapter.h>
#import <KYEngine/Private/Natives/KYEngineGameCenterController.h>

KYEngineGameCenterData gameCenterInit()
{
    KYEngineGameCenterController* data = [[KYEngineGameCenterController alloc] init];
    return (KYEngineGameCenterData) data;
}

void gameCenterAuthenticateLocalUser(KYEngineGameCenterData data)
{
    if (data == NULL)
        return;
    KYEngineGameCenterController* controller = (KYEngineGameCenterController*) data;
    [controller authenticateLocalUser];
}

void gameCenterSynchronizeAchievements(KYEngineGameCenterData data, const std::set<Achievement>& achievements)
{
    KYEngineGameCenterController* controller = (KYEngineGameCenterController*) data;
    for (std::set<Achievement>::const_iterator it = achievements.begin(); it != achievements.end(); it++) {
        const Achievement& achievement = *it;
        NSString* str = [NSString stringWithFormat:@"%s", achievement.id().c_str()];
        [controller submitAchievement:str percentComplete:achievement.percentage()];
    }
}

void gameCenterSynchronizeLeaderboards(KYEngineGameCenterData data, const std::set<Leaderboard>& leaderboards)
{
    KYEngineGameCenterController* controller = (KYEngineGameCenterController*) data;
    for (std::set<Leaderboard>::const_iterator it = leaderboards.begin(); it != leaderboards.end(); it++) {
        const Leaderboard& leaderboard = *it;
        NSString* str = [NSString stringWithFormat:@"%s", leaderboard.id().c_str()];
        [controller reportScore:leaderboard.value() forCategory:str];
    }
}