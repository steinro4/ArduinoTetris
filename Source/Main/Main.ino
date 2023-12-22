
#include <Arduino.h>
#include "LedControl.h"
#include "binary.h"
#include "LiquidCrystal.h"
#include "Joystick.h"
#include "TimerOne.h"
//******************************************************************
//Hardware variables
/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc = LedControl(12, 11, 10, 2);

//Joystick:
const int SW_pin = 2;  // Taster-Pin
const int X_pin = A0;  // X-Ausgang
const int Y_pin = A1;  // Y-Ausgang


//******************************************************************
//Dynamic variables
struct Coordinates {
  int x;
  int y;
};

Coordinates movingPiece[4];

//Pieces
Coordinates RightLPiece[4] = { 3, -3, 3, -2, 3, -1, 4, -1 };
Coordinates LeftLPiece[4] = { 4, -3, 4, -2, 4, -1, 3, -1 };
Coordinates LongPiece[4] = { 4, -4, 4, -3, 4, -2, 4, -1 };
Coordinates SquarePiece[4] = { 4, -2, 3, -2, 4, -1, 3, -1 };
Coordinates TPiece[4] = { 5, -2, 3, -2, 4, -2, 4, -1 };
Coordinates LeftZPiece[4] = { 5, -1, 3, -2, 4, -2, 4, -1 };
Coordinates RightZPiece[4] = { 3, -1, 5, -2, 4, -2, 4, -1 };

//******************************************************************
//Static variables
bool gameOver = false;
unsigned long lastMillis;
bool doReset;

//******************************************************************
//Main variables
// create playfield (addr, row, col)
bool staticField[8][16] = { {} };


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

  //Joystick
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  //Interrupt
  Timer1.initialize(200000);
  Timer1.attachInterrupt(checkInputs);
  Timer1.start();

  //******************************************************************
  //Dynamic setup
  Serial.begin(9600);

  randomSeed(analogRead(A7));
  getNewPiece(movingPiece);

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
    moveDown(movingPiece);

    noInterrupts();
    if (checkCollision(staticField, movingPiece)) {
      moveUp(movingPiece);
      addToField(staticField, movingPiece);
      getNewPiece(movingPiece);
    }
    showField(staticField);
    showPiece(movingPiece);
    interrupts();


    //******************************************************************
    //Static Loop
    while (checkRowIsFull(staticField))
      ;
    if (gameIsOver(staticField)) { gameOver = true; }
    delay(200);
  }

  //reset
  if (!digitalRead(SW_pin)) {
    if (ton(true, lastMillis, 3000)) {
      gameOver = false;
      clearField();
      getNewPiece(movingPiece);
      lastMillis = millis();
    }
  } else {
    lastMillis = millis();
  }
}

//******************************************************************
//Hardware Methods
void showField(bool staticField[8][16]) {
  int addr = 0;
  int k = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      if (j > 7) {
        k = j - 8;
        addr = 1;
      } else {
        k = j;
        addr = 0;
      }
      lc.setLed(addr, k, i, staticField[i][j]);
    }
  }
}

void showPiece(Coordinates *movingPiece) {
  int addr = 0;
  int k = 0;

  for (int i = 0; i < 4; i++) {
    if (movingPiece[i].y > 7) {
      k = movingPiece[i].y - 8;
      addr = 1;
    } else {
      k = movingPiece[i].y;
      addr = 0;
    }
    lc.setLed(addr, k, movingPiece[i].x, true);
  }
}

void checkInputs() {
  if (!digitalRead(SW_pin)) { turnRight(staticField, movingPiece); }  //press joystick
  if (analogRead(X_pin) > 1000) { moveRight(movingPiece); }
  if (analogRead(X_pin) < 20) { moveLeft(movingPiece); }
  if (analogRead(Y_pin) > 1000) { turnLeft(staticField, movingPiece); }
}

//******************************************************************
//Dynamic Methods

//*********************
//Get new Piece
void getNewPiece(Coordinates *piece) {
  Coordinates *tempPointer;
  switch (random(7)) {
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

    if (freeToMove) {
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

    if (freeToMove) {
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

  Coordinates tempCoords[4];

  for (int i = 0; i < 4; i++) {
    xTurningPoint += piece[i].x;
    yTurningPoint += piece[i].y;
  }

  xTurningPoint = round(xTurningPoint / 4);
  yTurningPoint = round(yTurningPoint / 4);

  for (int i = 0; i < 4; i++) {
    int tempX = 0;
    int tempY = 0;
    tempCoords[i].x = int(xTurningPoint) + (piece[i].y - int(yTurningPoint));
    tempCoords[i].y = int(yTurningPoint) - (piece[i].x - int(xTurningPoint));
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

  Coordinates tempCoords[4];

  for (int i = 0; i < 4; i++) {
    xTurningPoint += piece[i].x;
    yTurningPoint += piece[i].y;
  }

  xTurningPoint = round(xTurningPoint / 4);
  yTurningPoint = round(yTurningPoint / 4);

  for (int i = 0; i < 4; i++) {
    int tempX = 0;
    int tempY = 0;
    tempCoords[i].x = int(xTurningPoint) - (piece[i].y - int(yTurningPoint));
    tempCoords[i].y = int(yTurningPoint) + (piece[i].x - int(xTurningPoint));
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

//******************************************************************
//Static Methods
bool checkCollision(bool staticField[8][16], Coordinates *movingPiece) {

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

void addToField(bool field[8][16], Coordinates *movingPiece) {
  for (int i = 0; i < 4; i++) {
    staticField[movingPiece[i].x][movingPiece[i].y] = true;
  }
}

bool checkRowIsFull(bool field[8][16]) {
  bool lastRowWasFull = false;
  int countRowInOrder = 1;
  for (int r = 15; r >= 0; r--) {
    bool rowIsFull = true;
    for (int c = 0; c < 8; c++) {
      if (field[c][r] == false) {
        rowIsFull = false;
        lastRowWasFull = false;
        break;
      }
    }
    if (rowIsFull) {
      moveRows(r);
      if (lastRowWasFull) { countRowInOrder++; }
      lastRowWasFull = true;
      return true;
    }
  }
  return false;
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
