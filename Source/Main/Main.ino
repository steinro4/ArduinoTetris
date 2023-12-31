
#include <Arduino.h>
#include "LedControl.h"
#include "binary.h"
#include "LiquidCrystal.h"
#include "TimerOne.h"
#include "pitches.h"

//******************************************************************
//Sound
//notes in the melody:
int melody[] = {
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3, 
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3, 
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
};

//note durations: 4 = quarter note, 8 = eighth note, etc
int noteDurations[] = {
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};

bool soundOn = true;

//******************************************************************
//Hardware variables
/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc = LedControl(12, 11, 10, 2);

//Buttons
const int ButtonTurnLeft = 3;
const int ButtonTurnRight = 18;
const int ButtonMoveLeft = 19;
const int ButtonMoveRight = 20;
const int ButtonMoveDown = 21;

//Buzzerpin
const int BuzzerPin = 9;

/*
1 (Vss) -> GND
2 (Vdd) -> 5V
3 (V0) -> Pin 8
4 (RS) -> Pin 40
5 (RW) -> GND
6 (E) -> Pin 41
7
8
9
10
11 (D4) -> Pin 42
12 (D5) -> Pin 43
13 (D6) -> Pin 44
14 (D7) -> Pin 45
15 (A) -> 5V
16 (K) -> GND
*/
LiquidCrystal lcd(40, 41, 42, 43, 44, 45);
int Contrast=75;

byte lcdRightLPiece[8] = {
	0b00000,
	0b01100,
	0b01100,
	0b01100,
	0b01100,
	0b01111,
	0b01111,
	0b00000
};

byte lcdLeftLPiece[8] = {
	0b00000,
	0b00110,
	0b00110,
	0b00110,
	0b00110,
	0b11110,
	0b11110,
	0b00000
};

byte lcdLongPiece[8] = {
	0b00110,
	0b00110,
	0b00110,
	0b00110,
	0b00110,
	0b00110,
	0b00110,
	0b00110
};

byte lcdSquarePiece[8] = {
	0b00000,
	0b00000,
	0b01111,
	0b01111,
	0b01111,
	0b01111,
	0b00000,
	0b00000
};

byte lcdTPiece[8] = {
	0b00000,
	0b00000,
	0b11110,
	0b11110,
	0b01100,
	0b01100,
	0b00000,
	0b00000
};

byte lcdLeftZPiece[8] = {
	0b00000,
	0b00000,
	0b11100,
	0b11100,
	0b00111,
	0b00111,
	0b00000,
	0b00000
};

byte lcdRightZPiece[8] = {
	0b00000,
	0b00000,
	0b00111,
	0b00111,
	0b11100,
	0b11100,
	0b00000,
	0b00000
};

//******************************************************************
//Dynamic variables
struct Coordinates {
  int x;
  int y;
};

bool ButtonTurnLeftPressed;
bool ButtonTurnRightPressed;
bool ButtonMoveLeftPressed;
bool ButtonMoveRightPressed;
bool ButtonMoveDownPressed;

unsigned long turnLeftCooldown = 0;
unsigned long turnRightCooldown = 0;
unsigned long moveLeftCooldown = 0;
unsigned long moveRightCooldown = 0;
unsigned long moveDownCooldown = 0;

const int cooldownTime = 120;   //Cooldowntime of turnbuttons
const int moveTimeout = 100;    //Timeout for sideways movement

enum Shapes {
  eRightLPiece = 0,
  eLeftLPiece = 1,
  eLongPiece = 2,
  eSquarePiece = 3,
  eTPiece = 4,
  eLeftZPiece = 5,
  eRightZPiece = 6
};

Coordinates movingPiece[4];
Shapes movingShape;
Shapes nextShape;

