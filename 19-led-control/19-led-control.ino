/*
  Sur ce module spécifiquement :
  - PIN 6 : data neopixel
  - PIN 11 : digital in pour déclenchement


  PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

   Cablage mosfet :
  - blanc : GND
  - brun : VCC
  - vert : mosfet 1 / pin 5
  - jaune : mosfet 2 / pin 6

*/

const char MODULE_NAME[] = "19-led-control"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
const int NEOPIXEL_PIN = 6;
const int TRIGGER_PIN = 11;
int k;

//--------------------- config
int num_pixels = 200;
// ---------------------------


#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(num_pixels, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


//#include <bearlib.h> // à inclure en dernier

void setup() {
  Serial.begin(9600);
  Serial.println(MODULE_NAME);
  pinMode(TRIGGER_PIN, INPUT);

  strip.begin();
  strip.setBrightness(220); // 0 -> 255 (à 255 ça chauffe un peu, 220 éclaire quasi autant et semble plus safe)
  strip.show(); // Initialize all pixels to 'off'
}

//*****************************************************************************************//
void loop() {


  // Serial.println(digitalRead(TRIGGER_PIN)); // debug
  delay (20);

  while (digitalRead(TRIGGER_PIN) == HIGH)
  {
    Serial.println("show begin!");
    startshow(); // voir ci-dessous
    delay(500);
    Serial.println("show finished!");
  }

}


void startshow()
{
  // allume tout depuis le bas :
  for (int i = 0; i < num_pixels; i++)
  {
    strip.setPixelColor(i, 255, 200, 150);
    strip.setPixelColor(num_pixels - i, 255, 200, 150);
    strip.show();
    delay(2);
  }


  rainbow(1);

  delay(500);

  // éteint tout progressivement
  for (int i = 0; i < num_pixels / 2; i++)
  {
    strip.setPixelColor((num_pixels / 2) - i, 0, 0, 0);
    strip.setPixelColor((num_pixels / 2) + i, 0, 0, 0);
    strip.show();
    delay(2);
  }

  // éteint dernier pixels
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();


}



void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (int k=0; k < 1; k++) {
    for (j = 0; j < 256; j++) {
      if (j < 125) {
        strip.setBrightness(50);
      }
      else {
        strip.setBrightness(220);
      }
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel((i + j) & 255));
      }

      strip.show();
      delay(wait);
    }
  }
}




// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



