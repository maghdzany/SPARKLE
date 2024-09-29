#include "Storage.h"
#include "config.h"

void Storage::init() {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
}

void Storage::saveData(const char* key, const String& json) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    if (err == ESP_OK) {
        nvs_set_str(nvs_handle, key, json.c_str());
        nvs_commit(nvs_handle);
        nvs_close(nvs_handle);
    }
}

String Storage::getData(const char* key) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    size_t required_size = 0;
    nvs_get_str(nvs_handle, key, NULL, &required_size);

    if (required_size == 0) {
        nvs_close(nvs_handle);
        return String("[]");
    }

    char* value = new char[required_size];
    nvs_get_str(nvs_handle, key, value, &required_size);
    String result = String(value);
    delete[] value;
    nvs_close(nvs_handle);
    return result;
}

void Storage::deleteData(const char* key) {
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

    // Ensure active is taken from newJson, not hardcoded to false
    bool isActive = newData["active"]; // Correctly assign from input JSON
    newData["last_triggered"] = ""; // Placeholder for last triggered time

    JsonObject orderedData = doc.add<JsonObject>();
    orderedData["id"] = newData["id"];
    orderedData["active"] = isActive; // Use the correct value from newData
    orderedData["label"] = newData["label"];
    orderedData["time"] = newData["time"];
    orderedData["repeat"] = newData["repeat"];
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

void Storage::setGlobalVolume(int volume) {
    saveData("global_volume", String(volume));
}

int Storage::getGlobalVolume() {
    String volumeStr = getData("global_volume");
    return volumeStr.toInt();
}

void Storage::setDefaultVolume() {
    int volume = getGlobalVolume(); // Cek apakah volume sudah ada di NVS
    if (volume == 0) { // Jika belum ada, gunakan default dari config.h
        saveData("global_volume", String(DEFAULT_VOLUME));
    }
}