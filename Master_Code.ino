#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,9); //Setup for Master - RX, TX | for pins RX to TX on HC-05 and TX to RX on HC-05

void setup() {
  // put your setup code here, to run once:
  time = maxTime;
  float time;
  int score = 0;
  String command = "";
  int randNum;
  randomSeed(203847502347502);// random long as a seed
  Serial.begin(38400);
  BTSerial.begin(9600); 

}
 
static int maxScore = 100;
static float maxTime = 4;
static float timeDecrement = 0.03;


void loop() {

    randNum = random(1,4);// generates a random number from {1,2,3}

    if(randNum == 1)
    {
      displayTask("Rage It!");
      if(!rageIt())
      {
        gameOver();
      }
      command = "";

    }
    else if(randNum == 2)
    {
      displayTask("Shoot It!");
      if(!shootIt())
      {
        gameOver();
      }
      command = "";

    }
    else if(randNum == 3)
    {
      displayTask("Combo It!");
      if(!comboIt())
      {
        gameOver();
      }
      command = "";

    }
    else
    {
      Serial.println("Random Num Error!")
      command = "";
    }

  time -= timeDecrement
}

bool rageIt() {

    for(int i = 0; i < time; i++)
    {
       if(BTSerial.available() > 0)
      {
        command = BTSerial.readString()
      }
    }

    for(int i = 0; i < command.length()-1; i=i+2) // loop through the command all the way until the second to last char
    {
      if(command.substring(i,i+2) != "65")// loop through each two char substring, checking that all equal 65 which is A
      {
        return false;
      } 
    }
    return true;
}

bool comboIt() {

}

bool shootIt() {

}

void displayTask(){


}

void gameOver(){


}

