#include "Hardware.h"
#include "Dynamic.h"
#include "Static.h"

// create playfield (addr, row, col)
bool field[8][16] = { {} };

void setup() {
  hardwareInit();
}




void loop() {
  field[0][0] = true;   //first led 1st matrix
  field[7][7] = true;   //last led 1st matrix
  field[0][8] = true;   //first led 2nd matrix
  field[7][15] = true;  //last led 2st matrix
  setLeds(field);
}