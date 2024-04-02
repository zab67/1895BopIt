#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
SoftwareSerial BTSerial(10, 11); //Setup for Slave - RX, TX | for pins RX to TX on HC-05 and TX to RX on HC-05 (10,11)
int XState, OState,SquareState,TriangleState,DownState,LeftState,RightState;
String output = "";
// variable for reading the pushbutton status

//Acceloremeter - A

//X - X
//O - O
//Square - S
//Triangle - T

//Up - U
//Down - D
//Left - L
//Right - R


void setup() 
{
  Serial.begin(38400);

  //Init MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  checkSettings();

  BTSerial.begin(9600);

  pinMode(0, INPUT); // Right
  pinMode(2, INPUT); // Left
  pinMode(3, INPUT); // Down
  pinMode(4, INPUT); // X
  pinMode(5, INPUT); // O
  pinMode(6, INPUT); // Triangle
  pinMode(7, INPUT); // Square
}

void loop() 
{
  output = "";
  for(int i = 0; i < 200; i++) //Change size of i based off game timer - 1=10s, 2=9.3s...  715000-(50000*multiplier)
  {
    Vector normAccel = mpu.readNormalizeAccel();
    if((normAccel.YAxis > 19) and (normAccel.XAxis > 19))
    {
      output += "A";
      delay(170);
    }
    output += readButtonState(0, 'R');
    output += readButtonState(2, 'L');
    output += readButtonState(3, 'D');
    output += readButtonState(4, 'X');
    output += readButtonState(5, 'O');
    output += readButtonState(6, 'T');
    output += readButtonState(7, 'S');
  }
  BTSerial.print(output);
  delay(100);
}

void checkSettings()
{
  Serial.println();
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }   
  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}

String readButtonState(int pin, char symbol) 
{
  int state = digitalRead(pin);
  if(state == 1) 
  {
    delay(170);
    return String(symbol);
  }
  return "";
}