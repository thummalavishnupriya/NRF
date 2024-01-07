/*
NRF module
operating voltage: 1.9V to 3.6V
Logic inputs : 5V
125 different channels in a mesh
Each unit can communicate with upto 6 other units at the same time.

CE, CSN used for settinng the module in standby or active mode 
or 
To switch between transmit or command mode
100 meters
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(2, 3); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);//setting power amplifier level_
  //Need to increase the above PA level to more if the distance between the modules are more
  //If power level is changed to max need to use a bypass capacitor across 3.3V & GND so that they will have more stable voltage while operating
  radio.stopListening();//This sets module as TX
}

void loop() {
  const char text[] = "Hallo World";
  radio.write(&text, sizeof(text));//using radio.write() function we can send max of 32 bytes
  delay(1000);
}
