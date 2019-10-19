#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+

const int pinCE = 7; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 8; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
RF24 wirelessSPI(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
const uint64_t wAddress[] = {0xB00B1E50D2LL ,0xB00B1E50C3LL} ;              // Pipe to write or transmit on
//const uint64_t rAddress = 0xB00B1E50B1LL;  //pipe to recive data on
int moisture = 1;
int datatxed;
void setup()  
{
  datatxed = 100;
  Serial.begin(57600);   //start serial to communicate process
  wirelessSPI.begin();            //Start the nRF24 module
  wirelessSPI.setChannel(108);  // Above most Wifi Channels  
  wirelessSPI.setPALevel(RF24_PA_MAX);
  wirelessSPI.openWritingPipe(wAddress[0]);        //open writing or transmit pipe
  wirelessSPI.openWritingPipe(wAddress[1]);        //open writing or transmit pipe  
  //wirelessSPI.stopListening(); //go into transmit mode
}


void loop()  
{
 // int val1 = analogRead(moisture);

  wirelessSPI.write(&datatxed, sizeof(datatxed));
  Serial.println(datatxed);
  datatxed = datatxed + 1;
  delay(500);
}

