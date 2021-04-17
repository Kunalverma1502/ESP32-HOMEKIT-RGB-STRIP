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


void accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");

}
homekit_characteristic_t cha_programmable_switch1_event = HOMEKIT_CHARACTERISTIC_(PROGRAMMABLE_SWITCH_EVENT, 0);
homekit_characteristic_t cha_programmable_switch2_event = HOMEKIT_CHARACTERISTIC_(PROGRAMMABLE_SWITCH_EVENT, 0);
homekit_characteristic_t cha_programmable_switch3_event = HOMEKIT_CHARACTERISTIC_(PROGRAMMABLE_SWITCH_EVENT, 0);
homekit_characteristic_t cha_programmable_switch4_event = HOMEKIT_CHARACTERISTIC_(PROGRAMMABLE_SWITCH_EVENT, 0);


homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_switch, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Stateless Programmable Switch"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "KUNAL VERMA"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "101199"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP32"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.1"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
    HOMEKIT_SERVICE(STATELESS_PROGRAMMABLE_SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
          HOMEKIT_CHARACTERISTIC(NAME, "Stateless Programmable Switch1"),
          &cha_programmable_switch1_event,
      NULL
    }),
        HOMEKIT_SERVICE(STATELESS_PROGRAMMABLE_SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
          HOMEKIT_CHARACTERISTIC(NAME, "Stateless Programmable Switch2"),
          &cha_programmable_switch2_event,
      NULL
    }),
        HOMEKIT_SERVICE(STATELESS_PROGRAMMABLE_SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
          HOMEKIT_CHARACTERISTIC(NAME, "Stateless Programmable Switch3"),
          &cha_programmable_switch3_event,
      NULL
    }),
        HOMEKIT_SERVICE(STATELESS_PROGRAMMABLE_SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
          HOMEKIT_CHARACTERISTIC(NAME, "Stateless Programmable Switch4"),
          &cha_programmable_switch4_event,
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
