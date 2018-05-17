
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "01-rfid-fr"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
const int duree_max = 2000;

#include <bearlib.h> // à inclure en dernier



void setup() {
  bear_init();
  Serial.println("loop 01-fr-idle.h264");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    analogWrite(LED_PIN, LED_HIGH);

    if (bear_set_locale(LOCALE_FR)) {

      Serial.println("play 01-fr-action.h264");
      bear_led_blink();
      while (bear_is_playing(duree_max))
      {
      }
      
      Serial.println("loop 01-fr-idle.h264");
    
    } else {

      Serial.println("play error_fr.mp4");
      bear_led_blink_error();
      while (bear_is_playing(duree_max))
      {
      }
      
      Serial.println("loop 01-fr-idle.h264");
    }
  }

}
