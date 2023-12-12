/*
 Created by Rui Santos
 
 All the resources for this project:
 http://randomnerdtutorials.com/
*/

#include "LedControl.h"
#include "binary.h"

/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc = LedControl(12, 11, 10, 2);

// delay time
unsigned long delaytime = 1000;


const int numRows = 8;
const int numCols = 16;


// create playfield (addr, row, col)
bool field[numRows][numCols] = {{false}};

// init actual shape
int currentShape[4][4] = {{0}};

// init actual row/col
int currentRow = 0;
int currentCol = 0;

// activate/deactivate row LEDs
/*
byte high = B11111111;
byte low = B00000000;
*/

// count variables
int i = 0;
int j = 0;

void setup() {
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  // Set brightness to a low value
  lc.setIntensity(0, 1);
  lc.setIntensity(1, 1);
  // Clear the display
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

/*
void setRowHigh(int addr, int row) {
  lc.setRow(addr, row, high);
}

void setRowLow(int addr, int row) {
  lc.setRow(addr, row, low);
}
*/

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

void loop() {

  lc.setLed(0, i, j, true);  // Turn on LED at position (i, j) on matrix 0
  delay(1000);               // Delay for 1 second
  lc.setLed(0, i, j, false); // Turn off LED at position (i, j) on matrix 0

int randomShape = random(7);
setShape(randomShape);



// single led move row down/ col down
  // Move to the next LED position
  i++;
  if (i >= 8) {
    i = 0;
    j++;
    if (j >= 8) {
      j = 0;
    }
  }




/*

// complete row movement
  setRowHigh(j,i);
  delay(1000);
  setRowLow(j,i);
  i = i + 1;
  if (i >= 8 & j < 1) {
    i = 0;
    j = 1;
  }
  else if (i >= 8 & j > 0){
    i = 0;
    j = 0;
  }
  */
}