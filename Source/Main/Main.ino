#include "Hardware.h"

//******************************************************************
//Dynamic variables
struct Coordinates{
  int x;
  int y;
};

Coordinates *movingPiece;

//Pieces
Coordinates RightZPiece[4] = {3,-1,5,-2,4,-2,4,-1};
Coordinates RightLPiece[4] = {3,-3,3,-2,3,-1,4,-1};
Coordinates LeftLPiece[4] = {4,-3,4,-2,4,-1,3,-1};
Coordinates LongPiece[4] = {4,-4,4,-3,4,-2,4,-1};
Coordinates SquarePiece[4] = {4,-2,3,-2,4,-1,3,-1};
Coordinates TPiece[4] = {5,-2,3,-2,4,-2,4,-1};
Coordinates LeftZPiece[4] = {5,-1,3,-2,4,-2,4,-1};

//******************************************************************
//Static variables

//******************************************************************
//Main variables
// create playfield (addr, row, col)
bool field[8][16] = { {} };


void setup() {
  //******************************************************************
  //Dynamic setup

  hardwareInit();
  Serial.begin(9600);

  movingPiece = getNewPiece();

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
  for(int i=0; i < 4; i++)
  {
    Serial.println(movingPiece[i].y);
  }
  delay(500);

  //******************************************************************
  //Static Loop
}



//******************************************************************
//Dynamic Methods
Coordinates * getNewPiece(){
  return RightZPiece;
}

//******************************************************************
//Static Methods
