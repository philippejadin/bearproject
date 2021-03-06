
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "01-rfid-nl"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier

unsigned long timeout = 0;
int playing = false;




void setup() {
  bear_init();
  Serial.println("loop 01-idle-nl.h264");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    if (bear_set_locale(LOCALE_NL)) {
      Serial.println("play 01-action-nl.h264");

      // efface les données de la carte
      bear_erase();

      bear_stop();

      timeout = millis();
      playing = true;

      bear_led_blink();
      bear_delay(2000);

    } else {
      bear_delay(10);
      bear_stop();
    }

  }


  if (millis() > timeout + 12000 && playing)
  {
    Serial.println("loop 01-idle-nl.h264");
    playing = false;
  }
}
