#ifndef HARDWARE_H
#define HARDWARE_H
#include <Arduino.h>
#include "LedControl.h"
#include "binary.h"
#include "LiquidCrystal.h"
#include "Joystick.h"

void hardwareInit();
void setLeds(bool field[8][16]);

#endif