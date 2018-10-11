/*
   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

  Numéro de block : 6

  Position :
  08-rfid-panda :  1
  08-rfid-lippu : 2
  08-rfid-malais : 3
  08-rfid-collier : 4
  08-rfid-lunette : 5
  08-rfid-noir : 6
  08-rfid-polaire : 7
  08-rfid-brun : 8

*/

const char MODULE_NAME[] = "08-rfid-noir"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier

void setup() {
  bear_init();
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot
  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,

  // Attend une carte RFID
  if (bear_has_card()) {

    if (bear_read(6, 10) == 1) // efface tout si on a affiché le résultat
    {
      bear_erase_block(6);
      Serial.println("card reset");
    }

    if (bear_write(6, 6, 1)) //(block, position, valeur)
    {
      bear_led_blink();
    }
    bear_stop();

  }

  bear_delay(100);



}
