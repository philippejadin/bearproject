/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "00-test-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch

#include <bearlib.h> // à inclure en dernier



void setup() {
  bear_init();
}



//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente


  // Attend une carte RFID
  if (bear_has_card()) {

    Serial.println("carte détectée");

    analogWrite(LED_PIN, LED_HIGH);

    Serial.print("data : ");
    Serial.println(bear_read(4, 1));


    bear_write(4, 1, 2);


    Serial.print("data : ");
    Serial.println(bear_read(4, 1));

    bear_set_locale(LOCALE_DE);

    byte locale = bear_get_locale();

    Serial.print("locale : ");
    Serial.println(locale);


    // en fonction de la locale on écrit en série ce que l'on veut faire :
    if (locale == LOCALE_FR)
    {
      Serial.println(F("play fr.mp4"));
    }

    if (locale == LOCALE_NL)
    {
      Serial.println(F("play nl.mp4"));
    }

    if (locale == LOCALE_EN)
    {
      Serial.println(F("play en.mp4"));
    }

    if (locale == LOCALE_DE)
    {
      Serial.println(F("play de.mp4"));
    }


    bear_stop();
    bear_led_blink();

    delay(500); // attente totale : 1300 ms
  }

}