//Pieces
Coordinates RightLPiece[4] = { 3, -3, 3, -2, 3, -1, 4, -1 };
Coordinates LeftLPiece[4] = { 4, -3, 4, -2, 4, -1, 3, -1 };
Coordinates LongPiece[4] = { 4, -4, 4, -3, 4, -2, 4, -1 };
Coordinates SquarePiece[4] = { 4, -2, 3, -2, 4, -1, 3, -1 };
Coordinates TPiece[4] = { 5, -2, 3, -2, 4, -2, 4, -1 };
Coordinates LeftZPiece[4] = { 5, -1, 3, -2, 4, -2, 4, -1 };
Coordinates RightZPiece[4] = { 3, -1, 5, -2, 4, -2, 4, -1 };

bool movementPossible = true;

//******************************************************************
//Static variables
bool gameOver = true;
unsigned long lastMillis;

//******************************************************************
//Main variables
// create playfield (addr, row, col)
bool staticField[8][16] = { {} };

//******************************************************************
//Game variables
int speed = 150;
int level = 1;
int score = 0;
int highscore;
int linesCleared = 0;

int pointsForRows[4] = {40, 100, 300, 1200};

void setup() {
  //******************************************************************
  //Hardware setup
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  // Set brightness to a low value
  lc.setIntensity(0, 1);
  lc.setIntensity(1, 1);
  // Clear the display
  lc.clearDisplay(0);
  lc.clearDisplay(1);

  //LCD
  pinMode(8, OUTPUT);
  analogWrite(8,Contrast);
  lcd.begin(16, 2);

  lcd.createChar(eLeftLPiece, lcdLeftLPiece);
  lcd.createChar(eRightLPiece, lcdRightLPiece);
  lcd.createChar(eLongPiece, lcdLongPiece);
  lcd.createChar(eSquarePiece, lcdSquarePiece);
  lcd.createChar(eTPiece, lcdTPiece);
  lcd.createChar(eLeftZPiece, lcdLeftZPiece);
  lcd.createChar(eRightZPiece, lcdRightZPiece);


  //Buttons
  pinMode(ButtonTurnLeft, INPUT_PULLUP);
  pinMode(ButtonTurnRight, INPUT_PULLUP);
  pinMode(ButtonMoveLeft, INPUT_PULLUP);
  pinMode(ButtonMoveRight, INPUT_PULLUP);
  pinMode(ButtonMoveDown, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ButtonTurnLeft), turnLeftPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(ButtonTurnRight), turnRightPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(ButtonMoveLeft), moveLeftPressed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ButtonMoveRight), moveRightPressed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ButtonMoveDown), moveDownPressed, CHANGE);

  //Buzzer
  pinMode(BuzzerPin, OUTPUT);

  //Interrupt
  Timer1.initialize(10000);
  Timer1.attachInterrupt(interruptLoop);
  Timer1.start();

  //******************************************************************
  //Dynamic setup
  Serial.begin(9600);

  randomSeed(analogRead(A7));
  getNewPiece(movingPiece, &nextShape);

  Serial.println("newStart**************************");

  //******************************************************************
  //Static setup
}


void loop() {
  //******************************************************************
  //Hardware Loop

  //******************************************************************
  //Dynamic Loop
  if (!gameOver) {
    movementPossible = false;
    if (!checkCollision(movingPiece)) { moveDown(movingPiece); }

    if (checkCollision(movingPiece)) {
      moveUp(movingPiece);
      addToField(movingPiece);
      checkRowIsFull(staticField);
      getNewPiece(movingPiece, &nextShape);
    }    
    turnPiece();
    movementPossible = true;

    showField();
    

    //******************************************************************
    //Static Loop
    //while (checkRowIsFull(staticField));
    if(gameIsOver(staticField)){setGameOver();}

    //delay
    delay(speed);

  }
  else{random(7);}    //So it doesn't always repeat
  
  //reset
  if (!digitalRead(ButtonTurnLeft) && !digitalRead(ButtonMoveRight)) {
    if (ton(true, lastMillis, 1000)) {
      if(score > highscore){highscore = score;}
      speed = 150;
      level = 1;
      score = 0;
      linesCleared = 0;
      lcd.clear();
      gameOver = false;
      clearField();
      getNewPiece(movingPiece, &nextShape);
      lastMillis = millis();
    }
  } else {
    lastMillis = millis();
  }
}

