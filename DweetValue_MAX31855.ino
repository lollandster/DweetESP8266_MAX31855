#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "dweetESP8266.h"
#define THIG_NAME  "keramikk-ovn"  // Put here your thing name
#define WIFISSID "---"
#define PASSWORD "---"

// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   4
#define MAXCS   0
#define MAXCLK  2

// initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// Example creating a thermocouple instance with hardware SPI
// on a given CS pin.
//#define MAXCS   10
//Adafruit_MAX31855 thermocouple(MAXCS);

void setup() {
  Serial.begin(115200);
 
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  client.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
  // basic readout test, just print the current temp
   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.print("C = "); 
     Serial.println(c);
   }
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFarenheit());
   Serial.print("Asking for temperature..");
   double tempMeasurement = thermocouple.readCelsius();
   String temp = String(tempMeasurement);
   Serial.print("\nSending with Dweet:");
   client.add("test", temp);
   client.sendAll(THIG_NAME);
   Serial.print("\nOK");
   delay(1000);
}
