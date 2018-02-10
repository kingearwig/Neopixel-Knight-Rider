#include <Adafruit_NeoPixel.h>
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

// SETUP YOUR OUTPUT PIN AND NUMBER OF PIXELS
#define PIN 5
#define PixelCount 9
unsigned long Delay=0;
float Decay=1.5;
#define DimDelay 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PixelCount, PIN, NEO_GRBW + NEO_KHZ800);
Encoder myEnc(0, 2);
#define EncoderButtonPin 4
unsigned long LastEncoderButton=millis();
unsigned long lastTime = millis();
unsigned long lastTimeDim = millis();
int HighPixel=0;
bool Up=1;
int BrightnessArray[PixelCount];
long Delayposition  = -999;
long Decayposition =-999;
bool DelayorDecay=0;
void setup() {
  strip.begin();
  clearStrip(); // Initialize all pixels to 'off'
  delay(1000);
}

void loop(){
  long newPos = myEnc.read();
  if(!digitalRead(EncoderButtonPin) && millis()-LastEncoderButton>5)DelayorDecay=!DelayorDecay;
  if(!DelayorDecay)
  {
    if (newPos != Delayposition)
    {
      Delay=Delay+newPos;
      myEnc.write(0);
    }
  }
  else
  {
    if (newPos != Decayposition)
    {
      Decay=Decay+(.01*newPos);
      myEnc.write(0);
    }
  }
  dimBrightnessArray();
  setHighPixel();
  strip.show();
}


void setHighPixel(){
  if (millis()-lastTime>=Delay){
    lastTime=millis();
    if (HighPixel==PixelCount-1)Up=0;
    if (HighPixel==0)Up=1;
    if (Up)HighPixel++;
    if(!Up)HighPixel--;
  }
}

void dimBrightnessArray(){
  if(millis()-lastTimeDim>DimDelay){
    lastTimeDim=millis();
    for(int i=0;i<PixelCount;i++){
      BrightnessArray[i]=BrightnessArray[i]/Decay;
      if(BrightnessArray[i]<0)BrightnessArray[i]=0;
      }
      BrightnessArray[HighPixel]=255;
      for(int n=0;n<PixelCount;n++){
        strip.setPixelColor(n,BrightnessArray[n],0,0,0);
      }
  }
}



void clearStrip() {
  for( int i = 0; i<PixelCount; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}

