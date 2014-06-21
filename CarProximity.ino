/**********************************
Car Proximity v2
by Bithead942

Arduino Pins
2 - Xbee TX
3 - Xbee RX
10 - Piezoelectric buzzer
13 - LED

Requires:
Arduino Fio
1 Xbee Pro XCS
1 Piezoelectric Buzzer
1 LED


**********************************/

//#define DEBUG;
#include <SoftwareSerial.h>;
#include "pitches.h"

int pLED = 13;
int pBuzzer = 10;
int inBytes, i;
// SoftSerial RX: connect Arduino digitial 2 to the TX of of usb-serial device.  
uint8_t ssRX = 0;
// SoftSerial TX: connect Arduino digital 3 to RX of usb-serial device
uint8_t ssTX = 1;

SoftwareSerial xbee(ssRX, ssTX);

void setup() {
  pinMode(pLED, OUTPUT);
  pinMode(pBuzzer, OUTPUT);
    
  #ifdef DEBUG
      Serial.begin(9600);
  #endif

  // start XBee communication
  xbee.begin(9600);
}

void loop() {   
   #ifdef DEBUG
      Serial.print("Checking --> ");
   #endif
   xbee.listen();
   inBytes = xbee.available();
   if (inBytes > 0) {
       for (i=0; i<=(inBytes - 1); i++)
          {
          xbee.print(xbee.read());
          }
       digitalWrite(pLED, HIGH);
       MakeSound();
       #ifdef DEBUG
          Serial.println("Received Packet");
       #endif
       
   }
   else {
       digitalWrite(pLED, HIGH);
       delay(50);
       digitalWrite(pLED, LOW);
       #ifdef DEBUG
          Serial.println("No Packet");
       #endif
       delay(1000);
   }
   //delay(1000);
}

void MakeSound() {
   tone(pBuzzer, NOTE_C6);
   delay(250);
   noTone(pBuzzer);
   tone(pBuzzer, NOTE_E6);
   delay(250);
   noTone(pBuzzer);
   tone(pBuzzer, NOTE_G6);
   delay(250);
   noTone(pBuzzer);
   tone(pBuzzer, NOTE_C7);
   delay(250);
   noTone(pBuzzer);
}
