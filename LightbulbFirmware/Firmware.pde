/*
Adapted for use as system firmware for RFID-based computing with the project Lightbulb by Peter Hajas (www.peterhajas.com) for RCOS 2009.
 
 http://rcos.cs.rpi.edu/
 
Lightbulb Team:
 Peter Hajas
 Aileen Sheedy
 Michael O'Keefe
 
Licensed under the BSD License.

This code should go with the RFID_Daemon and corresponding software. Please check the RCOS site listed above for this software.

Originally written for Arduino Playground. The mention of the modifier of the code has been left below.

Thanks to Sean O'Sullivan for the sponsorship. 

*/
// Modified by Worapoht K.
#include <SoftwareSerial.h>

int  val = 0; 
char code[10]; 
int bytesread = 0; 

int speakerPin = 6;

#define rxPin 8
#define txPin 9
// RFID reader SOUT pin connected to Serial RX pin at 2400bps to pin8

void setup()
{ 
  Serial.begin(9600);  // Hardware serial for Monitor 9600bps

  pinMode(2,OUTPUT);       // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  pinMode(speakerPin, OUTPUT); //Set the speaker pin to be output, so we can play some tones when the tag is read
  digitalWrite(2, LOW);    // Activate the RFID reader 
}


void loop()
{ 
  SoftwareSerial RFID = SoftwareSerial(rxPin,txPin); 
  RFID.begin(2400);

  if((val = RFID.read()) == 10)
  {   // check for header 
    bytesread = 0; 
    while(bytesread<10)
    {  // read 10 digit code 
      val = RFID.read(); 
      if((val == 10)||(val == 13))
      {  // if header or stop bytes before the 10 digit reading 
        break;                       // stop reading 
      } 
      code[bytesread] = val;         // add the digit           
      bytesread++;                   // ready to read next digit  
    } 

    if(bytesread == 10)
    {  // if 10 digit read is complete 
      Serial.println(code);            // print the TAG code 
      /*for(int i = 0; i < 60; i++)
      {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(1500);
      }
      delay(100);
      for(int i = 0; i < 1600; i++)
      {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(30);
      }
      */
      wave();
    }
    bytesread = 0; 
    delay(1500);                       // wait for a second
  } 
} 

void wave()
{
  for(int i = 0; i < 1000; i+=5)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(i);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(i);
    delay(1);
  }
}
