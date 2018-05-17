
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
const int duree_max = 5000;
boolean play_video_wait;
#include <bearlib.h> // à inclure en dernier



void setup() {
  bear_init();
  Serial.println("loop 01-fr-idle.h264");
  play_video_wait = true;
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,

  if (play_video_wait != ) {
    Serial.println("loop 01-fr-idle.h264");

  }


  // Attend une carte RFID
  if (bear_has_card()) {

    analogWrite(LED_PIN, LED_HIGH);
    play_video_wait = false;
    if (bear_set_locale(LOCALE_FR)) {
      bear_led_blink();
      Serial.println("play 01-fr-action.h264");
      bear_is_playing(duree_max);

    } else {
      bear_led_blink_error();
      Serial.println("play error_fr.mp4");

      bear_is_playing(duree_max);
    }
  }
}


