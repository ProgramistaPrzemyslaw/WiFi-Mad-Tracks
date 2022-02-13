#pragma once
#include <esp_now.h>
#include <WiFi.h>

esp_err_t result;
typedef struct msg{
int a;
int adc_y_data;
int adc_x_data;
}msg;


typedef struct joystick{
int inputPin;
int zero;
int max_ADC;
int min_ADC;
}joystick;


void init_joystick(joystick *joystick);