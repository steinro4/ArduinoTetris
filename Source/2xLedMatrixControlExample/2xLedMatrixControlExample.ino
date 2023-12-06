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

bool field[7][15] = {};

byte high = B11111111;
byte low = B00000000;
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


void setRowHigh(int addr, int row) {
  lc.setRow(addr, row, high);
}

void setRowLow(int addr, int row) {
  lc.setRow(addr, row, low);
}

void loop() {
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
}