#include <SoftwareSerial.h>
SoftwareSerial BTSerial(8,2); //RX, TX on pins RX to TX on HC-05 and TX to RX on HC-05
String bit = "0";
void setup() 
{
  Serial.begin(38400);
  BTSerial.begin(9600);
}

void loop() 
{
  if(BTSerial.available() > 0)
  {
    bit = BTSerial.read();
    Serial.print(bit);
  }
}
