/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "00-base"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch

#include <SPI.h>
#include <MFRC522.h>
#include <avr/wdt.h>
#include <FadeLed.h>
#include <bearlib.h> // à inclure en dernier



void setup() {
  bear_init();
  wdt_enable(WDTO_8S); // active le watchdog pour rebooter l'arduino si pas de réponse après 8 secondes
}



//*****************************************************************************************//
void loop() {
  FadeLed::update(); // gestion du fondu des leds, à appeller en boucle
  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente

  
  // Attend une carte RFID
  if (bear_has_card()) {

    analogWrite(LED_PIN, LED_HIGH);

    byte locale = bear_get_locale();


    // en fonction de la locale on écrit en série ce que l'on veut faire :
    if (locale == LOCALE_FR)
    {
      Serial.println(F("play fr.h264"));
    }

    if (locale == LOCALE_NL)
    {
      Serial.println(F("play nl.h264"));
    }

    if (locale == LOCALE_EN)
    {
      Serial.println(F("play en.h264"));
    }

    if (locale == LOCALE_DE)
    {
      Serial.println(F("play de.h264"));
    }

    bear_led_blink();
    
    delay(500); // attente totale : 1300 ms
  }

}


