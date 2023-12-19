#include "Hardware.h"

//******************************************************************
//Dynamic variables
struct Coordinates{
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
bool field[8][16] = { {} };


void setup() {
  //******************************************************************
  //Dynamic setup
  movingPiece = getNewPiece();



  hardwareInit();
  Serial.begin(9600);

  //******************************************************************
  //Static setup
}




void loop() {
  field[0][0] = true;   //first led 1st matrix
  field[7][7] = true;   //last led 1st matrix
  field[0][8] = true;   //first led 2nd matrix
  field[7][15] = true;  //last led 2st matrix
  setLeds(field);


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
