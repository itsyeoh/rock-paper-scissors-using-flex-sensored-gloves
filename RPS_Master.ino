//
//CS362 Spring 2019 Term Project 
//
// [ TEAM NUMBER ]
// Team 33
//
// [ TEAM MEMBERS ] 
// Jason Yeoh (jyeoh2) 
// Ho Chon (hchon6)
//
// [ PROJECT NAME ]
// Rock-Paper-Scissor Flex Sensor Gloves
//
// [ ABSTRACT ] 
// Why play rock-paper-scissor the normal way when you can upgrade it to have a better experience? 
// Using flex sensing technology and an inter-integrated Arduino circuit, it would increase the fun 
// in playing a simple game. The timer countdown can be used to prevent cheating and it would light 
// up corresponding to a victory or loss. The winner would even get its own victory tune, improving 
// winning experience. 

#define PAPER 1
#define SCISSOR 2
#define ROCK 3
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
const int p1RingFlex = A1, p1MiddleFlex = A0;
const int p2RingFlex = A3, p2MiddleFlex = A2;
String picks[3] = {"PAPER", "SCISSOR", "ROCK"};
int winner, gameWinner, numRounds, flexValue, game = 0, prevGame;
int currButton = 0;


// Create a Player object consisting of sensor values, pick and current score
struct player
{
  int ringValue;
  int middleValue;
  int pick;
  int score;
};
typedef struct player Player;

Player p1, p2;


// Destruct the object
void destruct(Player *p)
{
  p->ringValue = 0;
  p->middleValue = 0;
  p->pick = 0;
  p->score = 0;
}


// Display a 3-second countdown on the LCD display
void displayCountdown(int round)
{ 
  for(int i = 3; i > 0; i--)
  {
    lcd.setCursor(0, 0);
    lcd.print("[   ROUND #");
    lcd.print(round);
    lcd.print("   ]");
    lcd.setCursor(8, 1);
    lcd.print(i);
    delay(1000);
    lcd.clear();
  }
}


// Identify the user pick given the two flex sensor values
void identifyPick(Player *p)
{
  flexValue = 640;
  
  if(p->ringValue < flexValue && p->middleValue < flexValue)
  {
    p->pick = PAPER;
  }
  else if((p->middleValue < flexValue) && 
          (p->ringValue > flexValue && p->ringValue <= 1023) )
  {
    p->pick = SCISSOR;
  }
  else if( (p->ringValue > flexValue && p->ringValue <= 1023) &&
           (p->middleValue > flexValue && p->middleValue <= 1023) )
  {
    p->pick = ROCK;
  }
}


// Return the winner of the RPS round
int comparePicks(Player *pA, Player *pB)
{
  int p1 = pA->pick;
  int p2 = pB->pick;
  
  if(p1 == p2)
  {
    return 3; // TIE
  }
  else
  {
    if(p1 == PAPER) {
      if(p2 == SCISSOR) { pB->score++; return 2; }
      if(p2 == ROCK)    { pA->score++; return 1; }
    }
    else if(p1 == SCISSOR) {
      if(p2 == PAPER)   { pA->score++; return 1; }
      if(p2 == ROCK)    { pB->score++; return 2; }
    }
    else if(p1 == ROCK) {
      if(p2 == PAPER)   { pB->score++; return 2; }
      if(p2 == SCISSOR) { pA->score++; return 1; }
    }
  }//end else 
}


// Show the scoreboard on the LCD display
void displayScore()
{
  String p1Message = "P1: " + picks[p1.pick - 1];
  String p2Message = "P2: " + picks[p2.pick - 1];
  String winMessage = "The winner is player ";

  // Display user picks 
  lcd.setCursor(0, 0);
  lcd.print(p1Message);
  lcd.setCursor(0, 1);
  lcd.print(p2Message);
  delay(2000);
  lcd.clear();

  // Display the outcome of the game
  lcd.setCursor(0, 0);
  if(winner == 3)
  {
    lcd.print("Tie game!");
  }
  else
  {
    lcd.print("[ ROUND WINNER ]");
    lcd.setCursor(0, 1);
    lcd.print("Player ");
    lcd.print(winner);
  }
  delay(1000);
  lcd.clear();

  // Display scoreboard
  p1Message = "P1: " + String(p1.score);
  p2Message = "P2: " + String(p2.score);

  lcd.setCursor(0, 0);
  lcd.print("[  SCOREBOARD  ]");
  lcd.setCursor(0, 1);
  lcd.print(p1Message);
  lcd.setCursor(8, 1);
  lcd.print(p2Message);
  delay(1000);
 
  lcd.clear();
}


// Display the overall winner
void displayResults()
{
  if(p1.score == p2.score)
  {
    lcd.setCursor(0, 0);
    lcd.print("TIE GAME!");
  }
  else
  {
    gameWinner = p1.score > p2.score ? 1 : 2;
    lcd.setCursor(0, 0);
    lcd.print("CONGRATULATIONS!");
    lcd.setCursor(0, 1);
    lcd.print("Player ");
    lcd.print(gameWinner);
  }
  
  delay(2000);
  lcd.clear();

  // Deallocate the following Player objects
  destruct(&p1);
  destruct(&p2);
}


// Initialize the game by utilizing the button data from the slave component
int initializeGame()
{
  lcd.setCursor(0, 0);
  lcd.print("Start game");
  lcd.setCursor(0, 1);
  lcd.print("End game");

  Wire.onReceive(receiveEvent);
  return currButton;
}

// Play a single round of the game
void playOneRound()
{
  p1.ringValue = analogRead(p1RingFlex);
  p1.middleValue = analogRead(p1MiddleFlex);
  p2.ringValue = analogRead(p2RingFlex);
  p2.middleValue = analogRead(p2MiddleFlex);
  
  identifyPick(&p1);
  identifyPick(&p2);

  winner = comparePicks(&p1, &p2);
  displayScore();
}

// Play the game
void playGame()
{
  numRounds = 3;
  lcd.clear();
  
  for(int i=0; i<numRounds; i++)
  {
    displayCountdown(i+1);
    playOneRound();
  }

  delay(500);
  
  // send the game winner to the slave Arduino
  Wire.beginTransmission(9);
  if(p1.score == p2.score)     
    Wire.write(3); // TIE GAME
  else if(p1.score > p2.score) 
    Wire.write(1); // PLAYER ONE WON
  else                         
    Wire.write(2); // PLAYER TWO WON
  Wire.endTransmission();

  displayResults();
}


// Display a game over screen
void gameOver()
{
  lcd.clear();
  lcd.print("GAME OVER");
  delay(2000);
}

// Receive the button data from the slave component
void receiveEvent(int bytes)
{
  currButton = Wire.read();
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  // Initialize player objects
  Player p1 = { .ringValue = 0, .middleValue = 0, .pick = 0, .score = 0 };
  Player p2 = { .ringValue = 0, .middleValue = 0, .pick = 0, .score = 0 };
}

  
void loop() {
  delay(500);
  game = initializeGame();
  
  if(game == 1)         // START GAME
  {
    playGame();
  }
  else if(game == 2)    // END GAME
  {
    gameOver();
  }

  if(prevGame != game) 
    lcd.clear();

  delay(10);
  prevGame = game;
  game = 0;
  currButton = 0;
}
