#include "TXcontrol.h"





void init_joystick(joystick *joystick, int inputPin){
    joystick->inputPin = inputPin;
    joystick->zero = analogRead(inputPin);
    
}