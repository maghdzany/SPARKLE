#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "AudioManager.h"
#include "config.h"

DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void AudioManager::init() {
    Serial2.begin(9600, SERIAL_8N1, RX_AUDIO, TX_AUDIO);  // For ESP32

    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
    
    if (!myDFPlayer.begin(Serial2, true, true)) {
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while (true) {
            delay(10);
        }
    }
    Serial.println(F("DFPlayer Mini online."));
    
    myDFPlayer.volume(DEFAULT_VOLUME);  // Set volume value (0-30)
}

void AudioManager::handlePlay(int trackNumber) {
    myDFPlayer.play(trackNumber);
}

void AudioManager::handleVolume(int volume) {
    myDFPlayer.volume(volume);
}

void AudioManager::handleVolumeUp() {
    int currentVolume = myDFPlayer.readVolume();
    if (currentVolume < 30) {  // Max volume is 30
        myDFPlayer.volume(currentVolume + 1);
    }
}

void AudioManager::handleVolumeDown() {
    int currentVolume = myDFPlayer.readVolume();
    if (currentVolume > 0) {  // Min volume is 0
        myDFPlayer.volume(currentVolume - 1);
    }
}

void AudioManager::handleMute() {
    myDFPlayer.volume(0);  // Mute by setting volume to 0
}

void AudioManager::handleUnmute() {
    
    myDFPlayer.volume(DEFAULT_VOLUME);  // Unmute by restoring default volume
}

void AudioManager::handleEqualizer(uint8_t eq) {
    myDFPlayer.EQ(eq);  // Set equalizer
}

String AudioManager::handleReadEqualizer() {
    uint8_t eqValue = myDFPlayer.readEQ();  // Mendapatkan nilai equalizer
    switch (eqValue) {
        case DFPLAYER_EQ_NORMAL: return "NORMAL";
        case DFPLAYER_EQ_POP: return "POP";
        case DFPLAYER_EQ_ROCK: return "ROCK";
        case DFPLAYER_EQ_JAZZ: return "JAZZ";
        case DFPLAYER_EQ_CLASSIC: return "CLASSIC";
        case DFPLAYER_EQ_BASS: return "BASS";
        default: return "UNKNOWN";  // Jika tidak ada yang cocok
    }
}


String AudioManager::handleCurrentTrack() {
    return String(myDFPlayer.readCurrentFileNumber());  // Return current track number
}

String AudioManager::handleListTracks() {
    String trackList = "[";
    int count = myDFPlayer.readFileCounts();
    for (int i = 1; i <= count; i++) {
        trackList += "\"" + padWithZeros(i, 4) + "\"";  // Format: 0001, 0002, etc.
        if (i < count) trackList += ",";
    }
    trackList += "]";  // Menutup array JSON
    return trackList;  // Mengembalikan daftar track dalam format JSON
}


String AudioManager::padWithZeros(int number, int length) {
    String padded = String(number);
    while (padded.length() < length) {
        padded = "0" + padded;  // Menambahkan nol di depan
    }
    return padded;
}


// void loop()
// {
//   if (myDFPlayer.available()) {
//     printDetail(myDFPlayer.readType(), myDFPlayer.read());
//   }
// }

// void printDetail(uint8_t type, int value){
//   switch (type) {
//     case TimeOut:
//       Serial.println(F("Time Out!"));
//       break;
//     case WrongStack:
//       Serial.println(F("Stack Wrong!"));
//       break;
//     case DFPlayerCardInserted:
//       Serial.println(F("Card Inserted!"));
//       break;
//     case DFPlayerCardRemoved:
//       Serial.println(F("Card Removed!"));
//       break;
//     case DFPlayerCardOnline:
//       Serial.println(F("Card Online!"));
//       break;
//     case DFPlayerPlayFinished:
//       Serial.print(F("Number:"));
//       Serial.print(value);
//       Serial.println(F(" Play Finished!"));
//       break;
//     case DFPlayerError:
//       Serial.print(F("DFPlayerError:"));
//       switch (value) {
//         case Busy:
//           Serial.println(F("Card not found"));
//           break;
//         case Sleeping:
//           Serial.println(F("Sleeping"));
//           break;
//         case SerialWrongStack:
//           Serial.println(F("Get Wrong Stack"));
//           break;
//         case CheckSumNotMatch:
//           Serial.println(F("Check Sum Not Match"));
//           break;
//         case FileIndexOut:
//           Serial.println(F("File Index Out of Bound"));
//           break;
//         case FileMismatch:
//           Serial.println(F("Cannot Find File"));
//           break;
//         case Advertise:
//           Serial.println(F("In Advertise"));
//           break;
//         default:
//           break;
//       }
//       break;
//     default:
//       break;
//   }
// }