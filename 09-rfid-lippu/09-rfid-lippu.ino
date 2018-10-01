
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
const int duree_video = 3200;//en ms
int locale, food;
#include <bearlib.h> // à inclure en dernier

void setup() {
  bear_init();
  Serial.println("play 09-bkg-lippu.png");
  Serial.println("loop 09-idle-lippu.h264");
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

    Serial.print("food : ");
    Serial.println(food);

    Serial.print("locale : ");
    Serial.println(locale);

    if (food == 20 && locale) // pas de nourriture !
    {
      if (locale == (LOCALE_FR))
      {
        Serial.println("play 09-wrong-fr.png");
      }

      if (locale == (LOCALE_EN))
      {
        Serial.println("play 09-wrong-en.png");
      }

      if (locale == (LOCALE_NL))
      {
        Serial.println("play 09-wrong-nl.png");
      }

      if (locale == (LOCALE_DE))
      {
        Serial.println("play 09-wrong-de.png");
      }
      bear_led_blink();
      bear_delay(4000);
      Serial.println("play 09-bkg-lippu.png");
    }

    if (food > 0 && food < 12)
    {
      if (food == 1) {
        Serial.println("play 09-result-lippu1.h264");
      }

      if (food == 2) {
        Serial.println("play 09-result-lippu2.h264");
      }

      if (food == 3) {
        Serial.println("play 09-result-lippu3.h264");
      }

      if (food == 4) {
        Serial.println("play 09-result-lippu4.h264");
      }

      if (food == 5) {
        Serial.println("play 09-result-lippu5.h264");
      }

      if (food == 6) {
        Serial.println("play 09-result-lippu6.h264");
      }

      if (food == 7) {
        Serial.println("play 09-result-lippu7.h264");
      }

      if (food == 8) {
        Serial.println("play 09-result-lippu8.h264");
      }
      if (food == 9) {
        Serial.println("play 09-result-lippu9.h264");
      }
      if (food == 10) {
        Serial.println("play 09-result-lippu10.h264");
      }
      if (food == 11) {
        Serial.println("play 09-result-lippu11.h264");
      }
      bear_led_blink();
      bear_delay(duree_video);
      Serial.println("loop 09-idle-lippu.h264");
    }
  
  }

}
