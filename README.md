# ESP32-HOMEKIT-RGB-STRIP
**[Deprecated]** Native Apple HomeKit accessory implementation for the ESP32 Arduino core.

This Arduino library is a native Apple HomeKit accessory implementation for the [ESP32 Arduino core](https://github.com/espressif/arduino-esp32), and works without any additional bridges.

This library is the ESP32 version of [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)

## Notes

* This is a "only-can-work" version for ESP32, remains something to be optimized.

* The `WolfSSL` used for ESP32 is based on `4.3.0-stable` version with **Hardware Acceleration Support** (enabled by default).

* The HomeKit running on ESP32 has a **GREAT PERFORMANCE** which Pair-Setup can be done in ~1.2s and Pair-Verify in < 0.1s (10x faster than ESP8266).

* The HomeKit storage on ESP32 is based on `nvs`.

## Performance WITH Hardware Acceleration on ESP32

* Preinit: ~0.53s
* Pair Setup Step 1/3: ~0s (The heavy crypto computation is done in Preinit)
* Pair Setup Step 2/3: ~0.53s 
* Pair Setup Step 3/3: ~0.20s 
* Pair Verify Step 1/2: ~0.05s
* Pair Verify Step 2/2: ~0.02s

## Performance WITHOUT Hardware Acceleration on ESP32

* Preinit: ~2.2s
* Pair Setup Step 1/3: ~0s (The heavy crypto computation is done in Preinit)
* Pair Setup Step 2/3: ~2.5s 
* Pair Setup Step 3/3: ~0.1s 
* Pair Verify Step 1/2: ~0.06s
* Pair Verify Step 2/2: ~0.03s

## Manual Installation 

Refer to the official guide: [Manual installation](https://www.arduino.cc/en/guide/libraries#toc5)
Note: this library will not publish the release version for Arduino IDE. 


#### Manual Installation for Windows

1. Click on _"Clone or Download"_ button, then click _"[Download ZIP](https://github.com/Kunalverma1502/ESP32-HOMEKIT-RGB-STRIP/archive/refs/heads/main.zip)"_ on the page.
1. Extract the contents of the downloaded zip file.
1. Rename the extracted folder to _"Arduino-HomeKit-ESP32"_.
1. Move this folder to your libraries directory. (under windows: `C:\Users\<USERNAME>\Documents\Arduino\libraries\`)
1. Restart your Arduino IDE.
1. Check out the examples.

## CHANGE ACCESSORY  

```
homekit_accessory_t *accessories[] = {
  HOMEKIT_ACCESSORY(.id = 1, .category = homekit_accessory_category_lightbulb, .services = (homekit_service_t*[]) {
    HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics = (homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "LIGHTBULB"),
      HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arduino HomeKit"),
      HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
      HOMEKIT_CHARACTERISTIC(MODEL, "ESP32"),
      HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
      HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
      NULL
 
    }),
    HOMEKIT_SERVICE(LIGHTBULB, .primary = true, .characteristics = (homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "LIGHTBULB"),
                             &cha_on,
                             &cha_name,
                             &cha_bright,
                             &cha_sat,
                             &cha_hue,
                             NULL
    }),
    NULL
  }),
  NULL
};

homekit_server_config_t config = {
  .accessories = accessories,
  .password = "111-11-111",
  //.on_event = on_homekit_event,
  .setupId = "ABCD"
};
```

## Setup code of the example sketch

``111-11-111``




