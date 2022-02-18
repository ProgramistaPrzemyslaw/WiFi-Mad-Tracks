#include "control.h"


extern struct msg rxData;
extern const uint8_t Enable1 = 13;
extern const uint8_t Enable2 = 15;
extern const uint8_t TEST_PIN = 12;


void LED_LIGHT(uint8_t PWM_Channel){
    ledcWrite(PWM_Channel,rxData.adc_y_data);
}


void motorControl(msg *Data, uint8_t PWM_Channel){
    bool direction = false;
    ledcWrite(PWM_Channel,Data->adc_y_data);
    Serial.println(Data->adc_y_data);
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
    if(Data->adc_x_data==0){

    rotation = 103;    //90 deg when you have 12 bit duty cycle resolution

    }else if(Data->direction_x==0){

    rotation = -90;

    }else if(Data->direction_x==1){

    rotation = 295;

    }
    //Serial.println(rotation);
    rotation = 205 + rotation; // to achieve pulse with width of 1-2ms
    //Serial.println(Data->adc_x_data); 
    ledcWrite(PWM_Channel, rotation);

}


void turnControl(msg *Data, uint8_t PWM_Channel){
    bool direction = false;
    if(Data->adc_x_data!=0){

        digitalWrite(TEST_PIN,HIGH);
    if(Data->direction_x==0){
        digitalWrite(Enable1, direction);
        digitalWrite(Enable2, !direction);
    }else{
        digitalWrite(Enable1, !direction);
        digitalWrite(Enable2, direction);
    }

    }else{
        digitalWrite(TEST_PIN,LOW);
    }
}
