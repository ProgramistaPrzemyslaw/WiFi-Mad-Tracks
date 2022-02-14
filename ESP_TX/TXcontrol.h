#pragma once
#include <esp_now.h>
#include <WiFi.h>
#include <math.h>
//esp_err_t result;
typedef struct msg{
int direction_y;
int direction_x;
uint8_t adc_y_data;
uint8_t adc_x_data;
}msg;


typedef struct joystick{
int inputPin;
int zero;
int max_ADC;
int min_ADC;
}joystick;


void init_joystick(joystick *joystick, int inputPin);
void zero_joysticks(joystick *joystick_y, joystick *joystick_x);
void get_joysticks_data(msg *sendData,joystick *joystick_y, joystick *joystick_x);
