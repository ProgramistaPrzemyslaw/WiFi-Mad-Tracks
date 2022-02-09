#include <esp_now.h>
#include <WiFi.h>

//Sender
//uint8_t broadcast_Addr[]={0xAC,0x67,0xB2,0x2C,0xC4,0x78};
////uint8_t broadcast_Addr[]={0x08,0x3A,0xF2,0x6E,0x66,0x94}; //esp cam 2
//uint8_t broadcast_Addr[]={0x9C,0x9C,0x1F,0xE9,0x04,0xF0};//ESP cam 1
uint8_t broadcast_Addr[]={0x00,0x00,0x00,0x00,0x00,0x00};//test
int dupa = 0;
esp_err_t result;
typedef struct msg{
int a;
int time;
int adc_data;
}msg;

msg sendData;


void OnDataSend(const uint8_t *mac_addr,esp_now_send_status_t status){
    Serial.print("\r\n Last Packet Send Status:\t");
    Serial.println(status==ESP_NOW_SEND_SUCCESS ? "SUCCES" : "FAIL");
}

void setup(){
    pinMode(18,INPUT_PULLUP);
    pinMode(19,INPUT_PULLUP);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if(esp_now_init()!=ESP_OK){
        Serial.println("Error initialising\n");
        return;
    }
    
    esp_now_register_send_cb(OnDataSend);
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr,broadcast_Addr,6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if(esp_now_add_peer(&peerInfo)!=ESP_OK){
        Serial.println("peer error\n");
        return;
    }
    Serial.println("piwko\n");
}

void loop(){


if(millis()%200){
    dupa=0;
    Serial.println("Sending data...\n");
    sendData.adc_data = analogRead(34);
    Serial.println(sendData.adc_data);
    sendData.a = digitalRead(19);
    sendData.time = random(10,200);
    if(esp_now_send(broadcast_Addr,(uint8_t*)&sendData, sizeof(sendData))==ESP_OK){
        Serial.println("Data was send\n");
    }else{
        Serial.println("Error sending data\n");
    }

}

}