//
//  KYEngineGameCenterController.h
//  KYEngine
//
//  Created by Helio Tejedor on 12/12/11.
//  Copyright (c) 2011 Mifune Games. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <KYEngine/Private/Natives/GameCenterManager.h>

@interface KYEngineGameCenterController : NSObject <GameCenterManagerDelegate> {
    GameCenterManager *gameCenterManager;
}

@property (retain, nonatomic) GameCenterManager *gameCenterManager;

- (id) init;

+ (BOOL) isGameCenterAvailable;
- (void) authenticateLocalUser;
- (void) reportScore: (int64_t) score forCategory: (NSString*) category;
- (void) submitAchievement: (NSString*) identifier percentComplete: (double) percentComplete;

@end
