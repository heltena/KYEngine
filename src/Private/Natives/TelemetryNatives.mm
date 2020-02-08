#import <KYEngine/Private/Natives/TelemetryNatives.h>

NSString* nsAccountID = NULL;
int curDispatchPeriod = -1;

void telemetryReconnect();

void telemetryReconnect()
{
//    dispatch_async(dispatch_get_main_queue(), ^(void) {
//        [[GANTracker sharedTracker] stopTracker];
//        [[GANTracker sharedTracker] startTrackerWithAccountID: nsAccountID
//                                               dispatchPeriod: curDispatchPeriod
//                                                     delegate: nil];
////        [[GANTracker sharedTracker] setDebug:YES];
//    });    
}

void telemetryStartTracking(const std::string& accountID, int dispatchPeriod)
{
//    nsAccountID = [[NSString stringWithFormat:@"%s", accountID.c_str()] retain];
//    curDispatchPeriod = dispatchPeriod;
//    dispatch_async(dispatch_get_main_queue(), ^(void) {
//        [[GANTracker sharedTracker] startTrackerWithAccountID: nsAccountID
//                                               dispatchPeriod: curDispatchPeriod
//                                                     delegate: nil];
////        [[GANTracker sharedTracker] setDebug:YES];
//    });
}

void telemetryStopTracking()
{
//    dispatch_async(dispatch_get_main_queue(), ^(void) {
//        [[GANTracker sharedTracker] stopTracker];
//    });
}

void telemetryTrackPageView(const std::string& pageURL)
{
//    NSString* nsPageURL = [NSString stringWithFormat:@"%s", pageURL.c_str()];
//    dispatch_async(dispatch_get_main_queue(), ^(void) {
//        NSError* error;
//        BOOL result = [[GANTracker sharedTracker] trackPageview:nsPageURL withError:&error];
//        if (! result) {
//            NSLog(@"GANTracker error (pageView): %@",error);
//            telemetryReconnect();
//        }
//    });
}

void telemetryTrackEvent(const std::string& category, const std::string& action, const std::string& label, int value)
{
//    NSString* nsCategory = [NSString stringWithFormat:@"%s", category.c_str()];
//    NSString* nsAction = [NSString stringWithFormat:@"%s", action.c_str()];
//    NSString* nsLabel = [NSString stringWithFormat:@"%s", label.c_str()];
//    
//    dispatch_async(dispatch_get_main_queue(), ^(void) {
//        NSError* error;
//        BOOL result = [[GANTracker sharedTracker] trackEvent: nsCategory
//                                                      action: nsAction
//                                                       label: nsLabel
//                                                       value: value
//                                                   withError: &error];
//        if (! result) {
//            NSLog(@"GANTracker error (trackEvent): %@",error);
//            telemetryReconnect();
//        }
//    });
}

void telemetryDispatchInfo()
{
//    dispatch_async(dispatch_get_main_queue(), ^(void) {
//        [[GANTracker sharedTracker] dispatch];
//    });
}