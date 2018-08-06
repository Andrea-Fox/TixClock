#include <Adafruit_NeoPixel.h>
#include <time.h>
#include <stdlib.h>
#include <Time.h>
#include <Wire.h>
#include <DS3231.h>

#define PIN 5
#define N 50

int  tutti[27] = {0, 23, 24, 2, 3, 4, 19, 20, 21,  26, 27, 28, 6, 7, 16, 17, 30, 31, 9, 10, 11, 12, 13, 14, 33, 34, 35};

int ledOraDec[3] = {0, 23, 24};
int ledOraUn[9] = {2, 3, 4, 19, 20, 21,  26, 27, 28};
int ledMinDec[6] = {6, 7, 16, 17, 30, 31};
int ledMinUn[9] = {9, 10, 11, 12, 13, 14, 33, 34, 35};
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


String ora = "12:34";
int oraDec = -10;
int oraUn = -10;
int minDec = -10;
int minUn = -10;

int luminosita;

DS3231 rtc(SDA, SCL);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 5, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  String ora;
  rtc.begin();
  pinMode( A0, INPUT);
  
  strip.setBrightness(25);
  strip.begin();
  for(int i=0; i<27; i++){        
    strip.setPixelColor(tutti[i], strip.Color( 255 , 0, 0));
  }
  strip.show(); // Initialize all pixels to 'off'
  delay(1000);    
  for(int i=0; i<27; i++){    //spegne tutti i led
    strip.setPixelColor(tutti[i], strip.Color( 0, 0, 0));
  }
  strip.show();
  
  delay(1000);

  ora =  rtc.getTimeStr();
    oraDec = (int) ora[0] -48;      
    oraUn = (int) ora[1] -48;
    minDec = (int) ora[3] -48;
    minUn = (int) ora[4] -48;
    int nLedOraDec = 3;
    int nLedOraUn = 9;
    int nLedMinDec = 6;
    int nLedMinUn = 9;
    ledAccesi(ledOraDec, nLedOraDec, oraDec, 1);          
    ledAccesi(ledOraUn, nLedOraUn, oraUn, 2);
    ledAccesi(ledMinDec, nLedMinDec, minDec, 3);
    ledAccesi(ledMinUn, nLedMinUn, minUn, 4);
  
}
void loop() {
    
    
    for(int j = 0; j<500; j++)
    {
    luminosita = analogRead(A1);
    Serial.println(luminosita);
    if(luminosita < 400)
      strip.setBrightness(55);
    else
      strip.setBrightness(1);
    delay(10);
    strip.show();
    }
    
    ora =  rtc.getTimeStr();
    oraDec = (int) ora[0] -48;      
    oraUn = (int) ora[1] -48;
    minDec = (int) ora[3] -48;
    minUn = (int) ora[4] -48;
    int nLedOraDec = 3;
    int nLedOraUn = 9;
    int nLedMinDec = 6;
    int nLedMinUn = 9;
    ledAccesi(ledOraDec, nLedOraDec, oraDec, 1);           il numero di elementi da illuminare e il colore(attraverso un int)
    ledAccesi(ledOraUn, nLedOraUn, oraUn, 2);
    ledAccesi(ledMinDec, nLedMinDec, minDec, 3);
    ledAccesi(ledMinUn, nLedMinUn, minUn, 4);
    
 
}

void ledAccesi(int vett[], int n, int w, int colore) {
  boolean vettBool[n];      
  for (int i = 0; i < n; i++)
    vettBool[i] = false;      
  int vettControllo[w];
  for (int i = 0; i < w; i++)
    vettControllo[i] = -10;
  int a = -20;
  int indiceVettore = 0;
  int j = 0;
  boolean flag = true;
  if (w != 0) {
    while (indiceVettore != w) {
      flag = true;
      a = random(n);
      for (j = 0; j < w; j++) {
        if (vettControllo[j] == a){
          flag = false;
          break;
        }
      }
      if (flag == true) {
        vettControllo[indiceVettore] = a;
        indiceVettore++;
      }
    }
  }
  for (int k = 0; k < w; k++) {
    int s = vettControllo[k];
    vettBool[s] = true;
  }
  for (int i = 0; i < n; i++) {
    if (vettBool[i] == true) {
      switch (colore) {
        case 1: strip.setPixelColor(vett[i], strip.Color(255, 0, 0));    break;    // hour tens' color
        case 2: strip.setPixelColor(vett[i], strip.Color(0, 255, 0));   break;    //hour units' color 
        case 3: strip.setPixelColor(vett[i], strip.Color(255, 255, 0));   break;    //minutes tens' color
        case 4: strip.setPixelColor(vett[i], strip.Color(0, 0, 255));    break;   //minutes units' color
        default: strip.setPixelColor(vett[i], strip.Color(0, 0, 0));
      }
    }
    else
      strip.setPixelColor(vett[i], strip.Color(0, 0, 0));
  }
  strip.show();
}
