#include "control.h"


extern struct msg rxData;

void LED_LIGHT(uint8_t PWM_Channel){
    if(rxData.a==0)
    ledcWrite(PWM_Channel,rxData.a);
    else
    ledcWrite(PWM_Channel,rxData.adc_y_data);
}


