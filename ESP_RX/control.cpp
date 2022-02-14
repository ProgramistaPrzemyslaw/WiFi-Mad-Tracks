#include "control.h"


extern struct msg rxData;



void LED_LIGHT(uint8_t PWM_Channel){
    ledcWrite(PWM_Channel,rxData.adc_y_data);
}

