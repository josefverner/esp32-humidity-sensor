/*********************************************************************
* Chip: ESP32-D0WDQ6 Rev 1                                           *
* Cores: 2                                                           *
* Chip ID: 13033968.                                                 *
* GPIO pin is rated at 40mA                                          *
* recommended 20mA per GPIO                                          *
* max 250mA at all GPIOs.                                            *
* Following GPIOs may be set HIGH or to PWM Signal at boot or reset: *
* GPIO 0, GPIO 1, GPIO 3, GPIO 5, GPIO 6 - 11, GPIO 14, GPIO 15.     *
*********************************************************************/

/*
Board goes to deep sleep.
When button is pressed:
- board wakes up
- humidity sensor is read
- LEDs bright up depending on the humidity
- LEDs stay ON for 5 seconds
- LEDs dim down
- board goes to deep sleep again
*/

#include <humidity_variables.h>
#include <utils.h>
#include <esp32-hal-ledc.h>

#include <Arduino.h> // Add the missing include directive

#define TOUCH_THRESHOLD 57

RTC_DATA_ATTR int bootCount = 0;
touch_pad_t touchPin;

bool fadeEnded = false;      // status of LED fade
bool fadeAllowed = true;
int touchValue = 0;

void ARDUINO_ISR_ATTR LED_FADE_ISR() {
  fadeEnded = true;
}


// put function declarations here:
// int myFunction(int, int);
void fade_in_leds(int activeLights);
void fade_out_leds(int activeLights);
void wakeup_and_measure();

void setup() {
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  Serial.begin(115200);
  while(!Serial) delay(10);

  ++bootCount;

  for (byte i = 0; i < LED_COUNT; i++) {
    ledcAttach(ledPins[i], LEDC_BASE_FREQ, LEDC_TIMER_BIT);
    ledcWrite(ledPins[i], LEDC_START_DUTY);
    delay(10);
  }

  Serial.println("LED Fade off started.");

  wakeup_and_measure();

  touchSleepWakeUpEnable(T3, TOUCH_THRESHOLD);

  Serial.println("Going to sleep now");
  esp_deep_sleep_start();
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
void fade_in_leds(int activeLights) {
  for (byte i = 0; i < activeLights; i++) {
    ledcFadeWithInterrupt(ledPins[i], LEDC_START_DUTY, LEDC_TARGET_DUTY, LEDC_FADE_TIME, LED_FADE_ISR); 
  }
  delay(LEDC_FADE_TIME);
  delay(100);
}

void fade_out_leds(int activeLights) {
  for (byte i = 0; i < activeLights; i++) {
    ledcFadeWithInterrupt(ledPins[i], LEDC_TARGET_DUTY, LEDC_START_DUTY, LEDC_FADE_TIME, LED_FADE_ISR); 
  }
  delay(LEDC_FADE_TIME);
  delay(100);
}

void wakeup_and_measure() {
  Serial.println("Woke up from deep sleep.");

  touchPin = esp_sleep_get_touchpad_wakeup_status();

  Serial.println("Touch Pin: " + String(touchPin));
  
  
  int humidity = analogRead(HUMIDITY_SENSOR_PIN);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  int activeLights = fixedMap(humidity, 3500, 1500, 0, LED_COUNT);

  delay(100);
  
  if (fadeAllowed) {
    Serial.println("LED Fade on started.");
    fadeAllowed = false;
    if (touchPin == TOUCH_PIN_VALUE) {
      fade_in_leds(activeLights);
    }
    delay(10);
    fadeAllowed = true;
  }

  while (true)
  {
    touchValue = touchRead(T3);
    Serial.println("Touch Value: " + String(touchValue));
    if (touchValue > TOUCH_THRESHOLD) {
      break;
    }
  }
  
  Serial.println("LED Fade off started.");
  fade_out_leds(activeLights);
}
