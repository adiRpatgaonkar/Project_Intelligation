/*
* Receiver module code.
* By : Aditya R. Patgaonkar
* Credits : Dejan Nedelkovski, www.HowToMechatronics.com
* Modified according to the goals/needs of our project.
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";
unsigned int motor = 6;
void setup() {
  pinMode(motor, OUTPUT);
  digitalWrite(motor, HIGH);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
unsigned int x = 0;
void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    x = atoi(text);
    Serial.println(x);
    if (x == 1)
      digitalWrite(motor, HIGH);  
    else if (x == 0)
    {
      digitalWrite(motor, LOW);
      Serial.println("Job done.");
    }
    else if (x == 2)
    {
      digitalWrite(motor, LOW);
      Serial.println("Error");
    }   
  }
}
