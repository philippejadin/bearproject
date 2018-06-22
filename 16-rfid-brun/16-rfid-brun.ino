
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)


  adresses i2c : (les adresses 0 à 7 sont réservées)
   - panda = 10
   - lippu = 11
   - malais = 12
   - collier = 13
   - lunette = 14
   - noir = 15
   - polaire = 16
   - brun = 17

*/

const char MODULE_NAME[] = "16-rfid-brun"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier
#include <Wire.h> // i2c 
// cfr. https://www.arduino.cc/en/Tutorial/MasterReader


int locale = 0; // locale stockée de manière globale

void setup() {
  bear_init();
  Wire.begin(17);                // join i2c bus with address #10
  Wire.onRequest(requestEvent); // register event
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {
    analogWrite(LED_PIN, LED_HIGH);
    locale = bear_get_locale(); // on stocke la locale qui sera envoyée au master quand il la demandera
    bear_stop();
    Serial.print("locale : ");
    Serial.println(locale);
    bear_led_blink();
    bear_delay(500);
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {

  Wire.write(locale); // on envoit la locale reçue et puis on la remet à 0 pour ne plus l'envoyer la fois suivante
  if (locale != 0)
  {
    locale = 0;
  }

}
