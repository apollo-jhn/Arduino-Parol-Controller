#include <stdint.h>
#include "Arduino.h"

class PulseClock {
  public:
    PulseClock(bool);
    void setInterval(uint16_t);
    bool getState();
  private:
    unsigned long interval;
    unsigned long currentTime;
    unsigned long previousTime;
    bool nsMode;
    bool state;
};

void PulseClock::setInterval(uint16_t timeInterval) {
  this->interval = timeInterval;
}

PulseClock::PulseClock(bool nanosecondMode = false) {
  this->nsMode = nanosecondMode;

  // Set the default value
  this->interval = 0;
  this->currentTime = 0;
  this->previousTime = 0;
}

bool PulseClock::getState() {
  // If interval is not set it will return default false
  if(this->interval == 0){return false;}

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


class Button {
  public:
    bool getState();
    Button(uint8_t);
  private:
    uint8_t buttonPin;
};
Button::Button(uint8_t pinNumber) {
  this->buttonPin = pinNumber;
  pinMode(this->buttonPin, INPUT_PULLUP);
}

bool Button::getState() {
  if (!digitalRead(buttonPin)){
    return true;
    delay(1000);
  } else {
    return false;
  }
}