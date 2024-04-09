#include <humidity_variables.h>

/*
#define LEDC_TIMER_12_BIT  12
#define LEDC_BASE_FREQ     5000
#define LEDC_START_DUTY    0
#define LEDC_TARGET_DUTY   4095
#define LEDC_FADE_TIME     3000
*/

const byte HUMIDITY_SENSOR_PIN = 36;

const byte LED_01_PIN = 23;
const byte LED_02_PIN = 22;
const byte LED_03_PIN = 21;
const byte LED_04_PIN = 19;
const byte LED_05_PIN = 18;
const byte LED_06_PIN = 17;
const byte LED_07_PIN = 16;
const byte LED_08_PIN = 4;
const byte LED_09_PIN = 25;
const byte LED_10_PIN = 26;

const uint8_t LEDC_TIMER_BIT = 12;
const uint32_t LEDC_START_DUTY = 0;
const uint32_t LEDC_TARGET_DUTY = 4094; // 2^LEDC_TIMER_BIT
const uint32_t LEDC_BASE_FREQ = 5000;
const int LEDC_FADE_TIME = 740;

const byte SWITCH_01_PIN = 32;
const byte SWITCH_02_PIN = 33;

const byte TOUCH_PIN_VALUE = 3; // Touch pin value of GPIO 15

const byte ledPins[] = {
  LED_01_PIN,
  LED_02_PIN,
  LED_03_PIN,
  LED_04_PIN,
  LED_05_PIN,
  LED_06_PIN,
  LED_07_PIN,
  LED_08_PIN,
  LED_09_PIN,
  LED_10_PIN
};
const byte LED_COUNT = sizeof(ledPins);
