
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "06-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

int locale;

void setup() {
  bear_init();
  //Serial.println("loop 02-fr-idle.h264");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    analogWrite(LED_PIN, LED_HIGH);
    locale = bear_get_locale();
    bear_stop();

else {
    if (locale == (LOCALE_FR))
    {
      Serial.println("play 06-action-fr.wav");
    }

    if (locale == (LOCALE_EN))
    {
      Serial.println("play 06-action-en.wav");
    }

    if (locale == (LOCALE_NL))
    {
      Serial.println("play 06-action-nl.wav");
    }


    if (locale == (LOCALE_DE))
    {
      Serial.println("play 06-action-de.wav");
    }
    bear_led_blink();
}
  }

}
