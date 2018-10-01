
/*
   Configuration spéciale de la raspberry pour ce module!

  Dans config.ini :
  - hdmi boost est uncommenté et mis à 4
  - la config spéciale hdmi des petits lcd est commentée pour garder l'auto config hdmi standard


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

    if (count > 11)
    {
      count = 1;
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
      //bear_delay(1000);
    }
    if (count == 6)
    {
      Serial.println("play 15-action6.png");
    }
    if (count == 7)
    {
      Serial.println("play 15-action7.png");
    }
    if (count == 8)
    {
      Serial.println("play 15-action8.png");
    }
    if (count == 9)
    {
      Serial.println("play 15-action9.png");
    }
    if (count == 10)
    {
      Serial.println("play 15-action10.png");
    }
    if (count == 11)
    {
      Serial.println("play 15-action11.png");
    }



    bear_led_blink();
  }

}
