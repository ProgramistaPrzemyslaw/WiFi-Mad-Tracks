#include "esp_camera.h"
#include <esp_now.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <esp_wifi.h>
#include "camera.h"

//Sender
uint8_t broadcast_Addr[]={0x9C,0x9C,0x1F,0xE9,0x04,0xF0};
const char* ssid = "SSID";
const char* password = "PASSWORD";
//AsyncWebServer server(80);
WiFiServer server(80);




int dupa = 0;
esp_err_t result;
bool received = false;
typedef struct msg{
int a;
int times;
int adc_data;
}msg;

msg rxData;

void LED_LIGHT(){
    digitalWrite(4,rxData.a);
    delay(rxData.times);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len){
    memcpy(&rxData, incomingData,sizeof(rxData));
    Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(rxData.a);
  Serial.print("Int: ");
  Serial.println(rxData.times);
  Serial.print("Int: ");
  Serial.println(rxData.adc_data);
  received = true;
}

void setup(){
 // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
Serial.begin(115200);
Serial.setDebugOutput(false);
WiFi.mode(WIFI_AP_STA);

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
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

}

void loop(){
    if(received){
    LED_LIGHT();
    received = false;
    }
}
