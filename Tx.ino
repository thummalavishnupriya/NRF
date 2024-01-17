//Nano
//Here nano works as Transmitter
//Nano reads push button state and send it to esp via nrf to trigger led attached to ESP

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define button 4

RF24 radio(2, 3); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

void setup() {
  pinMode(button, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(5);
  radio.stopListening();
  buttonState = digitalRead(button);
  radio.write(&buttonState, sizeof(buttonState));
  delay(5);

}
