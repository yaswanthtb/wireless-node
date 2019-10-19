#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 myRadio (8, 7); // "myRadio" is the identifier you will use in following methods(CE,CSN)
/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
volatile int dataTransmitted;  // Data that will be Transmitted from the transmitter
int moisture = 0;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Transmitter1");
  
  myRadio.begin();
  myRadio.setChannel(108);  //Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  myRadio.setPALevel(RF24_PA_MAX); // Max for more power

  myRadio.openWritingPipe(addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  delay(500);
  myRadio.stopListening();
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  dataTransmitted = analogRead(moisture);
  myRadio.write( &dataTransmitted, sizeof(dataTransmitted) ); //  Transmit the data

  Serial.print(F("Tank level = "));
  Serial.println(dataTransmitted);
  delay(1700);
}//--(end main loop )---
