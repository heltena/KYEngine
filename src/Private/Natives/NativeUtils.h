#pragma once

#include <KYEngine/KYLocale.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

#include <string>

typedef void* MusicData;

void nativeUtilsInit();

MusicData musicLoad(const std::string& filename, float volume, bool initialLoop);
void musicUnload(MusicData data);
void musicPlay(MusicData data, float volume, double atTime);
void musicSetVolume(MusicData data, float volume);
void musicSetLoop(MusicData data, bool loop);
bool musicLoop(MusicData data);
double musicCurrentTime(MusicData data);
double musicDuration(MusicData data);
void musicStop(MusicData data);
bool musicIsPlaying(MusicData data);

std::string currentCountry();
LocaleType currentLocale();

std::string filenamePath(const std::string& filename);
std::string documentPath(const std::string& docname);
bool documentExists(const std::string& docname);
void copyFileToDocument(const std::string& filename, const std::string& docname);
/*
void* loadPVRTexture(const std::string& filename);
void unloadPVRTexture(void* pvrTexture);
int createTextureIdFromPVR(void* pvrTexture);

bool openGLExtensionSupported(const std::string& extension);
*/

void openURL(const std::string& url);

int getFreeMemory();
int getUsedMemory();

void accelerometerActivate();
void accelerometerDeactivate();