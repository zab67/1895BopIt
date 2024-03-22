#include <SoftwareSerial.h>
SoftwareSerial BTSerial(8,3);
char outputs[10];
int state = 0;
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
    // for(int i = 0; i < 10; i++)
    // {
    bit = BTSerial.read();
    Serial.print(bit);
    //   Serial.print(recieved);
    //   outputs[i] = recieved;
    // }
  }
  // if(bit == "49")
  // {
  //   if(state == 0)
  //   {
  //     digitalWrite(4, HIGH);
  //     state = 1;
  //   }
  //   else
  //   {
  //     digitalWrite(4, LOW);
  //     state = 0;
  //   }
  // }
  // bit = "";
}
