#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,9); //Setup for Master - RX, TX | for pins RX to TX on HC-05 and TX to RX on HC-05
String bit = "0";
int state = 0;
void setup() 
{
  Serial.begin(38400);
  BTSerial.begin(9600);

  pinMode(8, OUTPUT);
}

void loop() 
{
  if(BTSerial.available() > 0)
  {
    bit = BTSerial.read();
    Serial.print(bit);
  }
  if(bit == "49")
  {
    if(state == 0)
    {
      digitalWrite(8, HIGH);
      state = 1;
    }
    else
    {
      digitalWrite(8, LOW);
      state = 0;
    }
  }
  bit = "";
}
