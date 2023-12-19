#include "Hardware.h"
#include "Dynamic.h"
#include "Static.h"

struct Coordinates{
  int x;
  int y;
};

Coordinates *movingPiece;//[4];
Coordinates RightZPiece[4] = {3,-1,5,-2,4,-2,4,-1};

// create playfield (addr, row, col)
bool field[8][16] = { {} };

void setup() {
  hardwareInit();
  Serial.begin(9600);

  movingPiece = getNewPiece();
}




void loop() {
  field[0][0] = true;   //first led 1st matrix
  field[7][7] = true;   //last led 1st matrix
  field[0][8] = true;   //first led 2nd matrix
  field[7][15] = true;  //last led 2st matrix
  setLeds(field);


  //Dynamic
  
  for(int i=0; i < 4; i++)
  {
    Serial.println(movingPiece[i].y);
    
    //Serial.print('   ');
    //Serial.println(RightZPiece[i].y);
    //Serial.println("hallo");
  }
  delay(500);
}



//*************************************************************

Coordinates * getNewPiece(){
  return RightZPiece;
}
