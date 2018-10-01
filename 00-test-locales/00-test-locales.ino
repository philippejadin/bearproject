
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "00-test-locale"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

int locale;
int food;

void setup() {
  bear_init();
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    locale = bear_get_locale();
    food = bear_read(5, 0);

    bear_stop();

    Serial.print("locale nr : ");
    Serial.println(locale);

    Serial.print("food nr : ");
    Serial.println(food);




    if (locale)
    {
      if (locale == (LOCALE_FR))
      {
        Serial.println("Locale is french");
      }

      if (locale == (LOCALE_EN))
      {
        Serial.println("Locale is english");
      }

      if (locale == (LOCALE_NL))
      {
        Serial.println("Locale is nederlands");
      }


      if (locale == (LOCALE_DE))
      {
        Serial.println("Locale is deutsch");
      }
      bear_led_blink();
      bear_delay(100);
    }
  }

}
