#include "Storage.h"
#include "config.h"
#include "AudioManager.h"



void Storage::init() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    nvs_handle_t nvs_handle;
    err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        Serial.println("Error opening NVS handle");
        return;
    }

    // Set default values if not already set
    int32_t value;
    err = nvs_get_i32(nvs_handle, "global_volume", &value);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        err = nvs_set_i32(nvs_handle, "global_volume", DEFAULT_VOLUME);
        if (err != ESP_OK) {
            Serial.println("Error setting default volume");
        }
    }

    err = nvs_get_i32(nvs_handle, "global_eq", &value);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        err = nvs_set_i32(nvs_handle, "global_eq", DEFAULT_EQUALIZER);
        if (err != ESP_OK) {
            Serial.println("Error setting default equalizer");
        }
    }

    nvs_commit(nvs_handle);
    nvs_close(nvs_handle);
}

void Storage::saveData(const char* key, int32_t value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    
    if (err != ESP_OK) {
        Serial.println("Error opening NVS handle for writing");
        return;
    }

    err = nvs_set_i32(nvs_handle, key, value);
    if (err != ESP_OK) {
        Serial.printf("Error saving data to NVS for key %s: %s\n", key, esp_err_to_name(err));
    } else {
        err = nvs_commit(nvs_handle);
        if (err == ESP_OK) {
            Serial.printf("Data successfully committed to NVS for key: %s, value: %d\n", key, value);
        } else {
            Serial.printf("Error committing data to NVS: %s\n", esp_err_to_name(err));
        }
    }
    
    nvs_close(nvs_handle);
}

int32_t Storage::getData(const char* key, int32_t defaultValue) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) {
        Serial.printf("Error opening NVS handle for reading: %s\n", esp_err_to_name(err));
        return defaultValue;
    }

    int32_t value;
    err = nvs_get_i32(nvs_handle, key, &value);
    if (err != ESP_OK) {
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            Serial.printf("Key %s not found, using default value: %d\n", key, defaultValue);
        } else {
            Serial.printf("Error reading %s: %s, using default value: %d\n", key, esp_err_to_name(err), defaultValue);
        }
        value = defaultValue;
    } else {
        Serial.printf("Successfully read %s: %d\n", key, value);
    }

    nvs_close(nvs_handle);
    return value;
}

void Storage::clearData(const char* key) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    if (err == ESP_OK) {
        nvs_erase_key(nvs_handle, key);
        nvs_commit(nvs_handle);
        nvs_close(nvs_handle);
    }
}

String Storage::addAlarm(const String& existingJson, const String& newJson) {
    JsonDocument doc;

    if (existingJson.length() > 0) {
        deserializeJson(doc, existingJson);
    } else {
        doc.to<JsonArray>();
    }

    JsonDocument newDoc;
    deserializeJson(newDoc, newJson);
    JsonObject newData = newDoc.as<JsonObject>();

    newData["id"] = doc.size() + 1;
    bool isActive = newData["active"]; 
    newData["last_triggered"] = ""; 

    JsonObject orderedData = doc.add<JsonObject>();
    orderedData["id"] = newData["id"];
    orderedData["active"] = isActive;
    orderedData["label"] = newData["label"];
    orderedData["time"] = newData["time"];
    orderedData["repeat"] = newData["repeat"];
    orderedData["relays"] = newData["relays"];
    orderedData["ringtone"] = newData["ringtone"];
    orderedData["last_triggered"] = newData["last_triggered"];

    String result;
    serializeJson(doc, result);
    return result;
}

String Storage::removeAlarmById(const String& existingJson, int id) {
    JsonDocument doc;
    deserializeJson(doc, existingJson);

    JsonArray dataArray = doc.as<JsonArray>();

    for (auto it = dataArray.begin(); it != dataArray.end(); ++it) {
        if ((*it)["id"] == id) {
            dataArray.remove(it);
            break;
        }
    }

    int newId = 1;
    for (JsonObject obj : dataArray) {
        obj["id"] = newId++;
    }

    String result;
    serializeJson(doc, result);
    return result;
}

void Storage::setGlobalVolume(uint8_t volume) {
    saveData("global_volume", int32_t(volume));
}

// Fungsi untuk menyimpan global equalizer
void Storage::setGlobalEqualizer(uint8_t equalizer) {
    saveData("global_eq", int32_t(equalizer));
}

uint8_t Storage::getGlobalVolume() {
    return (uint8_t)getData("global_volume", DEFAULT_VOLUME);
}

uint8_t Storage::getGlobalEqualizer() {
    return (uint8_t)getData("global_eq", DEFAULT_EQUALIZER);
}


