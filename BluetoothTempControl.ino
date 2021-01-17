/*
  Serial Call and Response in ASCII
  Language: Wiring/Arduino

  This program sends an ASCII A (byte of value 65) on startup and repeats that
  until it gets some data in. Then it waits for a byte in the serial port, and
  sends three ASCII-encoded, comma-separated sensor values, truncated by a
  linefeed and carriage return, whenever it gets a byte in.

  The circuit:
  - potentiometers attached to analog inputs 0 and 1
  - pushbutton attached to digital I/O 2

  created 26 Sep 2005
  by Tom Igoe
  modified 24 Apr 2012
  by Tom Igoe and Scott Fitzgerald
  Thanks to Greg Shakar and Scott Fitzgerald for the improvements

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialCallResponseASCII
*/

#include <SoftwareSerial.h>

SoftwareSerial BluetoothDevice(3,4);

String inString = "";         // incoming serial byte
String str_ii = "";

void setup() {
  Serial.begin(115200);
  BluetoothDevice.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(100);
  // while (!BluetoothDevice) {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }

  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  // if we get a valid byte, read analog ins:
  if(BluetoothDevice.available() > 0){
    while (BluetoothDevice.available() > 0) {
        char s = BluetoothDevice.read();
        inString += s;
        Serial.print(s);
        delay(100);
      // getString();
    }
     Serial.print("We got a string: ");
     Serial.println(inString);
  }
  delay(100);
}
// TODO Research async-await like functionality for c++ arduino.
void establishContact() {
  while (BluetoothDevice.available() <= 0) {
    BluetoothDevice.println("A");   // send an initial string
    delay(600);
  }
}


