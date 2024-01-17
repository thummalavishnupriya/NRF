//Nano(NodeA)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define led_n 10
#define button_n 4

RF24 radio(2, 3); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState_n = 0;
boolean buttonState_e = 0;

void setup() {
  pinMode(led_n, OUTPUT);
  pinMode(button_n, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  radio.stopListening(); // Switch to TX mode
  buttonState_n = digitalRead(button_n);
  radio.write(&buttonState_n, sizeof(buttonState_n));
  
  radio.startListening(); // Switch to RX mode
  if (radio.available()) {
    radio.read(&buttonState_e, sizeof(buttonState_e));
    digitalWrite(led_n, buttonState_e);
  }
  delay(10);
}
