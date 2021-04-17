#include "Arduino.h"
#include "WiFi.h"
#include "arduino_homekit_server.h"
#include "ESPButton.h"

TaskHandle_t Task1;
TaskHandle_t Task2;


extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_programmable_switch1_event;
extern "C" homekit_characteristic_t cha_programmable_switch2_event;
extern "C" homekit_characteristic_t cha_programmable_switch3_event;
extern "C" homekit_characteristic_t cha_programmable_switch4_event;



uint8_t cha_value = 0;



#define HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_SINGLE_PRESS   0
#define HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_DOUBLE_PRESS   1
#define HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_LONG_PRESS     2

// Called when the value is read by iOS Home APP
homekit_value_t cha_programmable_switch1_event_getter() {
  // Should always return "null" for reading, see HAP section 9.75
  return HOMEKIT_NULL_CPP();
}
// Called when the value is read by iOS Home APP
homekit_value_t cha_programmable_switch2_event_getter() {
  // Should always return "null" for reading, see HAP section 9.75
  return HOMEKIT_NULL_CPP();
}
// Called when the value is read by iOS Home APP
homekit_value_t cha_programmable_switch3_event_getter() {
  // Should always return "null" for reading, see HAP section 9.75
  return HOMEKIT_NULL_CPP();
}
// Called when the value is read by iOS Home APP
homekit_value_t cha_programmable_switch4_event_getter() {
  // Should always return "null" for reading, see HAP section 9.75
  return HOMEKIT_NULL_CPP();
}


const char *ssid = "your_ssid";
const char *password = "your_password";

void clickEvent1() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_SINGLE_PRESS;
  cha_programmable_switch1_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch1_event,
                                cha_programmable_switch1_event.value);
  Serial.println("clickEvent1");
}
void doubleClickEvent1() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_DOUBLE_PRESS;
  cha_programmable_switch1_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch1_event,
                                cha_programmable_switch1_event.value);
  Serial.println("doubleClickEvent1");
}
void holdEvent1() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_LONG_PRESS;
  cha_programmable_switch1_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch1_event,
                                cha_programmable_switch1_event.value);
  Serial.println("holdEvent1");
}


void clickEvent2() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_SINGLE_PRESS;
  cha_programmable_switch2_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch2_event,
                                cha_programmable_switch2_event.value);
  Serial.println("clickEvent2");
}
void doubleClickEvent2() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_DOUBLE_PRESS;
  cha_programmable_switch2_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch2_event,
                                cha_programmable_switch2_event.value);
  Serial.println("doubleClickEvent2");
}
void holdEvent2() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_LONG_PRESS;
  cha_programmable_switch2_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch2_event,
                                cha_programmable_switch2_event.value);
  Serial.println("holdEvent2");
}

void clickEvent3() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_SINGLE_PRESS;
  cha_programmable_switch3_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch3_event,
                                cha_programmable_switch3_event.value);
  Serial.println("clickEvent3");
}
void doubleClickEvent3() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_DOUBLE_PRESS;
  cha_programmable_switch3_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch3_event,
                                cha_programmable_switch3_event.value);
  Serial.println("doubleClickEvent3");
}
void holdEvent3() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_LONG_PRESS;
  cha_programmable_switch3_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch3_event,
                                cha_programmable_switch3_event.value);
  Serial.println("holdEvent3");
}
void clickEvent4() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_SINGLE_PRESS;
  cha_programmable_switch4_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch4_event,
                                cha_programmable_switch4_event.value);
  Serial.println("clickEvent4");
}
void doubleClickEvent4() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_DOUBLE_PRESS;
  cha_programmable_switch4_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch4_event,
                                cha_programmable_switch4_event.value);
  Serial.println("doubleClickEvent4");
}
void holdEvent4() {
  cha_value = HOMEKIT_PROGRAMMABLE_SWITCH_EVENT_LONG_PRESS;
  cha_programmable_switch4_event.value.uint8_value = cha_value;
  homekit_characteristic_notify(&cha_programmable_switch4_event,
                                cha_programmable_switch4_event.value);
  Serial.println("holdEvent4");
}

void Task1code( void * parameter) {
  for (;;) {
    int a = checkButton();
    if (a == 5) clickEvent1();
    if (a == 6) doubleClickEvent1();
    if (a == 7) holdEvent1();

    if (a == 10) clickEvent2();
    if (a == 12) doubleClickEvent2();
    if (a == 14) holdEvent2();

    if (a == 15) clickEvent3();
    if (a == 18) doubleClickEvent3();
    if (a == 21) holdEvent3();

    if (a == 20) clickEvent4();
    if (a == 24) doubleClickEvent4();
    if (a == 28) holdEvent4();
  }
}

// using core 0 for making sure wifi always remains connected
//https://randomnerdtutorials.com/solved-reconnect-esp32-to-wifi/
void Task2code( void * parameter) {
  for (;;) {
        unsigned long currentMillis = millis();
    // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
      Serial.print(millis());
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
      previousMillis = currentMillis;
    }
  }
  }



void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  printf("\n");
  printf("SketchSize: %d B\n", ESP.getSketchSize());
  printf("FreeSketchSpace: %d B\n", ESP.getFreeSketchSpace());
  printf("FlashChipSize: %d B\n", ESP.getFlashChipSize());
  //printf("FlashChipRealSize: %d B\n", ESP.getFlashChipRealSize());
  printf("FlashChipSpeed: %d\n", ESP.getFlashChipSpeed());
  printf("SdkVersion: %s\n", ESP.getSdkVersion());
  //printf("FullVersion: %s\n", ESP.getFullVersion().c_str());
  //printf("CpuFreq: %dMHz\n", ESP.getCpuFreqMHz());
  printf("FreeHeap: %d B\n", ESP.getFreeHeap());
  //printf("ResetInfo: %s\n", ESP.getResetInfo().c_str());
  //printf("ResetReason: %s\n", ESP.getResetReason().c_str());
  DEBUG_HEAP();

  //Init Button
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  homekit_setup();
  xTaskCreatePinnedToCore(
    Task1code, /* Function to implement the task */
    "Task1", /* Name of the task */
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    0,  /* Priority of the task */
    &Task1,  /* Task handle. */
    0); /* Core where the task should run */
delay(500);
      xTaskCreatePinnedToCore(
    Task2code, /* Function to implement the task */
    "Task2", /* Name of the task */
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    0,  /* Priority of the task */
    &Task2,  /* Task handle. */
    0); /* Core where the task should run */
}



void loop() {
//my_homekit_report();
  uint32_t time = millis();
  static uint32_t next_heap_millis = 0;
  if (time > next_heap_millis) {
    INFO("heap: %u, sockets: %d", ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
    next_heap_millis = time + 5000;
  }
  delay(5);
}

void homekit_setup() {

  // We create one FreeRTOS-task for HomeKit
  // No need to call arduino_homekit_loop
  arduino_homekit_setup(&config);
}
