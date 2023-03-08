#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel linijka = Adafruit_NeoPixel(16, 2, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
   linijka.begin(); //Inicjalizacja
  linijka.show();
  linijka.setPixelColor(0, linijka.Color(255,0,0));
   linijka.show();


//for (int i =0; i<9; i++){
  int gain =1;
float red, green, blue;
getHeatMapColor((80.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(0, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

getHeatMapColor((75.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(1, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();
//}

getHeatMapColor((60.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(2, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

   getHeatMapColor((50.f-30.f)/60.f, &red, &green, &blue);
  linijka.setPixelColor(3, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

   getHeatMapColor((30.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(4, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

   getHeatMapColor((30.f-30.f)/60.f, &red, &green, &blue);
  linijka.setPixelColor(5, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

   getHeatMapColor((30.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(6, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

   getHeatMapColor((30.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(7, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

   getHeatMapColor((30.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(8, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();

   getHeatMapColor((30.f-30.f)/50.f, &red, &green, &blue);
  linijka.setPixelColor(9, linijka.Color((int)(red*gain),(int)(green*gain),(int)(blue*gain)));
   linijka.show();


}

void loop() {
  // put your main code here, to run repeatedly:

/*
        for (int i =0; i<255; i++){

          linijka.setPixelColor(i%16, linijka.Color(255-i,i,i));
          linijka.setPixelColor((i+3)%16, linijka.Color(i,128-i,50));
          linijka.show();
          delay(5);
          linijka.setPixelColor(i%16, linijka.Color(0,0,0));
          linijka.setPixelColor((i-1)%16, linijka.Color(0,0,0));
        }
*/
}

bool getValueBetweenTwoFixedColors(float value, int &red, int &green, int &blue)
{
  int aR = 0;   int aG = 0; int aB=255;  // RGB for our 1st color (blue in this case).
  int bR = 255; int bG = 0; int bB=0;    // RGB for our 2nd color (red in this case).
  
  red   = (float)(bR - aR) * value + aR;      // Evaluated as -255*value + 255.
  green = (float)(bG - aG) * value + aG;      // Evaluates as 0.
  blue  = (float)(bB - aB) * value + aB;      // Evaluates as 255*value + 0.
}

bool getHeatMapColor(float value, float *red, float *green, float *blue)
{
  const int NUM_COLORS = 4;
  static float color[NUM_COLORS][3] = { {0,0,1}, {0,1,0}, {1,1,0}, {1,0,0} };
    // A static array of 4 colors:  (blue,   green,  yellow,  red) using {r,g,b} for each.
  
  int idx1;        // |-- Our desired color will be between these two indexes in "color".
  int idx2;        // |
  float fractBetween = 0;  // Fraction between "idx1" and "idx2" where our value is.
  
  if(value <= 0)      {  idx1 = idx2 = 0;            }    // accounts for an input <=0
  else if(value >= 1)  {  idx1 = idx2 = NUM_COLORS-1; }    // accounts for an input >=0
  else
  {
    value = value * (NUM_COLORS-1);        // Will multiply value by 3.
    idx1  = floor(value);                  // Our desired color will be after this index.
    idx2  = idx1+1;                        // ... and before this index (inclusive).
    fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).
  }
    
  *red   = (color[idx2][0] - color[idx1][0])*fractBetween + color[idx1][0];
  *green = (color[idx2][1] - color[idx1][1])*fractBetween + color[idx1][1];
  *blue  = (color[idx2][2] - color[idx1][2])*fractBetween + color[idx1][2];
}
