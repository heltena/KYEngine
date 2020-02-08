#import <KYEngine/Private/Natives/NativeUtils.h>
//#import "PVRTexture.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVAudioPlayer.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

#import <mach/mach.h>
#import <mach/mach_host.h>

NSString* pathFromFilename(const std::string& filename);
NSString* pathFromDocument(NSFileManager* fileManager, const std::string& docname);

NSMutableDictionary *musicDictionary;
int nextMusicId;

void nativeUtilsInit()
{
    musicDictionary = [[NSMutableDictionary alloc] init];
    nextMusicId = 1; // don't set '0' --> is null!
}

NSString* pathFromFilename(const std::string& filename)
{
	NSString *str = [NSString stringWithFormat:@"%s", filename.c_str()];
    NSString *res = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:str];
    return res;
}

NSString* pathFromDocument(NSFileManager* fileManager, const std::string& docname)
{
	NSString *filenameStr = [NSString stringWithFormat:@"%s", docname.c_str()];
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return [documentsDirectory stringByAppendingPathComponent:filenameStr];
}

MusicData musicLoad(const std::string& filename, float volume, bool initialLoop)
{
    NSString *filePath = pathFromFilename(filename);
    
	NSURL *url = [NSURL fileURLWithPath:filePath];

	AVAudioPlayer* player;
	NSError *error;
	player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];
	
	if(! player)
		throw std::runtime_error("musicLoad cannot load: " + filename);
	
    [player prepareToPlay];
	[player setNumberOfLoops: initialLoop ? -1 : 0];
	[player setVolume:volume];
	
    int musicId = nextMusicId++;

    [musicDictionary setObject:player forKey:[NSNumber numberWithInt:musicId]];

    return (MusicData) musicId;
}

void musicUnload(MusicData data)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
	[player stop];
	[player release];
    [musicDictionary removeObjectForKey:musicId];
}

void musicPlay(MusicData data, float volume, double atTime)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
    player.volume = volume;
    player.currentTime = atTime;
    [player play];
}

void musicSetVolume(MusicData data, float volume)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
    [player setVolume:volume];    
}

void musicSetLoop(MusicData data, bool loop)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
    [player setNumberOfLoops: loop ? -1 : 0];
}

bool musicLoop(MusicData data)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
    bool result = [player numberOfLoops] == -1;
    return result;
}

double musicCurrentTime(MusicData data)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
    double result = [player currentTime];
    return result;
}

double musicDuration(MusicData data)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
    double result = [player duration];
    return result;
}

void musicStop(MusicData data)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
	[player stop];
}

bool musicIsPlaying(MusicData data)
{
    id musicId = [NSNumber numberWithInt:(int) data];
    AVAudioPlayer* player = [musicDictionary objectForKey:musicId];
    bool result = [player isPlaying];    
    return result;
}

