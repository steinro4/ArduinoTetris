
#include <Arduino.h>
#include "LedControl.h"
#include "binary.h"
#include "LiquidCrystal.h"
#include "Joystick.h"
//******************************************************************
//Hardware variables
/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc = LedControl(12, 11, 10, 2);


//******************************************************************
//Dynamic variables
struct Coordinates {
  int x;
  int y;
};

Coordinates *movingPiece;

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


  //******************************************************************
  //Dynamic setup
  movingPiece = getNewPiece();

  Serial.begin(9600);

  Serial.println("newStart**************************");

  //******************************************************************
  //Static setup
}




void loop() {
  //******************************************************************
  //Hardware Loop
  staticField[0][0] = true;   //first led 1st matrix
  staticField[0][1] = true;   //last led 1st matrix
  staticField[4][10] = true;  //first led 2nd matrix
  staticField[7][15] = true;  //last led 2st matrix

  //******************************************************************
  //Dynamic Loop
  movingPiece = moveDown(movingPiece);

  if (checkCollision(staticField, movingPiece)) {
    movingPiece = moveUp(movingPiece);
    movingPiece = moveUp(movingPiece);
    movingPiece = moveUp(movingPiece);
    movingPiece = moveUp(movingPiece);
    movingPiece = turnLeft(movingPiece);
    addToField(staticField,movingPiece);
  }

  showField(staticField);
  showPiece(movingPiece);
  

  if(movingPiece[0].y > 10){
    movingPiece = getNewPiece();
  }
  delay(50);

  //******************************************************************
  //Static Loop
  //Serial.println(checkCollision(staticField, movingPiece));
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


//******************************************************************
//Dynamic Methods

//*********************
//Get new Piece
Coordinates tempPiece[4];
Coordinates *getNewPiece() {

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
    tempPiece[i] = tempPointer[i];
  }

  return tempPiece;
}

//*********************
//Move down
Coordinates *moveDown(Coordinates *piece) {
  for (int i = 0; i < 4; i++) {
    piece[i].y++;
  }
  return piece;
}

//*********************
//Move up
Coordinates *moveUp(Coordinates *piece) {
  for (int i = 0; i < 4; i++) {
    piece[i].y--;
  }
  return piece;
}

//*********************
//Move left
Coordinates *moveLeft(Coordinates *piece) {
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

  return piece;
}

//*********************
//Move right
Coordinates *moveRight(Coordinates *piece) {
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

  return piece;
}

//*********************
//Turn Left

//To do: check if turning is possible (if too close to the wall)
Coordinates * turnLeft(Coordinates *piece){
  float xTurningPoint = 0;
  float yTurningPoint = 0;

  for(int i = 0; i < 4; i++){
    xTurningPoint += piece[i].x;
    yTurningPoint += piece[i].y;
  }

  xTurningPoint = round(xTurningPoint/4);
  yTurningPoint = round(yTurningPoint/4);
  
  for(int i = 0; i < 4; i++){
    int tempX = 0;
    int tempY = 0;
    tempX = int(xTurningPoint) + (piece[i].y - int(yTurningPoint));   
    tempY = int(yTurningPoint) - (piece[i].x - int(xTurningPoint));

    piece[i].x = tempX;
    piece[i].y = tempY;
  }

  return piece;
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