// Fungsi untuk mendapatkan daftar ringtone dari storage atau AudioManager
String Storage::getRingtoneList() {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &nvs_handle);  // Membuka storage untuk baca/tulis
    if (err != ESP_OK) {
        Serial.println("Error opening NVS handle");
        return "[]";  // Nilai default jika terjadi kesalahan
    }

    size_t required_size;
    err = nvs_get_str(nvs_handle, "ringtone_list", nullptr, &required_size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        // Jika ringtone list belum ada di storage, ambil dari AudioManager
        Serial.println("Ringtone list not set, retrieving from AudioManager...");
        String ringtoneList = AudioManager::fileList();  // Mendapatkan ringtone list dari AudioManager

        // Simpan ringtone list ke storage
        err = nvs_set_str(nvs_handle, "ringtone_list", ringtoneList.c_str());
        if (err != ESP_OK) {
            Serial.println("Error saving ringtone list to NVS");
        }
        nvs_commit(nvs_handle);  // Commit perubahan
        nvs_close(nvs_handle);
        Serial.println("Saved ringtone list to storage: " + ringtoneList);
        return ringtoneList;  // Kembalikan ringtone list yang baru didapatkan
    }

    // Jika ringtone list ada di storage, ambil dari sana
    char* ringtoneList = new char[required_size];
    err = nvs_get_str(nvs_handle, "ringtone_list", ringtoneList, &required_size);
    if (err != ESP_OK) {
        Serial.println("Error reading ringtone list, using default");
        delete[] ringtoneList;
        return "[]";  // Nilai default jika terjadi kesalahan
    }

    String ringtoneListStr = String(ringtoneList);
    delete[] ringtoneList;
    nvs_close(nvs_handle);
    // Serial.println("Get ringtone list from storage: " + ringtoneListStr);
    return ringtoneListStr;
}

String Storage::getStringData(const char* key, const char* defaultValue) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) {
        Serial.printf("Error opening NVS handle for reading: %s\n", esp_err_to_name(err));
        return String(defaultValue);
    }

    size_t required_size;
    err = nvs_get_str(nvs_handle, key, nullptr, &required_size);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        nvs_close(nvs_handle);
        return String(defaultValue);
    }

    char* value = new char[required_size];
    err = nvs_get_str(nvs_handle, key, value, &required_size);
    if (err != ESP_OK) {
        delete[] value;
        nvs_close(nvs_handle);
        return String(defaultValue);
    }

    String result(value);
    delete[] value;
    nvs_close(nvs_handle);
    return result;
}

void Storage::saveStringData(const char* key, const char* value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    
    if (err != ESP_OK) {
        Serial.println("Error opening NVS handle for writing");
        return;
    }

    err = nvs_set_str(nvs_handle, key, value);
    if (err != ESP_OK) {
        Serial.printf("Error saving string data to NVS for key %s: %s\n", key, esp_err_to_name(err));
    } else {
        err = nvs_commit(nvs_handle);
        if (err == ESP_OK) {
            Serial.printf("String data successfully committed to NVS for key: %s\n", key);
        } else {
            Serial.printf("Error committing string data to NVS: %s\n", esp_err_to_name(err));
        }
    }
    
    nvs_close(nvs_handle);
}

// Fungsi untuk menampilkan seluruh key:value dari NVS
String Storage::listAllData() {
    nvs_handle handle;
    esp_err_t err;

    // Membuka NVS namespace
    err = nvs_open("storage", NVS_READONLY, &handle);
    if (err != ESP_OK) {
        return "Error opening NVS handle!";
    }

    size_t required_size;
    nvs_iterator_t it = nvs_entry_find(NVS_DEFAULT_PART_NAME, "storage", NVS_TYPE_ANY);
    String result = "";

    // Enumerasi key-value dari NVS
    while (it != NULL) {
        nvs_entry_info_t info;
        nvs_entry_info(it, &info);
        result += String(info.key) + ": ";

        // Mengambil tipe data dari key
        if (info.type == NVS_TYPE_I32) {
            int32_t value;
            nvs_get_i32(handle, info.key, &value);
            result += String(value);
        } else if (info.type == NVS_TYPE_STR) {
            // Mengambil ukuran string yang dibutuhkan
            nvs_get_str(handle, info.key, NULL, &required_size);
            char* value = (char*)malloc(required_size);
            nvs_get_str(handle, info.key, value, &required_size);
            result += String(value);
            free(value);
        }

        result += "\n";
        it = nvs_entry_next(it); // Lanjutkan ke entri berikutnya
    }

    nvs_close(handle);
    return result;
}