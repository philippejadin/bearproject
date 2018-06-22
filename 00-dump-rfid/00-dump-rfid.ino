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

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));


    delay(1000);
    // TOUJOURS appeller bear_stop quand on a fini avec la carte
    bear_stop();


    bear_led_blink();

    bear_delay(500); // attente totale : 1300 ms
  }

}


