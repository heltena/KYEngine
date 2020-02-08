//
//  KYEngineGameCenterController.m
//  KYEngine
//
//  Created by Helio Tejedor on 12/12/11.
//  Copyright (c) 2011 Mifune Games. All rights reserved.
//

#import <KYEngine/Core.h>
#import <KYEngine/Private/Natives/KYEngineGameCenterController.h>

@implementation KYEngineGameCenterController

@synthesize gameCenterManager;

- (id) init
{
    if (self = [super init]) {
        if ([GameCenterManager isGameCenterAvailable]) {
            self.gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
            self.gameCenterManager.delegate = self;
        }
    }
    return self;
}

- (void) dealloc
{
    self.gameCenterManager = nil;
    [super dealloc];
}

+ (BOOL) isGameCenterAvailable
{
    return [GameCenterManager isGameCenterAvailable];
}

- (void) authenticateLocalUser
{
    [self.gameCenterManager authenticateLocalUser];
}

- (void) reportScore: (int64_t) score forCategory: (NSString*) category
{
    [self.gameCenterManager reportScore:score forCategory:category];
}

- (void) submitAchievement: (NSString*) identifier percentComplete: (double) percentComplete
{
    [self.gameCenterManager submitAchievement:identifier percentComplete:percentComplete];
}

#pragma mark GameCenterDelegateProtocol Methods

//Delegate method used by processGameCenterAuth to support looping waiting for game center authorization
//- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
//{
//	[self.gameCenterManager authenticateLocalUser];
//}
//
//- (void) processGameCenterAuth: (NSError*) error
//{
//	if(error == NULL)
//	{
//        // TODO: advice
//	}
//	else
//	{
//		UIAlertView* alert= [[[UIAlertView alloc] initWithTitle: @"Game Center Account Required" 
//									message: [NSString stringWithFormat: @"Reason: %@", [error localizedDescription]]
//									delegate: self cancelButtonTitle: @"Try Again..." otherButtonTitles: NULL] autorelease];
//		[alert show];
//	}
//	
//}
//
//- (void) scoreReported: (NSError*) error
//{
//    if (error == NULL)
//    {
//        NSLog(@"score reported!");
//    }
//    else
//    {
//        NSLog(@"Cannot report score, reason: %@", [error localizedDescription]);
//    }
//}
//
//- (void) achievementSubmitted: (GKAchievement*) ach error:(NSError*) error
//{
//    if (error == NULL)
//    {
//        NSLog(@"Achievement submitted!");
///*        char achievementId[50];
//        CFStringGetCString((CFStringRef) [ach identifier], achievementId, sizeof(achievementId), kCFStringEncodingUTF8);
//        double d = [ach percentComplete];
//        Core::infoManager().receiveAchievementStatusFromGameCenter(achievementId, d);
//*/    }
//    else
//    {
//        NSLog(@"Cannot submit achievement, reason: %@", [error localizedDescription]);
//    }
//}


@end
