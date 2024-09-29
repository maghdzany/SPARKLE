#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

class AudioManager {
public:
    static void init();
    static void handlePlay(int trackNumber);
    static void handleVolume(int volume);
    static void handleVolumeUp();
    static void handleVolumeDown();
    static void handleMute();
    static void handleUnmute();
    static void handleEqualizer(uint8_t eq);
    static String handleReadEqualizer();
    static String handleCurrentTrack();
    static String handleListTracks();
    static String padWithZeros(int number, int length);
};

#endif // AUDIO_MANAGER_H
