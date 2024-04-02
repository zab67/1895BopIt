#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial BTSerial(10,9); //Setup for Master - RX, TX | for pins RX to TX on HC-05 and TX to RX on HC-05
LiquidCrystal_I2C lcd(0x20, 20, 4);

uint8_t squareSymbol[8] = {0x00,0x1F,0x11,0x11,0x11,0x1F,0x00,0x00};
uint8_t triangleSymbol[8] = {0x00,0x00,0x04,0x0A,0x11,0x1F,0x00,0x00};
uint8_t down[8] = {0x04,0x04,0x04,0x04,0x04,0x15,0x0E,0x04};
uint8_t left[8] = {0x00,0x00,0x04,0x08,0x1F,0x08,0x04,0x00};
uint8_t right[8] = {0x00,0x00,0x04,0x02,0x1F,0x02,0x04,0x00};

int score = 0;
String command = "";
float time;
static int maxScore = 100; // max score of 100 points
static int maxTime = 10; // max time of 10 seconds to perform task
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

String directions[3] = {"D", "L", "R"};

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

//done
void display(String str){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str);
  //delay(2000);
}

//done
void displayCombo(String combo){
    String outputStr = "";
    String byte = "";

    for(int i = 0; i < combo.length()-1; i=i+2) // loop through the combo all the way until the second to last char
    {
      byte += combo[i]; // add first digit of the ASCII number
      byte += combo[i+1]; // add second digit of the ASCII number

      if(byte == "88")
      {
        lcd.print("X");
      } 
      else if(byte == "79")
      {
        lcd.print("O");
      }
      else if(byte == "84")
      {
        lcd.print(1); // Triangle
      }
      else if(byte == "83")
      {
        lcd.print(0); // Square
      }
    }
  
}

//done
void displayShoot(String direction){
  if(direction == "U")
  {
    lcd.print(2); // Up
  }
  else if(direction == "L")
  {
    lcd.print(3); // Left
  }
  else if(direction == "R")
  {
    lcd.print(4); // Right
  }
  else
  {
    Serial.println("Shoot it Direction Error!");
  }

}

//done
void displayScore(){
  String score_string = String(score);
  display("Score: " + score_string);
}

//done
void startGame(){

  String anyButton = "";

  while(true)
  {
    display("Press any button to start!");
    if (BTSerial.available() > 0)
    {
      anyButton = BTSerial.read();

      if((anyButton.indexOf("65") > 0) || (anyButton.indexOf("82") > 0) || (anyButton.indexOf("85") > 0) || (anyButton.indexOf("76") > 0) || 
         (anyButton.indexOf("68") > 0) || (anyButton.indexOf("88") > 0) || (anyButton.indexOf("79") > 0) || (anyButton.indexOf("84") > 0) ||
         (anyButton.indexOf("83") > 0))
         {
          return;
         }
    }
  }

}

//done
void gameOver(){

  if (score >= maxScore) // user has won
  {
    display("Congratulations! You win!!");
    displayScore();
  }

  display("Sorry! Game Over! :(");
  displayScore();
  
  while(true)
  {}; // game over dead loop

}

//done
void setup() {
  // put your setup code here, to run once:
  time = maxTime;
  randomSeed(203847502347502);// random long as a seed

  Serial.begin(38400);
  BTSerial.begin(9600); //For Bluetooth Comm.

  //Initalize LCD Screen
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,squareSymbol);
  lcd.createChar(1,triangleSymbol);
  lcd.createChar(2,down);
  lcd.createChar(3,left);
  lcd.createChar(4,right);
  lcd.home();
  startGame();
}

//done
void loop() {

    int taskRandNum;
    taskRandNum = random(1,4);// generates a random number from {1,2,3}

    if(taskRandNum == 1)
    {
      display("Rage It!");
      if(!rageIt())
      {
        gameOver();
      }

    }
    else if(taskRandNum == 2)
    {
      display("Shoot It!");
      if(!shootIt())
      {
        gameOver();
      }

    }
    else if(taskRandNum == 3)
    {
      display("Combo It!");
      if(!comboIt())
      {
        gameOver();
      }

    }
    else
    {
      Serial.println("Random Num Error!");
    }

    display("Correct!");
    score++;

    if(score >= maxScore) // If user has won the game
    {
      gameOver();
    }

    if (score % 10 == 0) // only if we've reached a new task set, send the multiplier
    {
      BTSerial.print(multiplier);
      delay(100);
      multiplier++;
    }
    
}

//done
bool rageIt() {

    String command = "";
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

//done
bool comboIt() {

  String combo = "";
  String command = "";

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
    lcd.clear(); // clear the screen from displayCombo
    
    if(command == combo) // if the command from the slave matches
    {
      return true; // task passed
    }
    return false; // task failed
}

//done
bool shootIt() {
    String randDirection = "";
    String command = "";
    randDirection = directions[random(0,3)];
    displayShoot(randDirection);
    String correctShots[3] = {"6883", "7683", "8283"}; //down+square, left+square, right+square

    for(int i = 0; i < 715000 - 50000*multiplier; i++)
    {
       if(BTSerial.available() > 0)
      {
        delay(100);
        command = BTSerial.readString();
      }
    }

    return (((randDirection == "D") && (command == correctShots[0])) || 
            ((randDirection == "L") && (command == correctShots[1])) || 
            ((randDirection == "R") && (command == correctShots[2])));

}









