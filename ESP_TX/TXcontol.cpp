#include "TXcontrol.h"




void init_joystick(joystick *joystick, int inputPin){
    joystick->inputPin = inputPin;
    joystick->max_ADC = 4095;
    joystick->min_ADC = 0;
}

void zero_joysticks(joystick *joystick_y, joystick *joystick_x){
    int cal_val_x = 0;
    int cal_val_y = 0;
    int it = 15;
    for(int i=0;i<it;i++){
        cal_val_x += analogRead(joystick_x->inputPin);
        cal_val_y += analogRead(joystick_y->inputPin);
        delay(100);
    }

    joystick_x->zero = cal_val_x/it;
    joystick_y->zero = cal_val_y/it;
}


/*
void zero_joysticks(joystick *joystick_y, joystick *joystick_x){
    int cal_val_x = 0;
    int cal_val_y = 0;
    int it = 15;
    for(int i=0;i<it;i++){
        cal_val_x += analogRead(joystick_x->inputPin);
        cal_val_y += analogRead(joystick_y->inputPin);
        delay(100);
    }

    joystick_x->zero = cal_val_x/it;
    joystick_y->zero = cal_val_y/it;
}
*/