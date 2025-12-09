#include <Arduino.h>

// Light sensor variables
int lightPin;                          
const int lightAverageWindow = 10;

int lightReadings[lightAverageWindow];
int lightReadIndex = 0;
long lightTotal = 0;

int rawLight = 0;
int smoothedLight = 0;
int baselineLight = 0;

unsigned long lastRead = 0;
int readInterval = 50;

// ----------------------------------------------------------
// Setup
// ----------------------------------------------------------
void setupLight(int pin) {
  lightPin = pin;
  pinMode(lightPin, INPUT);

  // reset rolling average
  for (int i = 0; i < lightAverageWindow; i++) {
    lightReadings[i] = 0;
  }
  lightTotal = 0;
  lightReadIndex = 0;

  // baseline calibration
  long total = 0;
  for (int i = 0; i < lightAverageWindow; i++) {
    total += analogRead(lightPin);
    delay(30);
  }
  baselineLight = total / lightAverageWindow;
}

// ----------------------------------------------------------
// Update + smoothing
// ----------------------------------------------------------
void updateLight() {
  unsigned long now = millis();
  if (now - lastRead < readInterval) return;

  lastRead = now;

  rawLight = analogRead(lightPin);

  // rolling average
  lightTotal -= lightReadings[lightReadIndex];
  lightReadings[lightReadIndex] = rawLight;
  lightTotal += rawLight;
  lightReadIndex = (lightReadIndex + 1) % lightAverageWindow;

  smoothedLight = lightTotal / lightAverageWindow;
}

// ----------------------------------------------------------
// Convert brightness → movement (0/1/2)
// ----------------------------------------------------------
int getLightMovement() {
  int threshold = 100;

  if (abs(smoothedLight - baselineLight) <= threshold) return 0;  // same
  if (smoothedLight > baselineLight) return 1;                    // brighter → UP
  return 2;                                                       // darker → DOWN
}
