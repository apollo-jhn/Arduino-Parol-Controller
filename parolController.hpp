#include "Arduino.h"
#include <stdint.h>
#ifndef PAROL_CONTROLLER_HPP
#define PAROL_CONTROLLER_HPP

#include "popoyDriver.hpp"

class ParolController {
  public:
    // Stars Pin Number's, N of Stars, Ring Pin Number's, Ring N : N stands for "Number"
    ParolController(uint8_t[], uint8_t, uint8_t[], uint8_t, uint8_t);
    void init(); // Initialize
  private:
    uint8_t *stars; // Stars Pin Number Array
    uint8_t *rings;
    uint8_t stars_n;
    uint8_t ring_n;
    uint8_t beep;
    void playBeep(uint16_t);
};

void ParolController::playBeep(uint16_t frequency) {
  if(this->beep != -1){
    noTone(this->beep);
    tone(this->beep, frequency);
  }
}

void ParolController::init() {
  // Setting pinmode for stars
  for(int i = 0; i < this->stars_n; i++) {
    pinMode(this->stars[i], OUTPUT);
    digitalWrite(this->stars[i], HIGH);
    playBeep(i * 100 + 262);
    delay(1000);
  }

  // Setting pinmode for ring
  for(int i = 0; i < this->ring_n; i++) {
    pinMode(this->rings[i], OUTPUT);
    digitalWrite(this->rings[i], HIGH);
    playBeep(i * (100 * this->stars_n) + 262);
    delay(1000);
  }

  // Reset all output to zero
  if (this->beep != -1){ noTone(this->beep); }
  for(int i = 0; i < this->stars_n; i++){ digitalWrite(this->stars[i], LOW); }
  for(int i = 0; i < this->ring_n; i++) { digitalWrite(this->rings[i], LOW); }
}

ParolController::ParolController (uint8_t starsPinNumbers[], uint8_t starsNumber, uint8_t ringPinNumbers[], uint8_t ringNumber, uint8_t beepPin = -1) {
  // Get the maximum numbers
  this->stars_n = starsNumber;
  this->ring_n = ringNumber;

  // For Stars LEDS
  this->stars = new uint8_t[this->stars_n];
  for(int i = 0; i < starsNumber; i++){
    this->stars[i] = starsPinNumbers[i];
  }

  // For Ring LEDS
  this->rings = new uint8_t[this->ring_n];
  for(int i = 0; i < ringNumber; i++){
    this->rings[i] = ringPinNumbers[i];
  }

  // Beep
  this->beep = beepPin;
}
#endif // PAROL_CONTROLLER_HPP