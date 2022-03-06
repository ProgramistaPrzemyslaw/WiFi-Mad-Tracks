#include "TXcontrol.h"

//Sender
//uint8_t broadcast_Addr[]={0xAC,0x67,0xB2,0x2C,0xC4,0x78};
////uint8_t broadcast_Addr[]={0x08,0x3A,0xF2,0x6E,0x66,0x94}; //esp cam 2
//uint8_t broadcast_Addr[]={0x9C,0x9C,0x1F,0xE9,0x04,0xF0};//ESP cam 1
uint8_t broadcast_Addr[]={0x00,0x00,0x00,0x00,0x00,0x69};//test
int dupa = 0;

const uint8_t Y_Input_Pin = 34;
const uint8_t X_Input_Pin = 33;
const uint8_t macAddr_pin1 = 18;
const uint8_t macAddr_pin2 = 19;

bool dataTransfered = false;

msg sendData;

joystick y_joystick;
joystick x_joystick;


void OnDataSend(const uint8_t *mac_addr,esp_now_send_status_t status){
    Serial.print("\r\n Last Packet Send Status:\t");
    Serial.println(status==ESP_NOW_SEND_SUCCESS ? "SUCCES" : "FAIL");
}

void setup(){
    pinMode(macAddr_pin1,INPUT_PULLUP);
    pinMode(macAddr_pin2,INPUT_PULLUP);

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
    init_joystick(&x_joystick,X_Input_Pin);
    init_joystick(&y_joystick,Y_Input_Pin);
    zero_joysticks(&y_joystick, &x_joystick);


    broadcast_Addr[4] = (uint8_t)digitalRead(macAddr_pin1);
    broadcast_Addr[5] = (uint8_t)digitalRead(macAddr_pin2);

    Serial.printf("y:%d | x:%d", y_joystick.zero, x_joystick.zero);
}

void loop(){


if(millis()%500==0 && dataTransfered==false){

    dupa=0;
    Serial.println("Sending data...\n");
    get_joysticks_data(&sendData, &y_joystick, &x_joystick);
    Serial.println(sendData.adc_x_data);
    Serial.println(sendData.direction_x);
    Serial.println(sendData.direction_y);
    if(esp_now_send(broadcast_Addr,(uint8_t*)&sendData, sizeof(sendData))==ESP_OK){
        Serial.println("Data was send\n");
    }else{
        Serial.println("Error sending data\n");
    }
    dataTransfered = true;
}else if(millis()%500!=0 && dataTransfered==true){
    dataTransfered = false;
}

}
