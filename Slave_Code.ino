#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,9); //Setup for Slave - RX, TX | for pins RX to TX on HC-05 and TX to RX on HC-05

void setup() {
  // // put your setup code here, to run once:
  Serial.begin(38400);
  BTSerial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() 
{
  digitalWrite(8, HIGH);
  BTSerial.write("1");
  delay(1000);
}