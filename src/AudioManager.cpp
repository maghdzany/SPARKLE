#include "AudioManager.h"
#include <Arduino.h>
#include "config.h"
#include "Storage.h"

static DFRobotDFPlayerMini myDFPlayer;  // DFPlayer instance (harus statis di sini)

// Array of known file names
const char *fileNames[] = {
    "Alarm Clock", 
    "Beautiful Things",     
    "Demon Slayer Infinity",  
    "Genshin Intro",         
    "GTA SA",
    "Halloween Movie",
    "Iphone 13 Chamada",
    "Iphone Alarm",
    "Kamado Tanjiro no Uta",
    "Lantern Rite",
    "Super Mario",
    "Morning Alarm",
    "Morning Alarm 2",
    "Morning Flower",
    "Nana",
    "Super Mario 2",
    "Tetris",
    "The Best Alarm",
    "Vaders Theme",
    "Walk in the Forest"
};



// Inisialisasi DFPlayer
void AudioManager::init() {
    Serial1.begin(9600, SERIAL_8N1, 16, 17);  // ESP32 RX=16, TX=17

    if (!myDFPlayer.begin(Serial1)) {  // Memulai komunikasi dengan DFPlayer
        Serial.println(F("DFPlayer initialization failed!"));
        while (true) {
            delay(100);  // Mencegah looping tanpa jeda
        }
    }
    Serial.println(F("DFPlayer initialized."));

    
}


    

int AudioManager::fileCount() {
    return myDFPlayer.readFileCountsInFolder(1);  
}

String AudioManager::fileList()
{
  String fileList = "[";            // Awal list JSON
  int fileCount = AudioManager::fileCount(); // Baca jumlah file dari DFPlayer

  // Loop untuk setiap file dan format nama file dengan nomor urut
  for (int i = 1; i <= fileCount; i++)
  {
    String fileNumber = String(i); // Nomor file
    if (fileNumber.length() < 3)
    {
      // Tambahkan padding '0' agar format nomor menjadi 3 digit (001, 002, dll.)
      fileNumber = String("000").substring(0, 3 - fileNumber.length()) + fileNumber;
    }

    String fileName = getFileName(i); // Ambil nama file dari array

    // Tambahkan nama file ke dalam daftar dengan format "001 Nama File"
    fileList += "\"" + fileNumber + " " + fileName + "\"";

    // Jika ini bukan file terakhir, tambahkan koma sebagai pemisah
    if (i < fileCount)
    {
      fileList += ",";
    }
  }

  fileList += "]"; // Akhiri list JSON
  return fileList; // Kembalikan string berisi daftar file
}

const char* AudioManager::getFileName(int fileNumber) {
    // Hitung total file yang ada di array fileNames
    int totalFiles = sizeof(fileNames) / sizeof(fileNames[0]);
    
    // Pastikan nomor file berada di dalam jangkauan array
    if (fileNumber >= 1 && fileNumber <= totalFiles) {
        return fileNames[fileNumber - 1];  // Array 0-based, jadi fileNumber - 1
    } else {
        return "Untitled";  // Jika nomor file di luar jangkauan array
    }
}

// Function to convert ringtone number to DFPlayer file number
int convertRingtoneToFileNumber(int ringtoneNumber) {
    // Hitung total file yang ada di array fileNames
    int totalFiles = sizeof(fileNames) / sizeof(fileNames[0]);
    
    // Pastikan nomor ringtone berada dalam jangkauan file yang tersedia
    if (ringtoneNumber >= 1 && ringtoneNumber <= totalFiles) {
        return ringtoneNumber;  // DFPlayer uses 1-based numbering, so no need to adjust
    } else {
        // Jika nomor ringtone di luar jangkauan, default ke file pertama
        Serial.println("Invalid ringtone number, defaulting to 1");
        return 1;  // Default ke nomor file pertama
    }
}

// ============= MUSIC CONTROL =====================
void AudioManager::handlePlay(int trackNumber) {
    uint8_t storedVolume = Storage::getGlobalVolume();
    uint8_t storedEQ = Storage::getGlobalEqualizer();
    myDFPlayer.volume(storedVolume);
    myDFPlayer.EQ(storedEQ);

    // Konversi nomor ringtone ke nomor file yang benar (no need to adjust for DFPlayer)
    int fileNumber = convertRingtoneToFileNumber(trackNumber);
    
    Serial.print("Playing ringtone number: ");
    Serial.print(trackNumber);
    Serial.print(" (DFPlayer file number: ");
    Serial.print(fileNumber);
    Serial.println(")");
    
    myDFPlayer.play(fileNumber);  // Langsung mainkan file yang sesuai dengan penomoran 1-based
}

void AudioManager::handleStop()
{
  myDFPlayer.stop();
}

void AudioManager::handleVolume(uint8_t volume)
{
  myDFPlayer.volume(volume);
}

uint8_t AudioManager::readVolume()
{
  return myDFPlayer.readVolume();
}

void AudioManager::handleEqualizer(uint8_t eq)
{
  myDFPlayer.EQ(eq); // Set equalizer
}

uint8_t AudioManager::readEqualizer()
{
  return myDFPlayer.readEQ();
}
// =========================================================


void AudioManager::debugAudio()
{
  if (myDFPlayer.available())
  {
    AudioManager::printDetail(myDFPlayer.readType(), myDFPlayer.read());
  }
}

void printDetail(uint8_t type, int value)
{
  switch (type)
  {
  case TimeOut:
    Serial.println(F("Time Out!"));
    break;
  case WrongStack:
    Serial.println(F("Stack Wrong!"));
    break;
  case DFPlayerCardInserted:
    Serial.println(F("Card Inserted!"));
    break;
  case DFPlayerCardRemoved:
    Serial.println(F("Card Removed!"));
    break;
  case DFPlayerCardOnline:
    Serial.println(F("Card Online!"));
    break;
  case DFPlayerPlayFinished:
    Serial.print(F("Number:"));
    Serial.print(value);
    Serial.println(F(" Play Finished!"));
    break;
  case DFPlayerError:
    Serial.print(F("DFPlayerError:"));
    switch (value)
    {
    case Busy:
      Serial.println(F("Card not found"));
      break;
    case Sleeping:
      Serial.println(F("Sleeping"));
      break;
    case SerialWrongStack:
      Serial.println(F("Get Wrong Stack"));
      break;
    case CheckSumNotMatch:
      Serial.println(F("Check Sum Not Match"));
      break;
    case FileIndexOut:
      Serial.println(F("File Index Out of Bound"));
      break;
    case FileMismatch:
      Serial.println(F("Cannot Find File"));
      break;
    case Advertise:
      Serial.println(F("In Advertise"));
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}