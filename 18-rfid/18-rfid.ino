
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "18-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier


/*********** config *********/
const int duree_show = 5000;
/*********** ****************/

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup() {
  bear_init();
  Serial.println("loop 01-fr-idle.mp4");
  pinMode (RELAY_1, OUTPUT);//pin4

}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID

  if (bear_has_card()) {
    analogWrite(LED_PIN, LED_HIGH);


    //allume le relais selectionné
    digitalWrite (RELAY_1, HIGH );

    /*analogWrite (MOSFET_1, mosfet_etat);
      for (int i; i < duree_show; i++) {
      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;

      // reverse the direction of the fading at the ends of the fade:
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
      // wait for 30 milliseconds to see the dimming effect
      bear_delay(30);
      }
    */

    bear_led_blink();
    bear_stop();
    bear_delay(duree_show);
    digitalWrite (RELAY_1, HIGH );

  }

}
