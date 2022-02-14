#pragma once
#include <esp_now.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <esp_wifi.h>
#include "esp_timer.h"
#include "Arduino.h"


typedef struct msg{
int a;
int adc_y_data;
int adc_x_data;
}msg;



void LED_LIGHT(uint8_t PWM_Channel);
void zero_joystick();
