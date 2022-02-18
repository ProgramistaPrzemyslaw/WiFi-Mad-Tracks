
#include "camera.h"
#include "control.h"

//Sender
uint8_t custom_Addr[]={0x00,0x00,0x00,0x00,0x00,0x00};
const char* ssid = "SSID";
const char* password = "PASSWORD";
//AsyncWebServer server(80);

WiFiServer server(80);
httpd_handle_t stream_httpd = NULL;

const uint8_t PWM_RES = 8; //should be the same as ADC resolution on transmitting ESP in bits
const uint8_t Servo_Res = 12;
const uint8_t PWM_Channel = 10;
const uint8_t Servo_Channel = 5;
const double PWM_Freq = 5000;
const double Servo_Freq = 50;
const uint8_t PWM_Pin = 2;
const uint8_t Servo_Pin = 14;
const uint8_t Enable1 = 13;
const uint8_t Enable2 = 15;

const uint8_t Turn_Pin= 12;
const uint8_t Enable1_1 = 13;
const uint8_t Enable2_1 = 15;



int dupa = 0;

//esp_err_t result;

msg rxData;


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len){
    memcpy(&rxData, incomingData,sizeof(rxData));
    Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(rxData.direction_x);
  Serial.print("Int: ");
  Serial.println(rxData.adc_x_data);
  Serial.print("Int: ");
  Serial.println(rxData.adc_y_data);
  //LED_LIGHT(PWM_Channel);
  
}

void setup(){
 // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
 

  Serial.begin(115200);
  Serial.setDebugOutput(false);

  camera_config_t config;

  startCamera(&config);
  
  esp_err_t err = esp_camera_init(&config);
  
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }else{
  Serial.println("Camera init good startCamera");
  }
  WiFi.mode(WIFI_AP_STA);

    esp_wifi_set_mac(WIFI_IF_STA, &custom_Addr[0]);
  Serial.println("ESP MAC ADDRESS");
  Serial.println(WiFi.macAddress());

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  
  
  Serial.println("Server started");

  startCameraServer();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }else{
    Serial.println("Initialized ESP-NOW");
  }

  ledcSetup(PWM_Channel, PWM_Freq, PWM_RES);
  ledcAttachPin(PWM_Pin,PWM_Channel);
  pinMode(Enable1,OUTPUT);
  pinMode(Enable2,OUTPUT);

  ledcSetup(Servo_Channel,Servo_Freq,Servo_Res);
  ledcAttachPin(Servo_Pin, Servo_Channel);



  esp_now_register_recv_cb(OnDataRecv);

  // pinMode(PWM_Pin,OUTPUT);  

  //ledcAttachPin(PWM_Test_Pin,PWM_Channel);
}


void loop(){
  motorControl(&rxData,PWM_Channel);
  servoControl(&rxData,Servo_Channel);
}
