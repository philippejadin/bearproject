
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "15-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

int count = 1;

void setup() {
  bear_init();
  Serial.println("play 15-action1.png");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {


    bear_stop();

    count ++;

    if (count > 5)
    {
      count = 0;
    }

    if (count == 1)
    {
      Serial.println("play 15-action1.png");
    }
     if (count == 2)
    {
      Serial.println("play 15-action2.png");
    }
     if (count == 3)
    {
      Serial.println("play 15-action3.png");
    }
     if (count == 4)
    {
      Serial.println("play 15-action4.png");
    }
     if (count == 5)
    {
      Serial.println("play 15-action5.h264");
    }

    bear_led_blink();
  }

}
