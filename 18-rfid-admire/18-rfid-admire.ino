
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)


   RELAIS :
   - Blanc : GND
   - Rose : VCC
   - Brun : Relais 1 - pin 4
   - Vert : Relais 2 - pin 5
   - Gris : Relais 3 - pin 6
   - Jaune : Relais 4 - pin 7

*/

const char MODULE_NAME[] = "18-admire"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier


void setup() {
  bear_init();
  Serial.println("loop 01-fr-idle.mp4");
  pinMode (RELAY_1, OUTPUT);
  pinMode (RELAY_2, OUTPUT);
  pinMode (RELAY_3, OUTPUT);
  pinMode (RELAY_4, OUTPUT);
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    bear_stop();


    //allume le relais selectionné
    digitalWrite (RELAY_1, HIGH );
    Serial.print("Enable relay ");


    bear_led_blink();
    bear_delay(2000);

    digitalWrite (RELAY_1, LOW );
    Serial.print("Disable relay ");
    
  }

}
