/*********************************************************************
 * DF Pong Controller – Light Sensor Version
 *********************************************************************/

#include <ArduinoBLE.h>
#include "ble_functions.h"
#include "Pressure_raw.h"   // ← replaces buzzer_functions.h

// ============================================
const int DEVICE_NUMBER = 19;
// ============================================

String deviceNameStr = "DFPONG-" + String(DEVICE_NUMBER);
const char* deviceName = deviceNameStr.c_str();

const int LED_PIN = LED_BUILTIN;
const int PRESSURE_PIN = A7;

int currentMovement = 0;

void setup() 
{
  Serial.begin(9600);
  delay(1000);

  Serial.println("=== DF Pong Controller (Light Version) ===");

  pinMode(LED_PIN, OUTPUT);

  setupBLE(deviceName, DEVICE_NUMBER, LED_PIN);

  // Light sensor setup (instead of buzzer)
  setupLight(PRESSURE_PIN);
}

void loop() 
{
  updateBLE();

  handleInput();

  sendMovement(currentMovement);
}

void handleInput() 
{
  updateLight();                   // read + smooth light
  currentMovement = getLightMovement();   // 0/1/2
}
