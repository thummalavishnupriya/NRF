//esp(NodeB)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define led_e 15
#define button_e 35

RF24 radio(16, 17); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState_n = 0;
boolean buttonState_e = 0;

void setup() {
  pinMode(led_e, OUTPUT);
  pinMode(button_e, INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  radio.stopListening(); // Switch to TX mode
  buttonState_e = digitalRead(button_e);
  radio.write(&buttonState_e, sizeof(buttonState_e));
  
  radio.startListening(); // Switch to RX mode
  if (radio.available()) {
    radio.read(&buttonState_n, sizeof(buttonState_n));
    digitalWrite(led_e, buttonState_n);
  }
  delay(10);
}
