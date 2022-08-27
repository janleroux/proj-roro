/*
 Name:      Roro1_RFPingPong.ino
 Created:   2020/08/22
 Description: 
 - Test Radio. 
 - Wait 10s.
 - Sends a 0 every 10s to the serial port and over the RFM95.
 - If a value is received, send it to the serial port, increment it
   and send the incremented value back to the serial port and over the RFM95.
 - Which one receives the first value will not try to send a value anymore
 - Flash BLUE on Tx, RED on Rx.
 - System need to be restarted if any message does not get through. How many ping-pongs goes through.

 LoraWAN channels in NZ:
 Channel 0: 915 000 000
 Channel 1: 915 150 000
 Channel 2: 915 300 000
 Channel 3: 915 450 000
 Channel 4: 915 600 000
 Channel 5: 915 750 000
 Channel 6: 915 900 000
 Channel 7: 916 050 000
 Channel 8: 916 200 000
 Channel 9: 916 350 000
*/

#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>
#include <NeoPixelSegmentBus.h>
#include <LoRa.h>
#include <SPI.h>
#define colorSaturation 128

const uint8_t PixelPin = 2;
const uint16_t PixelCount = 1; 
RgbColor red(255,0,0);
RgbColor blue(0,0,255);
RgbColor black(0);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
int flashDelay = 1000;

//GLOBAL VARIABLES
const int csPin = 5;          // LoRa radio chip select
const int resetPin = 25;        // LoRa radio reset
const int irqPin = 32;          // change for your board; must be a hardware interrupt pin
const long freq = 915E6;
const int txSpeed = 7; //SF
long chan = 0;
int txCntr = 0;
String txMsg = "";
static unsigned long previousMillis = millis(); //starting timestamp
unsigned long currentMillis;
bool initialSend = true;
int initialWaitTime = 10000; //wait 10s
bool myTurnToTx = false; //message was received, my-turn-to-Tx flag

void setup() {
  //setup serial
  Serial.begin(115200); 
  Serial.println("RORO1 Starting...");

  //setup neopixels
  strip.Begin();
  strip.Show();

  //Get the frequency r
  chan = (chan * 150000) + freq;

  //setup the LoRa radio
  LoRa.setPins(csPin, resetPin, irqPin); // set CS, reset, IRQ pin 
  if (!LoRa.begin(chan)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(txSpeed);
}

void loop() {
  previousMillis = millis(); //start timestamp
  
  while(initialSend){ //wait for ack to arrive before resending ack
    currentMillis = millis(); //current timestamp
      if(currentMillis - previousMillis >= initialWaitTime){
        initialSend = false; //break the while loop. Only send once, do not try again
        Tx(); //do a first transmission        
      }
  }  

  if(myTurnToTx){
    Tx(); //it is my-turn-to-Tx flag
  }

  Rx(); //anything in the Rx queue to process?
}

/* ======================================================================
  Tx() builds up the PLINK message and send the message
====================================================================== */
void Tx() {
  strip.SetPixelColor(0, blue);
  strip.Show();

  myTurnToTx = false; //disable the my turn to Tx flag
  
  txMsg = txCntr;

  //send packet
  LoRa.beginPacket();
  LoRa.print(txMsg);
  LoRa.endPacket();

  Serial.print("Tx: ");
  Serial.println(txMsg);

  strip.SetPixelColor(0, black);
  strip.Show();
}

/* ======================================================================
  Rx() builds up the PLINK message and send the message
====================================================================== */
void Rx() {
  String rxMsg = "";
  initialSend = false; //break the while loop. Only send once, do not try again

  // try to parse packet
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    strip.SetPixelColor(0, red);
    strip.Show();
    // read packet
    while (LoRa.available()) {
      rxMsg += (char)LoRa.read();
    }

    txCntr = rxMsg.toInt();
    txCntr++;
    
    // print RSSI of packet
    Serial.print("Rx: ");
    Serial.print(rxMsg);
    Serial.print(", "); 
    Serial.println(LoRa.packetRssi());

    myTurnToTx = true; //enable the my-turn-to-Tx flag
 
    strip.SetPixelColor(0, black);
    strip.Show();

    delay(5000);
  }
}