//******************************************************************
//Game Methods
void setGameOver(){
 gameOver = true;
 Serial.print("Highscore: ");
 Serial.print(highscore);
 Serial.print("   |   score: ");
 Serial.println(score);
}

void addScore(int numOfRows){
  score += level*pointsForRows[numOfRows-1];
  linesCleared += numOfRows;
  if(linesCleared >= 10 && level < 100){
    speed -= 10;
    linesCleared %= 10;
    level++;
  }
  updateLCD();
}

//******************************************************************
//Hardware Methods
void showField() {

  for(int address = 0; address <= 1; address++){
    
    for(int row = 0; row < 8; row++){
      byte value = 0;
      for(int col = 0; col < 8; col++){
        bool movingPieceHere = false;
        for(int i=0; i<4; i++){
          if(movingPiece[i].x == col && movingPiece[i].y == row+(address*8))
          {
            movingPieceHere = true;
            break;
          }
        }

        if(staticField[col][row+(address*8)] || movingPieceHere){
          value += 1 << 7-col;
        }       
      }

      lc.setRow(address, row, value);     
    }
  }
}

//Display
void updateLCD(){
  //Score
  lcd.setCursor(0, 0);
  lcd.print("Sc:");
  lcd.print(score);

  //Level
  lcd.setCursor(10, 0);
  lcd.print("Lvl:");
  lcd.print(level);

  //Highscore
  lcd.setCursor(0, 1);
  lcd.print("Hs:");
  lcd.print(highscore);

  //Next Piece
  lcd.setCursor(10, 1);
  lcd.print("Next:");
  lcd.write((byte)nextShape);
}

//******************************************************************
//Dynamic Methods

//*********************
//Get new Piece
void getNewPiece(Coordinates *piece, Shapes *nextShape) {
  Coordinates *tempPointer;
  movingShape = *nextShape;
  *nextShape = random(7);
  updateLCD();

  switch (movingShape) {
    case 0: tempPointer = RightLPiece; break;
    case 1: tempPointer = LeftLPiece; break;
    case 2: tempPointer = LongPiece; break;
    case 3: tempPointer = SquarePiece; break;
    case 4: tempPointer = TPiece; break;
    case 5: tempPointer = LeftZPiece; break;
    case 6: tempPointer = RightZPiece; break;
  }
  //Make copy so the original doesn't get overwritten
  for (int i = 0; i < 4; i++) {
    piece[i] = tempPointer[i];
  }
}

//*********************
//Move down
void moveDown(Coordinates *piece) {
  for (int i = 0; i < 4; i++) {
    piece[i].y++;
  }
}

//*********************
//Move up
void moveUp(Coordinates *piece) {
  for (int i = 0; i < 4; i++) {
    piece[i].y--;
  }
}

//*********************
//Move left
void moveLeft(Coordinates *piece) {
  bool freeToMove = true;

  for (int i = 0; i < 4; i++) {
    if (piece[i].x <= 0 || piece[i].y >= 16)  //numRows
    {
      freeToMove = false;
    }

    if (freeToMove && piece[i].y >= 0) {
      if (staticField[piece[i].x - 1][piece[i].y]) {
        freeToMove = false;
      }
    }
  }

  if (freeToMove) {
    for (int i = 0; i < 4; i++) {
      piece[i].x--;
    }
  }
}

//*********************
//Move right
void moveRight(Coordinates *piece) {
  bool freeToMove = true;

  for (int i = 0; i < 4; i++) {
    if (piece[i].x > 6 || piece[i].y >= 16)  //numRows
    {
      freeToMove = false;
    }

    if (freeToMove && piece[i].y >= 0) {
      if (staticField[piece[i].x + 1][piece[i].y]) {
        freeToMove = false;
      }
    }
  }

  if (freeToMove) {
    for (int i = 0; i < 4; i++) {
      piece[i].x++;
    }
  }
}

