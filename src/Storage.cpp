#include "Storage.h"

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

    JsonObject orderedData = doc.add<JsonObject>();
    orderedData["id"] = newData["id"];
    orderedData["label"] = newData["label"];
    orderedData["time"] = newData["time"];
    orderedData["repeat"] = newData["repeat"];
    orderedData["ringtone"] = newData["ringtone"];

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