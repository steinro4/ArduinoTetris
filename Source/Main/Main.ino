
#include "LedControl.h"
#include "binary.h"

/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc = LedControl(12, 11, 10, 2);

const int numRows = 8;
const int numCols = 16;


// create playfield (addr, row, col)
bool field[numRows][numCols] = { {  } };

// init actual shape
int currentShape[4][4] = { { 0 } };


void setup() {
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  // Set brightness to a low value
  lc.setIntensity(0, 1);
  lc.setIntensity(1, 1);
  // Clear the display
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  //start monitor
  Serial.begin(9600);
}

void setShape(int shape) {
  // Define different shapes
  // 0: I, 1: J, 2: L, 3: O, 4: S, 5: Z, 6: T
  switch (shape) {
    case 0:
      currentShape[0][0] = 1;
      currentShape[0][1] = 1;
      currentShape[0][2] = 1;
      currentShape[0][3] = 1;
      break;
    case 1:
      /*{1, 0, 0, 0}
      {1, 1, 1, 0}
      {0, 0, 0, 0}
      {0, 0, 0, 0}*/
      currentShape[0][0] = 1;
      currentShape[1][0] = 1;
      currentShape[1][1] = 1;
      currentShape[1][2] = 1;
      break;

    case 2:
      /*{1, 1, 1, 0}
      {1, 0, 0, 0}
      {0, 0, 0, 0}
      {0, 0, 0, 0}*/
      currentShape[0][0] = 1;
      currentShape[0][1] = 1;
      currentShape[0][2] = 1;
      currentShape[1][0] = 1;
      break;


    case 3:
      /*{0, 1, 1, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}*/
      currentShape[0][1] = 1;
      currentShape[0][2] = 1;
      currentShape[1][1] = 1;
      currentShape[1][2] = 1;
      break;

    case 4:
      /*{0, 1, 1, 0},
      {1, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}*/
      currentShape[0][1] = 1;
      currentShape[0][2] = 1;
      currentShape[1][0] = 1;
      currentShape[1][1] = 1;
      break;

    case 5:
      /*{1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}*/
      currentShape[0][0] = 1;
      currentShape[0][1] = 1;
      currentShape[1][1] = 1;
      currentShape[1][2] = 1;
      break;

    case 6:
      /*{1, 1, 1, 0},
      {0, 1, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0}*/
      currentShape[0][0] = 1;
      currentShape[0][1] = 1;
      currentShape[0][2] = 1;
      currentShape[1][1] = 1;
      break;
      // Füge hier die Definitionen für die anderen Formen hinzu
  }
}

void setLeds(bool field[numRows][numCols]) {
  int addr = 0;
  int k = 0;
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (j > 7) {
        k = j - 8;
        addr = 1;
      } else {
        k = j;
        addr = 0;
      }
      lc.setLed(addr, i, k, field[i][j]);
    }
  }
}


void loop() {

  field[0][0] = true;  //first led 1st matrix
  field[0][8] = true;  //first led 2nd matrix
  setLeds(field);
}