/*


  Sur ce module spécifiquement :
  - PIN 6 : data neopixel

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)


  adresses i2c : (les adresses 0 à 7 sont réservées)
   - panda = 10
   - lippu = 11
   - malais = 12
   - collier = 13
   - lunette = 14
   - noir = 15
   - polaire = 16
   - brun = 17

   principe : le master demande à chaque slave si il a quelque chose à envoyer,
   si c'est le cas, le slave envoi le chiffre de la locale (fr, nl, en ou de),
   ainsi le master peux lancer la video adéquate en fonction de la locale et du numéro du slave

*/

const char MODULE_NAME[] = "16-pixel-master"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier
#include <Wire.h> // i2c 
// cfr. https://www.arduino.cc/en/Tutorial/MasterReader


// Setup neopixel libs
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6 // pin du data neopixel

/*

  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);
*/

// TODO changer le 4 en 6 quand les 6 panneaux sont soudés :
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 4, 1, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE +
                            NEO_TILE_TOP + NEO_TILE_RIGHT + NEO_TILE_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

int x = 0; // position du texte

int locale = 0; // locale stockée de manière globale



void setup() {
  bear_init();

  //i2c
  Wire.begin(9);        // join i2c bus (address optional for master)
  Wire.setClock(10000); // 10khz bus speed


  // neopixels :
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(50);
  matrix.setTextColor(colors[0]);

  x = matrix.width();

  matrix.fillScreen(matrix.Color(0, 0, 0));
  matrix.setCursor(x, 0);
  matrix.show();

  pixel_print("ready");
  delay(5000);
  pixel_clear();

}




int pass = 0;


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot






  // interroge chaque slave à tour de role pour savoir si il a quelque chose à nous dire (une locale)
  for (int i = 10; i < 18; i++)
  {
    Wire.requestFrom(i, 1);    // request 1 bytes from slave device #i (10-17)

    while (Wire.available()) { // slave may send less than requested
      locale = Wire.read(); // receive a byte as character

      if (locale != 0)
      {
        Serial.print("slave id : ");
        Serial.println(i);         // imprime l'adresse qui a répondu
        Serial.print("locale : ");
      }

      if (locale == LOCALE_FR)
      {
        Serial.println("FR");
        pixel_clear();
        pixel_print("fr");
      }
      if (locale == LOCALE_EN)
      {
        Serial.println("EN");
        pixel_clear();
        pixel_print("en");
      }

      if (locale == LOCALE_NL)
      {
        Serial.println("NL");
        pixel_clear();
        pixel_print("nl");
      }

      if (locale == LOCALE_DE)
      {
        Serial.println("DE");
        pixel_clear();
        pixel_print("de");
      }


    }

  }
}


void pixel_print(String message)
{
  matrix.setTextColor(matrix.Color(255, 0, 0));
  matrix.setCursor(0, 0);
  matrix.print(message);
  matrix.show();
  delay(70);
}

void pixel_clear()
{
  matrix.fillScreen(matrix.Color(0, 0, 0));
  matrix.show();
}

