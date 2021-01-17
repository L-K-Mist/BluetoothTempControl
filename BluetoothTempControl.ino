#include <SoftwareSerial.h>

#include "thermistor.h"
// Analog pin used to read the NTC
#define NTC_PIN A0

#include "TempSensor.h"
#include "Heater.h"

TempSensor tempSensor(NTC_PIN);
Heater heater(&tempSensor);

// Global temperature reading
float temp;

SoftwareSerial BluetoothDevice(3,4);

String inString = "";         // incoming serial byte
String str_ii = "";

void setup() {
  heater.setup();

  Serial.begin(115200);
  BluetoothDevice.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(100);
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  // temp = heater.getTempC();

  // if we get a valid byte, read analog ins:
  // if(BluetoothDevice.available() > 0){
    while (BluetoothDevice.available() > 0) {
        char endMarker = '\n';
        char s = BluetoothDevice.read();
        inString += s;
        // Serial.print(s);
        delay(100);
      // getString();
    }
     Serial.print("We got a string: ");
     Serial.println(inString);
     executeIncomingCommand(inString);

  // }
  delay(100);
}
// TODO Research async-await like functionality for c++ arduino.
void establishContact() {
  while (BluetoothDevice.available() <= 0) {
    BluetoothDevice.println("A");   // send an initial string
    delay(600);
  }
}

void executeIncomingCommand(String command) {
  Serial.print("Got command: ");
  Serial.println(command);
  if(command == "Beautiful\n"){
    Serial.println("Yip I know it's Beautiful");
  }
inString = "";
}


