#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "DFRobotDFPlayerMini.h"

class AudioManager
{
public:
    static void init();     
    static int fileCount(); 
    static String fileList();
    static const char *getFileName(int fileNumber);
    static void handlePlay(int trackNumber);
    static void handleStop();
    static void handleVolume(uint8_t volume);
    static uint8_t readVolume();
    static void handleEqualizer(uint8_t eq);
    static uint8_t readEqualizer();
    static void debugAudio();
    static void printDetail(uint8_t type, int value);
};

#endif // AUDIO_MANAGER_H
