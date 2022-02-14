#pragma once
#include <esp_now.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <esp_wifi.h>
#include "esp_timer.h"
#include "Arduino.h"


typedef struct msg{
int direction_y;
int direction_x;
uint8_t adc_y_data;
uint8_t adc_x_data;
}msg;



void LED_LIGHT(uint8_t PWM_Channel);
void zero_joystick();