std::string currentCountry()
{
    CFLocaleRef locale = CFLocaleCopyCurrent();
    CFTypeRef countryType = CFLocaleGetValue(locale, kCFLocaleCountryCode);

    if (CFGetTypeID(countryType) != CFStringGetTypeID())
        return "us";
    
    char countryName[50];
	CFStringGetCString((CFStringRef) countryType, countryName, sizeof(countryName), kCFStringEncodingUTF8);
	std::string result = countryName;
    
    CFRelease(locale);
    
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

LocaleType currentLocale()
{
	CFArrayRef languages = CFLocaleCopyPreferredLanguages();
	CFStringRef lang = (CFStringRef) CFArrayGetValueAtIndex(languages, 0);

	char localeName[50];
	CFStringGetCString((CFStringRef) lang, localeName, sizeof(localeName), kCFStringEncodingUTF8);
	std::string result = localeName;
    CFRelease(languages);
    
    std::cout << "Read locale from iOS: " << result << std::endl;
    
	if (result == "es" || result == "ca")
		return SPANISH;
	else if (result == "fr")
        return FRENCH;
    else if (result == "it")
        return ITALIAN;
    else if (result == "de")
        return GERMAN;
    else
		return ENGLISH;
}

std::string filenamePath(const std::string& filename)
{
    return [pathFromFilename(filename) UTF8String];
}

std::string documentPath(const std::string& docname)
{
    NSFileManager* fileManager = [[[NSFileManager alloc] init] autorelease];
    return [pathFromDocument(fileManager, docname) UTF8String];
}

bool documentExists(const std::string& docname)
{
    NSFileManager* fileManager = [[[NSFileManager alloc] init] autorelease];
    NSString* path = pathFromDocument(fileManager, docname);
    return [fileManager fileExistsAtPath:path] == YES;
}

void copyFileToDocument(const std::string& filename, const std::string& docname)
{
    NSFileManager* fileManager = [[[NSFileManager alloc] init] autorelease];
    NSString* filepath = pathFromFilename(filename);
    NSString* docpath = pathFromDocument(fileManager, docname);
    
    NSError* error;
    BOOL success = [fileManager copyItemAtPath:filepath toPath:docpath error:&error];
    if (!success)
        throw std::runtime_error("copyFileToDocument error");
}
/*
void* loadPVRTexture(const std::string& filename)
{
	NSString *filePath = [NSString stringWithFormat:@"%@/%s", 
						  [[NSBundle mainBundle]resourcePath],
						  filename.c_str()];
	
	NSURL *url = [NSURL fileURLWithPath:filePath];
    
    PVRTexture* texture = [PVRTexture pvrTextureWithContentsOfURL:url];
    return texture;
}

void unloadPVRTexture(void* pvrTexture)
{
    PVRTexture* texture = (PVRTexture*) pvrTexture;
    [texture release];
}

int createTextureIdFromPVR(void* pvrTexture)
{
    PVRTexture* texture = (PVRTexture*) pvrTexture;
    if ([texture createGLTexture])
        return [texture name];
    throw std::runtime_error("Cannot create GL texture");
}

bool openGLExtensionSupported(const std::string& extension)
{
	NSString *extensionsString = [NSString stringWithCString:(char *)glGetString(GL_EXTENSIONS) encoding:NSUTF8StringEncoding];
	NSArray *extensionsNames = [extensionsString componentsSeparatedByString:@" "];
	NSString* extName = [NSString stringWithFormat:@"%s", extension.c_str()];
	return [extensionsNames containsObject:extName] == YES;
}*/

void openURL(const std::string& url)
{
    std::cout << "openURL: " << url << std::endl;
    NSString* strUrl = [NSString stringWithFormat:@"%s", url.c_str()];
    NSURL* obUrl = [NSURL URLWithString: strUrl];
    [[UIApplication sharedApplication] openURL:obUrl];
}

int getFreeMemory()
{
    mach_port_t host_port;
    mach_msg_type_number_t host_size;
    vm_size_t pagesize;
    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);
    vm_statistics_data_t vm_stat;
    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS) {
        NSLog(@"Failed to fetch vm statistics");
        return 0;
    }
    /* Stats in bytes */
//    natural_t mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;    
    natural_t mem_free = vm_stat.free_count * pagesize;
    return mem_free;
}

int getUsedMemory()
{
    mach_port_t host_port;
    mach_msg_type_number_t host_size;
    vm_size_t pagesize;
    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);
    vm_statistics_data_t vm_stat;
    if (host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) != KERN_SUCCESS) {
        NSLog(@"Failed to fetch vm statistics");
        return 0;
    }
    /* Stats in bytes */
    natural_t mem_used = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.wire_count) * pagesize;    
//    natural_t mem_free = vm_stat.free_count * pagesize;
    return mem_used;
}

void accelerometerActivate()
{
    id delegate = [[UIApplication sharedApplication] delegate];
	[[UIAccelerometer sharedAccelerometer] setDelegate:delegate];
	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:1.0f/60.0f];
}

void accelerometerDeactivate()
{
    [[UIAccelerometer sharedAccelerometer] setDelegate:nil];
}
