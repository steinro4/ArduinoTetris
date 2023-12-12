
//load libraries
#include "LedControl.h"
#include "binary.h"
#include "Keypad.h"
#include "LiquidCrystal.h"

/*
----------
DISPLAY
----------
*/
int level = 1;
int points = 0;

/*
RS connected to 12
E connected to 11
D4 connected to 2 
D5 connected to 3
D6 connected to 4
D7 connected to 5
*/
LiquidCrystal lcd(7, 6, 2, 3, 4, 5);

const int keypadRows = 4;
const int keypadCols = 4;

/*
----------
KEYPAD
----------
*/
//init keypad
char keys[keypadRows][keypadCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// pins for rows/cols on the Arduino
byte rowPins[keypadRows] = {53, 51, 49, 47}; 
byte colPins[keypadCols] = {45, 43, 41, 39};

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


/*
----------
FIELD
----------
*/
bool field[numRows][numCols] = {false};

/*
byte high = B11111111;
byte low = B00000000;
int i = 0;
int j = 0;
*/

int ledRow = 0;
int ledCol = 0;

/*
----------
SETUP
----------
*/
void setup() {
/*  
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  // Set brightness to a low value
  lc.setIntensity(0, 1);
  lc.setIntensity(1, 1);
  // Clear the display
  lc.clearDisplay(0);
  lc.clearDisplay(1);
*/
    // Initialisiere das LCD mit 16x2 Zeichen
  lcd.begin(16, 2);

}

/*
----------
LOOP
----------
*/
void loop() {

  // Example for Display update add points and level after 2 seconds.
  level++;
  points += 10;

  // update the display
  updateDisplay();

  delay(2000);
  // clear the display for the next update
  lcd.clear();



  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      resetLED();
    } else {
      moveLED(key);
    }
  }
}

/*
----------
MOVE LED
----------
*/  
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



/*
----------
UPDATE LED
----------
*/
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


/*
----------
UpdateDisplay
----------
*/
void updateDisplay() {
  // Setze den Cursor auf die erste Zeile und schreibe das Level
  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(level);

  // Setze den Cursor auf die zweite Zeile und schreibe die Punkte
  lcd.setCursor(0, 1);
  lcd.print("Points: ");
  lcd.print(points);
}

