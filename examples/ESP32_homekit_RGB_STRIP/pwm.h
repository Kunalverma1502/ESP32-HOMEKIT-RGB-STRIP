

const int R_pin = 2;  // R corresponds to GPIO16
const int G_pin = 17; // G corresponds to GPIO17
const int B_pin = 5;  // B corresponds to GPIO5

const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int resolution = 8;

void pwm_setup() {
  // configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(R_pin, ledChannel1);
  ledcAttachPin(G_pin, ledChannel2);
  ledcAttachPin(B_pin, ledChannel3);
}
