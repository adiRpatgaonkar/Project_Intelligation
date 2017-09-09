/*
* Transmitter module code.
* By : Aditya R. Patgaonkar
* Credits : Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>


RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";
int ss1 = A0, ss2 = A1;
void setup() {
  pinMode(ss1, INPUT);
  pinMode(ss2, INPUT);
  //Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
int sensorValue1 = 0, sensorValue2 = 0, motorState = 1;
void loop() {
  sensorValue1 = analogRead(ss1);
  sensorValue2 = analogRead(ss2);
  delay(1000);
  if (sensorValue1 < 400 && sensorValue2 < 400)
  {
    motorState = 0;
  }
  else if (sensorValue1 < 400 && sensorValue2 > 400)
  {
    unsigned int t = millis();
    while (((unsigned int)millis() - t) < 3000)
    {
      sensorValue2 = analogRead(ss2);
      if (sensorValue2 < 400)
        motorState = 0;   
    }
    if (motorState == 1)
      motorState = 2;
  }
  else if (sensorValue2 < 400 && sensorValue1 > 400)
  {
    unsigned int t = millis();
    while (((unsigned int)millis() - t) < 3000)
    {
      sensorValue1 = analogRead(ss1);
      if (sensorValue1 < 400)
        motorState = 0;   
    }
    if (motorState == 1)
      motorState = 2;
  }
  //Serial.println(sensorValue);
  delay(1000);
  char text[5] = "";
  itoa(motorState, text, 10);
  radio.write(&text, sizeof(text));
  delay(1000);
  text[5] = "";
  itoa(sensorValue1, text, 10);
  radio.write(&text, sizeof(text));
  delay(1000);
  text[5] = "";
  itoa(sensorValue2, text, 10);
  radio.write(&text, sizeof(text));
  delay(1000);
}
