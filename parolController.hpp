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
    void play(); // Must be inside of a while loop or arduino main loop to run
  private:
    PulseClock timer;
    bool alternate;
    void channelWrite(uint8_t, bool); // Function to set channel either HIGH or LOW with trigger if audio is enabled
    void patternManager(uint8_t);
    // Pattern START
    void p_static_all();
    void p_static_stars();
    void p_static_ring();
    void p_static_all_off();
    void p_static_stars_off();
    void p_static_ring_off();

    void p_blink_all();
    // Pattern END
    uint8_t *stars; // Stars Pin Number Array
    uint8_t *rings;
    uint8_t stars_n;
    uint8_t ring_n;
    uint8_t beep;
    void playBeep(uint16_t);
};

void ParolController::play() {
  this->patternManager(1);
}

void ParolController::patternManager(uint8_t  patternN = -1) {
  switch (patternN) {
    case 0: // All Turn On
      this->p_static_all();
      break;
    case 1:
      this->p_blink_all();
      break;
    default:
      this->p_static_all_off();
      break;
  }
};

// PATTERN START
void ParolController::p_blink_all() {
  if (this->timer.getState()){
    if(this->alternate){
      this->p_static_all();
    } else {
      this->p_static_all_off();
    }
    // Inverse
    this->alternate = !this->alternate;
  }
}

void ParolController::p_static_all(){
  // Turn all the channels HIGH on Stars and Rings
  this->p_static_stars();
  this->p_static_ring();
}
void ParolController::p_static_stars(){
  for(int i = 0; i < this->stars_n; i++){
    channelWrite(this->stars[i], HIGH);
  }
}
void ParolController::p_static_ring(){
  for(int i = 0; i < this->ring_n; i++){
    channelWrite(this->rings[i], HIGH);
  }
}
void ParolController::p_static_all_off(){
  this->p_static_stars_off();
  this->p_static_ring_off();
}
void ParolController::p_static_stars_off(){
  for(int i = 0; i < this->stars_n; i++){
    channelWrite(this->stars[i], LOW);
  }
}
void ParolController::p_static_ring_off(){
  for(int i = 0; i < this->ring_n; i++){
    channelWrite(this->rings[i], LOW);
  }
}
// PATTERN END

void ParolController::channelWrite(uint8_t channelN, bool state) {
  digitalWrite(channelN, state ? HIGH : LOW);
}

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

  // Set the time interval
  timer.setInterval(1000/10);

  this->alternate = false;

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