
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "09-rfid-lippu"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
const int duree_video = 1800;//en ms
int locale, food;
#include <bearlib.h> // à inclure en dernier

void setup() {
  bear_init();
  Serial.println("loop 09-idle-lippu.h264");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot
  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,

  // Attend une carte RFID
  if (bear_has_card()) {
    locale = bear_get_locale();
    delay(100);// verifier
    food = bear_read(5, 0);
    delay(100);
    bear_stop();
    if (food == 0) {

      if (locale == (LOCALE_FR))
      {
        Serial.println("play 09-wrong-fr.png");
      };

      if (locale == (LOCALE_EN))
      {
        Serial.println("play 09-wrong-en.png");
      };

      if (locale == (LOCALE_NL))
      {
        Serial.println("play 09-wrong-nl.png");
      };

      if (locale == (LOCALE_DE))
      {
        Serial.println("play 09-wrong-de.png");
      };
      bear_led_blink();
    }

    else if (food == 1) {
      Serial.println("09-result-lippu1.h264");
    }

    else if (food == 2) {
      Serial.println("09-result-lippu2.h264");
    }

    else if (food == 3) {
      Serial.println("09-result-lippu3.h264");
    }

    else if (food == 4) {
      Serial.println("09-result-lippu4.h264");
    }

    else if (food == 5) {
      Serial.println("09-result-lippu5.h264");
    }

    else if (food == 6) {
      Serial.println("09-result-lippu6.h264");
    }

    else if (food == 7) {
      Serial.println("09-result-lippu7.h264");
    }

    else if (food == 8) {
      Serial.println("09-result-lippu8.h264");
    }
    else if (food == 9) {
      Serial.println("09-result-lippu9.h264");
    }
    else if (food == 10) {
      Serial.println("09-result-lippu10.h264");
    }
    else if (food == 11) {
      Serial.println("09-result-lippu11.h264");
    }
    bear_led_blink();
    bear_delay(duree_video);//ce chiffre est à peu près ok
    //Serial.println("bear on the place");

    Serial.println("loop 09-idle-lippu.h264");
  }

}
