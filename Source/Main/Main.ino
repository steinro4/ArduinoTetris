
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
Coordinates RightLPiece[4] = {3,-3,3,-2,3,-1,4,-1};
Coordinates LeftLPiece[4] = {4,-3,4,-2,4,-1,3,-1};
Coordinates LongPiece[4] = {4,-4,4,-3,4,-2,4,-1};
Coordinates SquarePiece[4] = {4,-2,3,-2,4,-1,3,-1};
Coordinates TPiece[4] = {5,-2,3,-2,4,-2,4,-1};
Coordinates LeftZPiece[4] = {5,-1,3,-2,4,-2,4,-1};
Coordinates RightZPiece[4] = {3,-1,5,-2,4,-2,4,-1};

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

  //******************************************************************
  //Static setup
}




void loop() {
  //******************************************************************
  //Hardware Loop
  staticField[0][0] = true;   //first led 1st matrix
  staticField[7][7] = true;   //last led 1st matrix
  staticField[0][8] = true;   //first led 2nd matrix
  staticField[7][15] = true;  //last led 2st matrix
  showField(staticField);


  //******************************************************************
  //Dynamic Loop
  movingPiece = moveDown(movingPiece);
  for(int i=0; i < 4; i++)
  {
    Serial.println(movingPiece[i].y);
  }
  if(movingPiece[0].y > 10){
    movingPiece = getNewPiece();
  }
  delay(500);

  //******************************************************************
  //Static Loop
  Serial.println(checkCollision(staticField, movingPiece));
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
      lc.setLed(addr, i, k, staticField[i][j]);
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
    lc.setLed(addr, movingPiece[i].x, movingPiece[i].y, true);
  }
}


//******************************************************************
//Dynamic Methods

//*********************
//Get new Piece
Coordinates tempPiece[4];
Coordinates * getNewPiece(){

  Coordinates *tempPointer;

  switch(random(7)){
    case 0: tempPointer = RightLPiece; break;
    case 1: tempPointer = LeftLPiece; break;
    case 2: tempPointer = LongPiece; break;
    case 3: tempPointer = SquarePiece; break;
    case 4: tempPointer = TPiece; break;
    case 5: tempPointer = LeftZPiece; break;
    case 6: tempPointer = RightZPiece; break;
  }

  //Make copy so the original doesn't get overwritten
  for(int i = 0; i < 4; i++)
  {
      tempPiece[i] = tempPointer[i];
  }

  return tempPiece;
}

//*********************
//Move down
Coordinates * moveDown(Coordinates *piece){
  for(int i = 0; i < 4; i++)
  {
    piece[i].y++;
  }
  return piece;
}

//*********************
//Move up
Coordinates * moveUp(Coordinates *piece){
  for(int i = 0; i < 4; i++)
  {
    piece[i].y--;
  }
  return piece;
}

//*********************
//Move left
Coordinates * moveLeft(Coordinates *piece){
  bool freeToMove = true;

  for(int i = 0; i < 4; i++)
  {
    if(piece[i].x <= 0 || piece[i].y >= 16) //numRows
    {
      freeToMove = false;
    }

    if(freeToMove)
    {
      if(field[piece[i].x-1][piece[i].y])
      {
        freeToMove = false;
      }
    }
  }

  if(freeToMove)
  {
    for(int i = 0; i < 4; i++)
    {
      piece[i].x--;
    }
  }

  return piece;
}

//*********************
//Move right
Coordinates * moveRight(Coordinates *piece){
  bool freeToMove = true;

  for(int i = 0; i < 4; i++)
  {
    if(piece[i].x > 7 || piece[i].y >= 16) //numRows
    {
      freeToMove = false;
    }

    if(freeToMove)
    {
      if(field[piece[i].x+1][piece[i].y])
      {
        freeToMove = false;
      }
    }
  }

  if(freeToMove)
  {
    for(int i = 0; i < 4; i++)
    {
      piece[i].x++;
    }
  }

  return piece;
}

//******************************************************************
//Static Methods
bool checkCollision(bool staticField[8][16], Coordinates *movingPiece) {
  for (int r = 0; r < 16; r++) {
    for (int c = 0; c < 8; c++) {
      for (int i = 0; i < 4; i++) {
        if ((staticField[r][c] && r == movingPiece[i].x && c == movingPiece[i].y) || movingPiece[i].y > 15) {
          return true;
        }
      }
    }
  }
  return false;
}
