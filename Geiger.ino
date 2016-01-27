/*
 * Geiger.ino
 * 
 * This code interacts with the Alibaba RadiationD-v1.1 (CAJOE) Geiger counter board 
 * and reports readings in CPM (Counts Per Minute).
 * 
 * Author: Mark A. Heckler (@MkHeck, mark.heckler@gmail.com)
 * 
 * License: MIT License
 * 
 * Please use freely with attribution. Thank you!
 */

#include <SPI.h>

#define LOG_PERIOD 5000 //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 60000 //Maximum logging period

volatile unsigned long counts = 0;                       // GM Tube events
unsigned long cpm = 0;                                   // CPM
const unsigned int multiplier = MAX_PERIOD / LOG_PERIOD; // Calculates/stores CPM
unsigned long previousMillis;                            // Time measurement
const int pin = 3;

void tube_impulse() { // Captures count of events from Geiger counter board
  counts++;
}

void setup() {
  Serial.begin(115200);                                               // Start serial monitor
  pinMode(pin, INPUT);                                                // Set pin to input for capturing GM Tube events
  interrupts();                                                       // Enable interrupts (in case they were previously disabled)
  attachInterrupt(digitalPinToInterrupt(pin), tube_impulse, FALLING); // Define external interrupts
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > LOG_PERIOD) {
    previousMillis = currentMillis;
    cpm = counts * multiplier;
    Serial.println(cpm);
    counts = 0;
  }
}

