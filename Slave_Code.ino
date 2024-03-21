#include <SoftwareSerial.h>
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
SoftwareSerial BTSerial(10,9); //Setup for Slave - RX, TX | for pins RX to TX on HC-05 and TX to RX on HC-05
int XState, OState,SquareState,TriangleState,UpState,DownState,LeftState,RightState = 0;
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

  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  checkSettings();

  BTSerial.begin(9600);

  pinMode(0, INPUT); // Right
  pinMode(1, INPUT); // UP
  pinMode(2, INPUT); // Left
  pinMode(3, INPUT); // Down
  pinMode(4, INPUT); // X
  pinMode(5, INPUT); // O
  pinMode(6, INPUT); // Triangle
  pinMode(7, INPUT); // Square

  pinMode(8, INPUT);

}

void loop() 
{

  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  if((normAccel.XAxis >= 1) or (normAccel.YAxis >= 1))
  {
    BTSerial.write("A");
    delay(170);
  }
  Serial.print(normAccel.XAxis);
  Serial.print(normAccel.YAxis);
  Serial.println(normAccel.ZAxis);
  delay(100);

  RightState = digitalRead(0);
  if(RightState == 1)
  {
    BTSerial.write("R");
    delay(170);
  }

  UpState = digitalRead(1);
  if(UpState == 1)
  {
    BTSerial.write("U");
    delay(170);
  }

  LeftState = digitalRead(2);
  if(LeftState == 1)
  {
    BTSerial.write("L");
    delay(170);
  }

  DownState = digitalRead(3);
  if(DownState == 1)
  {
    BTSerial.write("D");
    delay(170);
  }
  
  XState = digitalRead(4);
  if(XState == 1)
  {
    BTSerial.write("X");
    delay(170);
  }

  OState = digitalRead(5);
  if(OState == 1)
  {
    BTSerial.write("O");
    delay(170);
  }

  TriangleState = digitalRead(6);
  if(TriangleState == 1)
  {
    BTSerial.write("T");
    delay(170);
  }

  SquareState = digitalRead(7);
  if(SquareState == 1)
  {
    BTSerial.write("S");
    delay(170);
  }
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
