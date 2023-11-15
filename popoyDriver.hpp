#include "Arduino.h"

class PulseClock {
  public:
    PulseClock(unsigned long, bool);
    bool getState();
  private:
    unsigned long interval;
    unsigned long currentTime;
    unsigned long previousTime;
    bool nsMode;
    bool state;
};

PulseClock::PulseClock(unsigned long timeInterval, bool nanosecondMode = false) {
  this->interval = timeInterval; // Get the time interval
  this->nsMode = nanosecondMode;

  // Set the default value
  this->currentTime = 0;
  this->previousTime = 0;
}

bool PulseClock::getState() {
  // Get the current time
  if(!this->nsMode){
    this->currentTime = millis();
  } else {
    this->currentTime = micros();
  }

  // Process
  if(this->currentTime - this->previousTime >= this->interval) {
    this->state = true;
    this->previousTime = this->currentTime;
  } else if (this->currentTime < this->previousTime) {
    this->previousTime = 0; // Reset the clock
  } else {
    this->state = false;
  }

  return this->state;
}