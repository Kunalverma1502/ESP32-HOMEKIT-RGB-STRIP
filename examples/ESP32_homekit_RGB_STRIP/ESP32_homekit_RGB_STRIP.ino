#include "Arduino.h"
#include "WiFi.h"
#include "arduino_homekit_server.h"
#include "pwm.h"


TaskHandle_t Task1;

#define LED_RGB_SCALE 255       // this is the scaling factor used for color conversion

typedef union {
  struct {
    uint16_t blue;
    uint16_t green;
    uint16_t red;
    uint16_t white;
  };
  uint64_t color;
} rgb_color_t;

// Color smoothing variables
rgb_color_t current_color = { { 0, 0, 0, 0 } };
rgb_color_t target_color = { { 0, 0, 0, 0 } };

bool received_sat = false;
bool received_hue = false;

bool is_on = false;
float current_brightness =  100.0;
float current_sat = 0.0;
float current_hue = 0.0;
int rgb_colors[3];

unsigned long previousMillis = 0;
unsigned long interval = 30000;

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";


extern "C" homekit_server_config_t config;
extern "C" char ACCESSORY_NAME[32];
extern "C" void accessory_init();
extern "C" homekit_characteristic_t cha_on;
extern "C" homekit_characteristic_t cha_bright;
extern "C" homekit_characteristic_t cha_sat;
extern "C" homekit_characteristic_t cha_hue;

// called when value changed in home app
void set_on(const homekit_value_t v) {
  bool on = v.bool_value;
  cha_on.value.bool_value = on; //sync the value

  if (on) {
    is_on = true;
    Serial.println("On");
  } else  {
    is_on = false;
    Serial.println("Off");
  }

  updateColor();
}

// called when value changed in home app
void set_hue(const homekit_value_t v) {
  Serial.println("set_hue");
  float hue = v.float_value;
  cha_hue.value.float_value = hue; //sync the value

  current_hue = hue;
  received_hue = true;

  updateColor();
}

// called when value changed in home app
void set_sat(const homekit_value_t v) {
  Serial.println("set_sat");
  float sat = v.float_value;
  cha_sat.value.float_value = sat; //sync the value

  current_sat = sat;
  received_sat = true;

  updateColor();

}

// called when value changed in home app
void set_bright(const homekit_value_t v) {

  Serial.println("set_bright");
  int bright = v.int_value;
  cha_bright.value.int_value = bright; //sync the value

  current_brightness = bright;

  updateColor();

}


//http://blog.saikoled.com/post/44677718712/how-to-convert-from-hsi-to-rgb-white
static void hsi2rgb(float h, float s, float i, rgb_color_t* rgb) {
  int r, g, b;

  while (h < 0) {
    h += 360.0F;
  };     // cycle h around to 0-360 degrees
  while (h >= 360) {
    h -= 360.0F;
  };
  h = 3.14159F * h / 180.0F;          // convert to radians.
  s /= 100.0F;                        // from percentage to ratio
  i /= 100.0F;                        // from percentage to ratio
  s = s > 0 ? (s < 1 ? s : 1) : 0;    // clamp s and i to interval [0,1]
  i = i > 0 ? (i < 1 ? i : 1) : 0;    // clamp s and i to interval [0,1]
  //i = i * sqrt(i);                    // shape intensity to have finer granularity near 0

  if (h < 2.09439) {
    r = LED_RGB_SCALE * i / 3 * (1 + s * cos(h) / cos(1.047196667 - h));
    g = LED_RGB_SCALE * i / 3 * (1 + s * (1 - cos(h) / cos(1.047196667 - h)));
    b = LED_RGB_SCALE * i / 3 * (1 - s);
  }
  else if (h < 4.188787) {
    h = h - 2.09439;
    g = LED_RGB_SCALE * i / 3 * (1 + s * cos(h) / cos(1.047196667 - h));
    b = LED_RGB_SCALE * i / 3 * (1 + s * (1 - cos(h) / cos(1.047196667 - h)));
    r = LED_RGB_SCALE * i / 3 * (1 - s);
  }
  else {
    h = h - 4.188787;
    b = LED_RGB_SCALE * i / 3 * (1 + s * cos(h) / cos(1.047196667 - h));
    r = LED_RGB_SCALE * i / 3 * (1 + s * (1 - cos(h) / cos(1.047196667 - h)));
    g = LED_RGB_SCALE * i / 3 * (1 - s);
  }


  Serial.println(r);
  Serial.println(g);
  Serial.println(b);

  ledcWrite(ledChannel1, r);
  ledcWrite(ledChannel2, g);
  ledcWrite(ledChannel3, b);

  //  rgb->red = (uint8_t) r;
  //  rgb->green = (uint8_t) g;
  //  rgb->blue = (uint8_t) b;
}

// using core 0 for making sure wifi always remains connected
//https://randomnerdtutorials.com/solved-reconnect-esp32-to-wifi/
void Task1code( void * parameter) {
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

//setting the values of light
void updateColor() {

  if (is_on) {
    hsi2rgb(current_hue, current_sat, current_brightness, &target_color);
    Serial.println("hsi2rgb calling !!");
  } else  {
    ledcWrite(ledChannel1, 0);
    ledcWrite(ledChannel2, 0);
    ledcWrite(ledChannel3, 0);
  }
}


void setup() {

  Serial.begin(115200);
  //  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  //  WiFi.persistent(false);
  //  WiFi.disconnect(false);
  //  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());

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



  homekit_setup();

  pwm_setup();

  //  delay(5000);                // uncomment only to reset homekit storage
  //homekit_storage_reset();      // uncomment only to reset homekit storage

  
  xTaskCreatePinnedToCore(
    Task1code, /* Function to implement the task */
    "Task1", /* Name of the task */
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    0,  /* Priority of the task */
    &Task1,  /* Task handle. */
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
  accessory_init();

  cha_on.setter = set_on;
  cha_bright.setter = set_bright;
  cha_sat.setter = set_sat;
  cha_hue.setter = set_hue;

  // We create one FreeRTOS-task for HomeKit
  // No need to call arduino_homekit_loop
  arduino_homekit_setup(&config);
}
