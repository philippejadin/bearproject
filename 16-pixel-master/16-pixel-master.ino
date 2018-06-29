/*
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


int locale = 0; // locale stockée de manière globale

void setup() {
  bear_init();
  Wire.begin(9);        // join i2c bus (address optional for master)
  Wire.setClock(10000); // 10khz bus speed
}


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
      }
      if (locale == LOCALE_EN)
      {
        Serial.println("EN");
      }

      if (locale == LOCALE_NL)
      {
        Serial.println("NL");
      }

      if (locale == LOCALE_DE)
      {
        Serial.println("DE");
      }

      
    }

  }
}
