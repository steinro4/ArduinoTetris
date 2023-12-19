#include "Hardware.h"

/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc = LedControl(12, 11, 10, 2);

void hardwareInit() {
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  // Set brightness to a low value
  lc.setIntensity(0, 1);
  lc.setIntensity(1, 1);
  // Clear the display
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

void setLeds(bool field[8][16]) {
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
      lc.setLed(addr, i, k, field[i][j]);
    }
  }
}
