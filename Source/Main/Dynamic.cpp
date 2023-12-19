#include "Dynamic.h"

struct Coordinates{
  int x;
  int y;
};


Coordinates RightLPiece[4] = {3,-3,3,-2,3,-1,4,-1};
Coordinates LeftLPiece[4] = {(4,-3),(4,-2),(4,-1),(3,-1)};
Coordinates LongPiece[4] = {(4,-4),(4,-3),(4,-2),(4,-1)};
Coordinates SquarePiece[4] = {(4,-2),(3,-2),(4,-1),(3,-1)};
Coordinates TPiece[4] = {(5,-2),(3,-2),(4,-2),(4,-1)};
Coordinates LeftZPiece[4] = {(5,-1),(3,-2),(4,-2),(4,-1)};
//Coordinates RightZPiece[4] = {3,-1,5,-2,4,-2,4,-1};
//Coordinates RightZPiece[4] = {(3,-1),(5,-2),(4,-2),(4,-1)};

//*************************************************************
/*Coordinates * getNewPiece(){
  return RightZPiece;
}*/

    