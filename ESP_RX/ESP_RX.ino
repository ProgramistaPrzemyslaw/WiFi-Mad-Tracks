#include "esp_camera.h"
#include <esp_now.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <esp_wifi.h>
#include "camera.h"

//Sender
uint8_t custom_Addr[]={0x00,0x00,0x00,0x00,0x00,0x00};
const char* ssid = "SSID";
const char* password = "PASSWORD";
//AsyncWebServer server(80);
WiFiServer server(80);

const uint8_t PWM_RES = 12; //should be the same as ADC resolution on transmitting ESP in bits
const uint8_t PWM_Channel = 1;
const double PWM_Freq = 5000;
const uint8_t PWM_Pin = 4;
const uint8_t PWM_Test_Pin = 13;


int dupa = 0;
esp_err_t result;

bool received = false;

typedef struct msg{
int a;
int adc_y_data;
int adc_x_data;
}msg;

msg rxData;

void LED_LIGHT(){
    if(rxData.a==0)
    ledcWrite(PWM_Channel,rxData.a);
    else
    ledcWrite(PWM_Channel,rxData.adc_y_data);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len){
    memcpy(&rxData, incomingData,sizeof(rxData));
    Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(rxData.a);
  Serial.print("Int: ");
  Serial.println(rxData.adc_x_data);
  Serial.print("Int: ");
  Serial.println(rxData.adc_y_data);
  LED_LIGHT();
}

void setup(){
 // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
Serial.begin(115200);
Serial.setDebugOutput(false);
WiFi.mode(WIFI_AP_STA);

esp_wifi_set_mac(WIFI_IF_STA, &custom_Addr[0]);
Serial.println("ESP MAC ADDRESS");
Serial.println(WiFi.macAddress());

camera_config_t config;
startCamera(config);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  startCameraServer();
  
  Serial.println("Server started");
  pinMode(4,OUTPUT);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
  ledcSetup(PWM_Channel, PWM_Freq, PWM_RES);
  ledcAttachPin(PWM_Pin,PWM_Channel);
  ledcAttachPin(PWM_Test_Pin,PWM_Channel);
}


void loop(){
    
}
