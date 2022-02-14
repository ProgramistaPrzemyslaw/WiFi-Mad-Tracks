#include "control.h"


extern struct msg rxData;
extern const uint8_t Enable1 = 13;
extern const uint8_t Enable2 = 15;


void LED_LIGHT(uint8_t PWM_Channel){
    ledcWrite(PWM_Channel,rxData.adc_y_data);
}


void motorControl(msg *Data, uint8_t PWM_Channel){
    bool direction = false;
    ledcWrite(PWM_Channel,Data->adc_y_data);
    if(Data->direction_y==0){
        digitalWrite(Enable1, direction);
        digitalWrite(Enable2, !direction);
    }else{
        digitalWrite(Enable1, !direction);
        digitalWrite(Enable2, direction);
    }
}

void servoControl(msg *Data, uint8_t PWM_Channel){

    int rotation = 0; 
    
   // Serial.println("__________________");
   // Serial.println(Data->direction_x);
    if(Data->adc_x_data==0){

    rotation = 103;    //90 deg when you have 12 bit duty cycle resolution

    }else if(Data->direction_x==0){
        rotation = -90;
    //rotation = rotation - Data->adc_x_data;
    //Serial.println(rotation);
    /*
    if(rotation<0){
    rotation=0;
    }*/

    }else if(Data->direction_x==1){

    rotation = rotation + Data->adc_x_data;
/*
    if(rotation>205){
    rotation=205;
    }*/
    rotation = 295;
    }
    //Serial.println(rotation);
    rotation = 205 + rotation; // to achieve pulse with width of 1-2ms
    //Serial.println(Data->adc_x_data); 
    ledcWrite(PWM_Channel, rotation);

}
