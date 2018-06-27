/*


   Cette version utilise juste une boucle for

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

   Cablage mosfet :
  - blanc : GND
  - brun : VCC
  - vert : mosfet 1 / pin 5
  - jaune : mosfet 2 / pin 6

*/

const char MODULE_NAME[] = "19-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier

void setup() {
  bear_init();
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    analogWrite(LED_PIN, LED_HIGH);
    bear_stop();



    Serial.println("start show");

    digitalWrite(RELAY_1, HIGH);
    analogWrite(LED_PIN, LED_HIGH);

    bear_led_blink();

    bear_delay(200);

    digitalWrite(RELAY_1, LOW);
    analogWrite(LED_PIN, LED_LOW);


    bear_delay(2000);

    Serial.println("ready for more");

  } else {

    bear_delay(100);
    bear_stop();

  }

}


