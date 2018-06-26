/*

  Cette version utilise fadeled

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

const char MODULE_NAME[] = "12-rfid-moving"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

//----- config me
const int pause = 1000;  // ms
const int battement = 2000; // ms
const int nbr_battement = 6;
//-----------


int up_and_down = (battement / 3);

void coeur() {

  for (int i = 0; i <= up_and_down; i++) {
    int var_led = map(i, 0, up_and_down, 0, 255);
    //analogWrite (MOSFET_1, var_led );
    analogWrite (3, var_led );
    wdt_reset();

  }


  bear_delay(up_and_down);

  for (int i = up_and_down; i >= 0; i--) {
    int var_led = map(i, 0, up_and_down, 0, 255);
    //analogWrite (MOSFET_1, var_led );
    analogWrite (3, var_led );
    wdt_reset();
  }

}
void setup() {
  bear_init();
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {
    bear_stop();
    for (int i = 0; i <= nbr_battement; i++ ) {
      Serial.print("play 12-moving.wav");
      coeur();
      bear_delay(pause);
    }



  }

}


