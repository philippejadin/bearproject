
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)


  adresses i2c : (les adresses 0 à 7 sont réservées)
   - winter = 10

   principe : le master demande à chaque slave si il a quelque chose à envoyer,
   si c'est le cas, le slave envoi le chiffre de la locale (fr, nl, en ou de),
   ainsi le master peux lancer la video adéquate en fonction de la locale et du numéro du slave

*/

const char MODULE_NAME[] = "13-rfid-summer-master"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier
#include <Wire.h> // i2c 
// cfr. https://www.arduino.cc/en/Tutorial/MasterReader


int saison = 0; // locale stockée de manière globale

void setup() {
  bear_init();
  Wire.begin(9);        // join i2c bus (address optional for master)
  Wire.setClock(10000); // 10khz bus speed
}

//*****************************************************************************************//
void loop() {
  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  // interroge chaque slave à tour de role pour savoir si il a quelque chose à nous dire (une locale)
  Wire.requestFrom(11, 1);    // request 1 bytes from slave device #i (10-17)

  while (Wire.available()) {

    saison = Wire.read();
    if (saison != 0){
    

      Serial.println("play 13-prout.wav");
      delay(100);
      Serial.println("play 13-action-winter.h264");
}

}
if (bear_has_card()) {
  bear_stop();

  Serial.println ("play 13-prout.wav");
  delay(100);
  Serial.println("play 13-action-summer.h264");
  bear_led_blink();
}
}
