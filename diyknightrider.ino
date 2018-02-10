#include <Adafruit_NeoPixel.h>

// SETUP YOUR OUTPUT PIN AND NUMBER OF PIXELS
#define PIN 5
#define PixelCount 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PixelCount, PIN, NEO_GRBW + NEO_KHZ800);
int BrightnessArray[]={
  0,0,0,0,0,0,0,0,0
};
void setup() {
  strip.begin();
  clearStrip(); // Initialize all pixels to 'off'
  delay(1000);
}

void loop(){
  for(int x = 0;x<PixelCount;x++){
    for(int i=0;i<PixelCount;i++){
      BrightnessArray[i]=BrightnessArray[i]/1.5;
      if(BrightnessArray[i]<0)BrightnessArray[i]=0;
    }
    BrightnessArray[x]=255;
    for(int n=0;n<PixelCount;n++){
      strip.setPixelColor(n,BrightnessArray[n],0,0,0);
    }
    strip.show();
    delay(100);
  }
  for(int x = PixelCount-1;x>0;x--){
    for(int i=0;i<PixelCount;i++){
      BrightnessArray[i]=BrightnessArray[i]/1.5;
      if(BrightnessArray[i]<0)BrightnessArray[i]=0;
    }
    BrightnessArray[x]=255;
    for(int n=0;n<PixelCount;n++){
      strip.setPixelColor(n,BrightnessArray[n],0,0,0);
    }
    strip.show();
    delay(100);
  }
}







void clearStrip() {
  for( int i = 0; i<PixelCount; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
}

