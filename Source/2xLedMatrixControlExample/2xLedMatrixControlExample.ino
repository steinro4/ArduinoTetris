
//load libraries
#include "LedControl.h"
#include "binary.h"
#include "Keypad.h"
#include "LiquidCrystal.h"
#include "Joystick.h"

/*
----------
DISPLAY init
----------
*/
int level = 1;
int points = 0;
int highscore = 0;
/*
RS connected to 7
E connected to 6
D4 connected to 2 
D5 connected to 3
D6 connected to 4
D7 connected to 5
*/
LiquidCrystal lcd(7, 6, 2, 3, 4, 5);
/*
----------
LED Control Init
----------
*/
/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc = LedControl(12, 11, 10, 2);

// delay time
unsigned long delaytime = 1000;

const int numRows = 8;
const int numCols = 8;


/*
----------
JOYSTICK init
----------
*/
const int xAxis = A1;       // Analog input for the X-Axis
const int yAxis = A2;       // Analog input for the Y-Axis
const int buttonPin = 8;    //Digital input for the Joystick
const int threshold = 100;  // Threshold for the movement in a direction, can be modified
/*
----------
FIELD init
----------
*/
bool field[numRows][numCols] = {false};


int ledRow = 0;
int ledCol = 0;

/*
----------
SETUP
----------
*/
void setup() {

  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // Setze den Button-Pin als Eingang mit Pull-Up-Widerstand

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

  if (level < 10 and level > 0){ // condition for the Game -> has to be changed.
  gameRunning();
  }
  
  else if(level <= 0){ // condition to win the Game
    lcd.clear();
    gameWon();
  }

  else { //condition for GAMEOVER
    lcd.clear();
    gameOver();
  }

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
GAMERUNNING
----------
*/
void gameRunning(){
   // Joystick "left"

  //read the value of the X- and Y-Axis
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);
  int buttonState = digitalRead(buttonPin);

    if (xValue < (512 - threshold)) {
      level --;
    // Joystick "right"
      } else if (xValue > (512 + threshold)) {
        level ++;
      }
    // Joystick "up"
    if (yValue < (512 - threshold)) {
      points ++;
    // Joystick "down"
      } else if (yValue > (512 + threshold)) {
        points --;
      }
    // Joystick tilt
    if (buttonState == LOW){
      highscore ++;
      }
      
    // update the LCD display
    updateDisplay();
    delay(100);
    // clear the LCD display for the next update
    lcd.clear();

}
/*
----------
GAMEOVER
----------
*/
void gameOver(){

  lcd.setCursor(6, 0);
  lcd.print("GAME");
  lcd.setCursor(6, 1);
  lcd.print("OVER");
}
/*
----------
GAMEWON
----------
*/
void gameWon(){

  lcd.setCursor(6, 0);
  lcd.print("GAME");
  lcd.setCursor(6, 1);
  lcd.print("WON");
}
/*
----------
UpdateDisplay
----------
*/
void updateDisplay() {
  // place the cursor on the first row and write the level
  lcd.setCursor(0, 0);
  lcd.print("LVL:");
  lcd.print(level);

  // place the cursor on the second row and write the Points
  lcd.setCursor(0, 1);
  lcd.print("PT:");
  lcd.print(points);


  // place the cursor on the second row, 8th col and write the Highscore
  lcd.setCursor(8, 1);
  lcd.print("HS:");
  lcd.print(highscore);
}


