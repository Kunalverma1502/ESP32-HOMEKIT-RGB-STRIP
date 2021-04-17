/*
   builtin_led_accessory.c
   Define the accessory in pure C language using the Macro in characteristics.h

    Created on: 2021-04-10
        Author: KUNAL VERMA
*/

#include <Arduino.h>
#include <homekit/types.h>
#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <stdio.h>
#include <port.h>
#include <esp_wifi_types.h>
#include <esp_wifi.h>

static char ACCESSORY_NAME[32] = "ESP32_LED";

void accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");

}
homekit_characteristic_t cha_on = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "ESP8266 Lamp");
homekit_characteristic_t cha_bright = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 50);
homekit_characteristic_t cha_sat = HOMEKIT_CHARACTERISTIC_(SATURATION, (float) 0);
homekit_characteristic_t cha_hue = HOMEKIT_CHARACTERISTIC_(HUE, (float) 180);


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
      //Air Conditioners   SWITCH
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

void accessory_init() {
  //Rename ACCESSORY_NAME base on MAC address.
  uint8_t mac[6];
  esp_wifi_get_mac(WIFI_IF_STA, mac);
  sprintf(ACCESSORY_NAME, "ESP32_LED_%02X%02X%02X", mac[3], mac[4], mac[5]);
}
