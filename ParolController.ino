#include "parolController.hpp"

const uint8_t starsLEDS[] = {3, 4 , 5, 6, 7};
const uint8_t ringLEDS[] = {2};
const uint8_t beeperPin = 8;

ParolController pc(starsLEDS, 5, ringLEDS, 1, beeperPin);
void setup() {
  Serial.begin(9600);
  pc.init();
}

void loop() {
}


