#include "dweetESP8266.h"
#define THIG_NAME  "keramikk-ovn"  // Put here your thing name
#define WIFISSID "ssid"
#define PASSWORD "password"

#include "max6675.h"

int thermoDO = 4;
int thermoCS = 0;
int thermoCLK = 2;

dweet client;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup(){
    Serial.begin(115200);
    Serial.print("Init..");
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
    pinMode(3, OUTPUT);
    pinMode(1, OUTPUT);
    Serial.print("OK\n");
}
void loop(){
    //String val = String(analogRead(A0));
    //client.add(key, val); // specifies the args of type "String"
    Serial.print("Asking for temperature..");
    float tempMeasurement = thermocouple.readCelsius();
    String temp = String(tempMeasurement);
    Serial.print("\nSending with Dweet:");
    client.add("test", temp);
    client.sendAll(THIG_NAME);
    Serial.print("\nOK");
}
