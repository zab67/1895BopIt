#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial BTSerial(10,11); //Setup for Master - RX, TX | for pins RX to TX on HC-05 and TX to RX on HC-05
LiquidCrystal_I2C lcd(0x20, 20, 4);

int score = 0;
String command = "";
int taskRandNum;
float time;
static int maxScore = 100; // max score of 100 points
static int maxTime = 10; // max time of 10 seconds to perform task

String testA = "";

void setup() 
{
  time = maxTime;

  randomSeed(203847502347502);// random long as a seed

  Serial.begin(38400);
  BTSerial.begin(9600); //For Bluetooth Comm.

  //Initalize LCD Screen
  lcd.init();
  lcd.backlight();
  lcd.home();
}

  int multiplier = 0;

  String combos[10] = { //10 random combinations
    "88887984838483798884",
    "83847988798383847988",
    "79887988838384838384",
    "88848884838488848884",
    "79838384888883797979",
    "79798388848883798888",
    "88887983798884847983",
    "88838479887983847979",
    "83838388848379838884",
    "79798884837984838383"
  };

//ASCII Reference:
//A = 65
//R = 82
//U = 85
//L = 76
//D = 68
//X = 88
//O = 79
//T = 84
//S = 83


void loop() 
{
  if(BTSerial.available() > 0)
  {
    testA = BTSerial.read();
    delay(100);
    lcd.print(testA);
    delay(200);
  }
  testA = "";
  


    // taskRandNum = random(1,4);// generates a random number from {1,2,3}
    // if(taskRandNum == 1)
    // {
    //   display("Rage It!");
    //   if(!rageIt())
    //   {
    //     gameOver();
    //   }
    //   command = "";
    // }
    // else if(taskRandNum == 2)
    // {
    //   display("Shoot It!");
    //   if(!shootIt())
    //   {
    //     gameOver();
    //   }
    //   command = "";
    // }
    // else if(taskRandNum == 3)
    // {
    //   display("Combo It!");
    //   if(!comboIt())
    //   {
    //     gameOver();
    //   }
    //   command = "";
    // }
    // else
    // {
    //   Serial.println("Random Num Error!");
    //   command = "";
    // }

    // score++;

    // if(score >= maxScore) // If user has won the game
    // {
    //   gameOver();
    // }

    // if (score % 10 == 0) // only if we've reached a new task set, send the multiplier
    // {
    //   BTSerial.print(multiplier);
    //   delay(100);
    //   multiplier++;
    // }
}

bool rageIt() 
{

    for(int i = 0; i < 715000 - 50000*multiplier; i++)
    {
       if(BTSerial.available() > 0)
      {
        delay(100);
        command = BTSerial.readString();
      }
    }

    String byte = "";

    for(int i = 0; i < command.length()-1; i=i+2) // loop through the command all the way until the second to last char
    {
      byte += command[i]; // add first digit of the ASCII number
      byte += command[i+1]; // add second digit of the ASCII number

      if(byte != "65")// loop through each byte, checking that all equal 65 which is A
      {
        return false; // task failed
      } 

      byte = ""; // clear byte
    }

    return true; // task passed
}

bool comboIt() 
{
    String combo = "";
    combo = combos[random(0,10)]; // select a random combo
    displayCombo(combo); // display combo

    for(int i = 0; i < 715000 - 50000*multiplier; i++)
    {
       if(BTSerial.available() > 0)
      {
        delay(100);
        command = BTSerial.readString();
      }
    }
    if(command == combo) // if the command from the slave matches
    {
      return true; // task passed
    }
    return false; // task failed
}


bool shootIt() 
{
    for(int i = 0; i < 715000 - 50000*multiplier; i++)
    {
       if(BTSerial.available() > 0)
      {
        delay(100);
        command = BTSerial.readString();
      }
    }
}

void display(String str)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str);
  //delay(2000);
}

void displayShoot()
{

  return;
}

void displayCombo(String combo)
{
    String outputStr = "";
    String byte = "";

    for(int i = 0; i < combo.length()-1; i=i+2) // loop through the combo all the way until the second to last char
    {
      byte += combo[i]; // add first digit of the ASCII number
      byte += combo[i+1]; // add second digit of the ASCII number

      if(byte == 88)//X
      {
        outputStr += "X";
      } //TODO complete this if statement with what to output on the LCD
      //Zack said something about custom symbols so maybe we can use those?

      display(outputStr);
    }
}

void displayScore()
{
  return;
}

void gameOver()
{
  return;
}

