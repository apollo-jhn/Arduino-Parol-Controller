#include "parolController.hpp"

const uint8_t starsLEDS[] = {3, 4 , 5, 6, 7};
const uint8_t ringLEDS[] = {2};

ParolController pc(starsLEDS, 5, ringLEDS, 1);

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pc.init();
}

uint16_t peak = 0;
uint16_t reading = 0;
PulseClock regulator;

void loop() {
  // Regulate
  regulator.setInterval(1000);

  if (regulator.getState() && peak != 0) {
    peak--;
  }

  reading = analogRead(A0);
  pc.changeInterval(reading - 100);
  if(peak < reading){
    peak = reading;
  }


  Serial.println(String(reading) + " " + String(peak));
  pc.play();
}


