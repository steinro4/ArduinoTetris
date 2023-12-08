/*
 Created by Rui Santos
 
 All the resources for this project:
 http://randomnerdtutorials.com/
*/
//load libraries
#include "LedControl.h"
#include "binary.h"
#include "Keypad.h"


//Keypad


const int keypadRows = 4;
const int keypadCols = 4;
//init keypad
char keys[keypadRows][keypadCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// pins for rows/cols on the Arduino
byte rowPins[keypadRows] = {9, 8, 7, 6}; 
byte colPins[keypadCols] = {5, 4, 3, 2};

// Assign hardware buttons
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, keypadRows, keypadCols);

LedControl lc = LedControl(12, 11, 10, 2);

/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/


// delay time
unsigned long delaytime = 1000;

const int numRows = 8;
const int numCols = 8;

bool field[numRows][numCols] = {false};

/*
byte high = B11111111;
byte low = B00000000;
int i = 0;
int j = 0;
*/

int ledRow = 0;
int ledCol = 0;

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


void loop() {

  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      resetLED();
    } else {
      moveLED(key);
    }
  }
}

  
//move the LED by pressing buttons (2:up, 4:left, 6:right, 8:down)
void moveLED(char direction) {
  switch (direction) {
    case '2': // Unten
      if (ledRow < numRows - 1) {
        ledRow++;
      }
      break;

    case '8': // Oben
      if (ledRow > 0) {
        ledRow--;
      }
      break;

    case '4': // Links
      if (ledCol > 0) {
        ledCol--;
      }
      break;

    case '6': // Rechts
      if (ledCol < numCols - 1) {
        ledCol++;
      }
      break;

  }
  updateLED();
}

//reset option (button #)
void resetLED() {
  ledRow = 0;
  ledCol = 0;
  updateLED();
}

//update Led Position
void updateLED() {
  // Schalte alle LEDs aus
  lc.clearDisplay(0);
  lc.clearDisplay(1);

  // Schalte die LED an der neuen Position ein
  lc.setLed(0, ledRow, ledCol, true);
  lc.setLed(1, ledRow, ledCol, true);


  // Warte kurz, um die Bewegung sichtbar zu machen
  delay(500);

  // Schalte alle LEDs aus
  lc.clearDisplay(0);
  lc.clearDisplay(1);

}