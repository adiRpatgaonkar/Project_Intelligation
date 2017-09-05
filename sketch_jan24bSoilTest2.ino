int ss1 = A0, ss2 = A1;
int bLed = 8, rLed = 9, gLed = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(ss1, INPUT);
  pinMode(ss2, INPUT);

  pinMode(bLed, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);

  digitalWrite(bLed, HIGH);
  digitalWrite(rLed, LOW);
  digitalWrite(gLed, LOW);
  Serial.begin(9600);
}
int moistT = 280; // Threshold to stop valve
int x = 0, y = 0; // To read values of soil sensors

void loop() 
{
  // put your main code here, to run repeatedly:
  x = analogRead(ss1); y = analogRead(ss2);
  Serial.print("ss1 = "); Serial.print(x); Serial.print(" | ");
  Serial.print("ss2 = "); Serial.print(y); Serial.println(".");

  if ((x > moistT) && (y > moistT))
  {
    Serial.println("Motor on!");
    digitalWrite(bLed, HIGH);
  }
  if ((x < moistT) && (y > moistT))
  {
    delay(10000);
    if (y > moistT)
    { 
      Serial.println("Motor off!");
      digitalWrite(bLed, LOW);
    }
  }
  if ((x > moistT) && (y < moistT))
  {
    delay(10000);
    if (x > moistT)
    { 
      Serial.println("Motor off!");
      digitalWrite(bLed, LOW);
    }
  }
  if ((x < moistT) && (y < moistT))
  {
    Serial.println("Motor off!");
    digitalWrite(bLed, LOW);
  }
}

