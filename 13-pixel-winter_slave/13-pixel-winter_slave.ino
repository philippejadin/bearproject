
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

const char MODULE_NAME[] = "13-rfid-winter_slave"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier
#include <Wire.h> // i2c

int saison;
// cfr. https://www.arduino.cc/en/Tutorial/MasterReader


void setup() {
  bear_init();
  Wire.begin(10);        // join i2c bus (address optional for master)
  Wire.setClock(10000); // 10khz bus speed
  Wire.onRequest(requestEvent); // register event
}

//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {
    bear_stop();
    saison = 1;
    bear_delay(1000);

  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {

  Wire.write(saison); // on envoit la locale reçue et puis on la remet à 0 pour ne plus l'envoyer la fois suivante
  if (saison != 0)
  {
    saison = 0;
  }

}
