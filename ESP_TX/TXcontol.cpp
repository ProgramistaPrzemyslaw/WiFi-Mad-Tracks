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

void get_joysticks_data(msg *sendData,joystick *joystick_y, joystick *joystick_x){
    int data_y=analogRead(joystick_y->inputPin)-joystick_y->zero;
    int data_x=analogRead(joystick_x->inputPin)-joystick_x->zero;
    if(abs(data_y)<100){
        sendData->adc_y_data = 0;
    }else if(data_y>0){         //forward
        sendData->direction_y=1;
        sendData->adc_y_data=data_y/11;//left room for bonuses
    }else if(data_y<0){         //backward
        sendData->direction_y=0;
        sendData->adc_y_data=abs(data_y)/20;
    }

    if(abs(data_x)<100){
        sendData->adc_x_data = 0;
    }else if(data_x>0){         //forward
        sendData->direction_x=1;
        sendData->adc_x_data=data_x/10;//left room for bonuses
    }else if(data_x<0){         //backward
        sendData->direction_x=0;
        sendData->adc_x_data=abs(data_x)/10;
    }
    
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

    if(abs(data_x)<100){
        sendData->adc_x_data = 0;
    }else if(data_x>0){         //forward
        sendData->direction_x=1;
        sendData->adc_x_data=data_x/10;//left room for bonuses
    }else if(data_x<0){         //backward
        sendData->direction_x=0;
        sendData->adc_x_data=abs(data_x)/10;
    }
}
*/