//*********************
//Turn Left
void turnLeft(bool staticField[8][16], Coordinates *piece) {
  float xTurningPoint = 0;
  float yTurningPoint = 0;

  int tempX = 0;
  int tempY = 0;

  Coordinates tempCoords[4];

  for (int i = 0; i < 4; i++) {
    xTurningPoint += piece[i].x;
    yTurningPoint += piece[i].y;
  }

  switch (movingShape) {
    case eRightLPiece:
    case eLeftLPiece:
    case eTPiece:
      xTurningPoint = round(xTurningPoint / 4);
      yTurningPoint = round(yTurningPoint / 4);

      for (int i = 0; i < 4; i++) {
        tempCoords[i].x = int(xTurningPoint) + (piece[i].y - int(yTurningPoint));
        tempCoords[i].y = int(yTurningPoint) - (piece[i].x - int(xTurningPoint));
      }
      break;
    case eSquarePiece: return;
    case eLongPiece:
    case eLeftZPiece:
    case eRightZPiece:
      xTurningPoint = xTurningPoint / 4;
      yTurningPoint = yTurningPoint / 4;

      for (int i = 0; i < 4; i++) {
        tempCoords[i].x = int(xTurningPoint) + (piece[i].y - int(yTurningPoint));
        tempCoords[i].y = int(yTurningPoint) - (piece[i].x - round(xTurningPoint));
      }
      break;
  }



  for (int i = 0; i < 4; i++) {

    if (tempCoords[i].x < 0
        || tempCoords[i].x > 7
        || tempCoords[i].y > 15) {
      return;  //Turning not possible due to part beeing out of the field
    }

    if (tempCoords[i].y > 0) {
      if (staticField[tempCoords[i].x][tempCoords[i].y]) {
        return;  //Turning not possible due to part beeing inside the staticField
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    piece[i] = tempCoords[i];
  }
}

//*********************
//Turn Right
void turnRight(bool staticField[8][16], Coordinates *piece) {
  float xTurningPoint = 0;
  float yTurningPoint = 0;
  int tempX = 0;
  int tempY = 0;

  Coordinates tempCoords[4];

  for (int i = 0; i < 4; i++) {
    xTurningPoint += piece[i].x;
    yTurningPoint += piece[i].y;
  }

  switch (movingShape) {
    case eRightLPiece:
    case eLeftLPiece:
    case eTPiece:
      xTurningPoint = round(xTurningPoint / 4);
      yTurningPoint = round(yTurningPoint / 4);

      for (int i = 0; i < 4; i++) {
        tempCoords[i].x = int(xTurningPoint) - (piece[i].y - int(yTurningPoint));
        tempCoords[i].y = int(yTurningPoint) + (piece[i].x - int(xTurningPoint));
      }

      break;
    case eSquarePiece: return;
    case eLongPiece:
    case eLeftZPiece:
    case eRightZPiece:
      xTurningPoint = xTurningPoint / 4;
      yTurningPoint = yTurningPoint / 4;

      for (int i = 0; i < 4; i++) {
        tempCoords[i].x = int(xTurningPoint) - (piece[i].y - round(yTurningPoint));
        tempCoords[i].y = int(yTurningPoint) + (piece[i].x - int(xTurningPoint));
      }
      break;
  }

  for (int i = 0; i < 4; i++) {

    if (tempCoords[i].x < 0
        || tempCoords[i].x > 7
        || tempCoords[i].y > 15) {
      return;  //Turning not possible due to part beeing out of the field
    }

    if (tempCoords[i].y > 0) {
      if (staticField[tempCoords[i].x][tempCoords[i].y]) {
        return;  //Turning not possible due to part beeing inside the staticField
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    piece[i] = tempCoords[i];
  }
}

void turnPiece() {
  if (ButtonTurnLeftPressed) { turnLeft(staticField, movingPiece); }
  if (ButtonTurnRightPressed) { turnRight(staticField, movingPiece); }
  ButtonTurnLeftPressed = ButtonTurnRightPressed = false;
}

//******************************************************************
//Static Methods
bool checkCollision(Coordinates *movingPiece) {

  for (int i = 0; i < 4; i++) {
    if (movingPiece[i].y >= 0) {
      if (movingPiece[i].y >= 16) {
        return true;
      }
      if (staticField[movingPiece[i].x][movingPiece[i].y]) {
        return true;
      }
    }
  }
  return false;
}

void addToField(Coordinates *movingPiece) {
  for (int i = 0; i < 4; i++) {
    if(movingPiece[i].y >= 0){staticField[movingPiece[i].x][movingPiece[i].y] = true;}    
  }
}

bool checkRowIsFull(bool field[8][16]) {
  int streak = 0;
  int y = 16;
  while(y >= 0){
    y--;
    bool rowFull = true;
    for (int x = 0; x < 8; x++) {
      if(!field[x][y]){rowFull = false;break;}
    }

    if(rowFull){
      moveRows(y);
      y++; //so it continues on same line
      streak++;
    }
    else if(streak > 0){
      addScore(streak);
      streak = 0;
    }
  }
}

void moveRows(int rowToDelete) {
  for (int r = rowToDelete; r > 0; r--) {
    for (int c = 0; c < 8; c++) {
      staticField[c][r] = staticField[c][r - 1];
      if (r == 1) {
        staticField[c][0] = false;
      }
    }
  }
}

bool gameIsOver(bool field[8][16]) {
  for (int c = 0; c < 8; c++) {
    if (field[c][0]) { return true; }
  }
  return false;
}

void clearField() {
  for (int r = 0; r < 16; r++) {
    for (int c = 0; c < 8; c++) {
      staticField[c][r] = false;
    }
  }
}

//start delay
bool ton(bool start, unsigned long lastMillis, unsigned long delay) {
  if (start && (millis() - lastMillis) >= delay) { return true; }
  return false;
}

//******************************************************************
//Interrupt loop
unsigned long prevMillisSound = 0;
unsigned long prevMillisMove = 0;
int thisNote = 0;
void interruptLoop(){
  unsigned long actMillis = millis();

  if(prevMillisMove + moveTimeout < actMillis)
  {
    prevMillisMove = actMillis;
    if(ButtonMoveLeftPressed && movementPossible) { moveLeft(movingPiece); showField();}
    if(ButtonMoveRightPressed && movementPossible) { moveRight(movingPiece); showField();}
    
    if(ButtonMoveDownPressed && movementPossible) {
       moveDown(movingPiece);
       if (checkCollision(movingPiece)) {moveUp(movingPiece);} else {showField();}
    }
  }


  //********************************
  //Sound
  if(gameOver){thisNote=0;return;}
  int noteDuration = 1000/noteDurations[thisNote];
  if(soundOn){
    tone(9, melody[thisNote],noteDuration);
  }

  int pauseBetweenNotes = noteDuration * float(speed)/100; //1.30;
  
  if(prevMillisSound + pauseBetweenNotes > actMillis){
    return;
  }
  else{    
    prevMillisSound = actMillis;
    noTone(9); //stop the tone playing:
    thisNote++;
    if(thisNote >= sizeof(melody) / sizeof(melody[0])){
      thisNote = 0;
    }
  }
}

//******************************************************************
//Button interrupts
void turnLeftPressed(){
  if(turnLeftCooldown + cooldownTime > millis()){return;}  
  turnLeftCooldown = millis();
  if(movementPossible){
    turnLeft(staticField, movingPiece);
    showField();
  }
  else{
    ButtonTurnLeftPressed = true;
  }
}

void turnRightPressed(){
  if(turnRightCooldown + cooldownTime > millis()){return;}  
  turnRightCooldown = millis();
  if(movementPossible){
    turnRight(staticField, movingPiece);
    showField();
  }
  else{
    ButtonTurnRightPressed = true;
  }
}

void moveLeftPressed(){
  ButtonMoveLeftPressed = !digitalRead(ButtonMoveLeft);
}

void moveRightPressed(){
  ButtonMoveRightPressed = !digitalRead(ButtonMoveRight);
}

void moveDownPressed(){
  ButtonMoveDownPressed = !digitalRead(ButtonMoveDown);
}

