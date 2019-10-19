#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>   // Comes with Arduino IDE

RF24 myRadio (8,7); // "myRadio" is the identifier you will use in following methods
/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node", "2Node", "3Node"}; // Create address for 1 pipe.
volatile int  dataRx1;  // Data that will be received from the transmitter
volatile int  dataRx2;
volatile int  dataRx3;
volatile int relay1 = 2;
volatile int relay2 = 3;
volatile int relay3 = 4;
void setup()   /****** SETUP: RUNS ONCE ******/
{
  // Use the serial Monitor (Symbol on far right). Set speed to 115200 (Bottom Right)
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("Receiving Tank data"));
  
  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  myRadio.setPALevel(RF24_PA_MAX);

  myRadio.openReadingPipe(1, addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  myRadio.openReadingPipe(2, addresses[1]); // Use the first entry in array 'addresses' (Only 1 right now)
  myRadio.openReadingPipe(3, addresses[2]);

  myRadio.startListening();

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  byte pipenum = 0;
  if ( myRadio.available(&pipenum)) // Check for incoming data from transmitter
  {
    switch(pipenum)
    {
      case 1:
      myRadio.read( &dataRx1, sizeof(dataRx1) ); // Get the data payload (You must have defined that already!)
      Serial.print("From TX :");
      Serial.println(pipenum);
      Serial.print("Data received from TX1= ");
      Serial.println(dataRx1);
      if(dataRx1 > 300 && dataRx1 < 600)
     {
      digitalWrite(relay1,HIGH);
     }
    else
     {
      digitalWrite(relay1,LOW);
     }
      break;
      
      case 2:
      myRadio.read( &dataRx2, sizeof(dataRx2) ); // Get the data payload (You must have defined that already!)
      Serial.print("From TX :");
      Serial.println(pipenum);
      Serial.print("Data received from TX2= ");
      Serial.println(dataRx2);
     if(dataRx2 > 300 && dataRx2 < 600)
     {
      digitalWrite(relay2,HIGH);
     }
    else
     {
      digitalWrite(relay2,LOW);
     }
      break;

      case 3:
      myRadio.read(&dataRx3, sizeof(dataRx3));
      Serial.print("From TX:");
      Serial.println(pipenum);
      Serial.print("Data received from TX3= ");
      Serial.println(dataRx3);
      if(dataRx3 > 300 && dataRx3 < 600)
      {
        digitalWrite(relay3,HIGH);
      }
      else
      {
        digitalWrite(relay3,LOW);
      }
      break;
    }// switch
  }//if available
}// main loop()
