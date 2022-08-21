/*
 Name:      Roro1_NeoPixel-flash.ino
 Created:   2020/08/20
 Description: 
 - Basic NeoPixel test
 - Basic Serial test
*/

#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>
#include <NeoPixelSegmentBus.h>
#define colorSaturation 128

const uint8_t PixelPin = 2;
const uint16_t PixelCount = 1; 
RgbColor white(colorSaturation);
RgbColor red(255,0,0);
RgbColor green(0,255,0);
RgbColor blue(0,0,255);
RgbColor yellow(255,255,0);
RgbColor orange(255,128,0);
RgbColor grey(20,20,20);
RgbColor black(0);
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
int flashDelay = 1000;


void setup() {
  //setup serial
  Serial.begin(115200); 
  Serial.println("RORO1 Starting...");

  //setup neopixels
  strip.Begin();
  strip.Show();
}

void loop() {
  delay(flashDelay);
  strip.SetPixelColor(0, red);
  strip.Show();
  Serial.println("Red");

  delay(flashDelay);
  strip.SetPixelColor(0, orange);
  strip.Show();
  Serial.println("Orange");

  delay(flashDelay);
  strip.SetPixelColor(0, yellow);
  strip.Show();
  Serial.println("Yellow");

  delay(flashDelay);
  strip.SetPixelColor(0, green);
  strip.Show();
  Serial.println("Green");
  
  delay(flashDelay);
  strip.SetPixelColor(0, blue);
  strip.Show();
  Serial.println("Blue");

  delay(flashDelay);
  strip.SetPixelColor(0, white);
  strip.Show();
  Serial.println("White");

  delay(flashDelay);
  strip.SetPixelColor(0, grey);
  strip.Show();
  Serial.println("Grey");

  delay(flashDelay);
  strip.SetPixelColor(0, black);
  strip.Show();
  Serial.println("Black");
}
