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
