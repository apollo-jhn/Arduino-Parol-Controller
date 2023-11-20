#include "parolController.hpp"

const uint8_t starsLEDS[] = {3, 4 , 5, 6, 7};
const uint8_t ringLEDS[] = {2};
Button nextButton(8, 1000);

ParolController pc(starsLEDS, 5, ringLEDS, 1);

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pc.init();
}

uint16_t reading = 0;

void loop() {
  nextButton.update();

  if(nextButton.getState()){
    pc.changePattern();
  }

  reading = analogRead(A0);
  pc.changeInterval((reading - 100 < 1) ? 1 : reading - 100);

  pc.play();
}


