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
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 5, 1, PIN,
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
  matrix.setBrightness(20);
  matrix.setTextColor(colors[0]);

  x = matrix.width();

  matrix.fillScreen(matrix.Color(0, 0, 0));
  matrix.setCursor(x, 0);
  matrix.show();

  pixel_print("ready");
  delay(2000);
  pixel_clear();

}




int pass = 0;


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot


  // interroge chaque slave à tour de role pour savoir si il a quelque chose à nous dire (une locale)
  for (int slave_id = 10; slave_id < 18; slave_id++)
  {
    Wire.requestFrom(slave_id, 1);    // request 1 bytes from slave device #slave_id (10-17)

    while (Wire.available()) { // slave may send less than requested
      locale = Wire.read(); // receive a byte as character


      if (locale != 0)
      {
        Serial.print("slave id : ");
        Serial.println(slave_id);         // imprime l'adresse qui a répondu


        // construction du nom de fichier :
        //16-cartel-panda-fr.h264

        String filename = "16-cartel-";
        long countdown = 0; // nombre d'ours encore en vie
        int color = 1; // couleur du chiffre définitif

        pixel_clear();

        if (slave_id == 10)
        {
          filename = filename + "panda";
          countdown = 2000;
          color = 2;
        }
        if (slave_id == 11)
        {
          filename = filename + "lippu";
          countdown = 20000;
          color = 1;
        }
        if (slave_id == 12)
        {
          filename = filename + "malais";
          countdown = 10000;
          color = 1;

        }
        if (slave_id == 13)
        {
          filename = filename + "collier";
          countdown = 60000;
          color = 1;
        }
        if (slave_id == 14)
        {
          filename = filename + "lunette";
          countdown = 10000;
          color = 1;
        }
        if (slave_id == 15)
        {
          filename = filename + "noir";
          countdown = 900000;
          color = 3;
        }
        if (slave_id == 16)
        {
          filename = filename + "polaire";
          countdown = 25000;
          color = 1;
        }
        if (slave_id == 17)
        {
          filename = filename + "brun";
          countdown = 200000;
          color = 3;
        }

        filename = filename + "-";



        Serial.print("locale : ");

        if (locale == LOCALE_FR)
        {
          filename = filename + "fr";
          Serial.println("FR");
        }
        else if (locale == LOCALE_EN)
        {
          filename = filename + "en";
          Serial.println("EN");
        }
        else if (locale == LOCALE_NL)
        {
          filename = filename + "nl";
          Serial.println("NL");
        }

        else if (locale == LOCALE_DE)
        {
          filename = filename + "de";
          Serial.println("DE");
        }
        else
        {
          filename = filename + "en";
          Serial.println("EN");
        }


        // joue le fichier
        filename = filename + ".h264";

        Serial.print("loop ");
        Serial.println(filename);

        // affiche le nombre sur le lcd avec anim
        pixel_countdown(countdown, color);
      }
    }
  }
}


void pixel_print(String message)
{
  matrix.setTextColor(matrix.Color(255, 255, 255));
  matrix.setCursor(0, 0);
  matrix.print(message);
  matrix.show();
  bear_delay(70);
}


// colors :
// 1 = rouge
// 2 = orange
// 3 = vert
void pixel_countdown(long number, int color)
{
  matrix.setTextColor(matrix.Color(255, 255, 255));
  matrix.setCursor(0, 0);

  long interval = number / 50; // nombre de "frames" dans l'animation du décompte
  for (long i = 0; i <= number; i = i + interval)
  {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    pixel_print_aligned(i);
    matrix.show();
    bear_delay(5);
  }

  bear_delay(250);

  if (color == 1)
  {
    matrix.setTextColor(matrix.Color(255, 0, 0));
  }

  if (color == 2)
  {
    matrix.setTextColor(matrix.Color(255, 128, 0));
  }

  if (color == 3)
  {
    matrix.setTextColor(matrix.Color(0, 255, 0));
  }

  matrix.fillScreen(matrix.Color(0, 0, 0));
  pixel_print_aligned(number);
  matrix.show();



}


// affiche un nombre sur le neopixel avec le bon alignement (à droite)
void pixel_print_aligned(long number)
{

  if (number < 10000000)
  {
    matrix.setCursor(0, 0);
  }

  if (number < 1000000)
  {
    matrix.setCursor(5, 0);
  }

  if (number < 100000)
  {
    matrix.setCursor(11, 0);
  }

  if (number < 10000)
  {
    matrix.setCursor(17, 0);
  }

  if (number < 1000)
  {
    matrix.setCursor(23, 0);
  }

  if (number < 100)
  {
    matrix.setCursor(29, 0);
  }

  if (number < 10)
  {
    matrix.setCursor(36, 0);
  }







  matrix.print(number);
}

void pixel_clear()
{
  matrix.fillScreen(matrix.Color(0, 0, 0));
  matrix.show();
}

