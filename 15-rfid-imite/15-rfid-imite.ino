
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
  Serial.println("play 15-action1.jpg");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {


    bear_stop();

    count ++;

    if (count > 9)
    {
      count = 1;
    }

    if (count == 1)
    {
      Serial.println("play 15-action1.jpg");
    }
    if (count == 2)
    {
      Serial.println("play 15-action2.jpg");
    }
    if (count == 3)
    {
      Serial.println("play 15-action3.jpg");
    }
    if (count == 4)
    {
      Serial.println("play 15-action4.jpg");
    }
    if (count == 5)
    {
      Serial.println("loop 15-action5.h264");
    }
    if (count == 6)
    {
      Serial.println("play 15-action6.jpg");
    }
    if (count == 7)
    {
      Serial.println("play 15-action7.jpg");
    }
    if (count == 8)
    {
      Serial.println("play 15-action8.jpg");
    }
    if (count == 9)
    {
      Serial.println("play 15-action9.jpg");
    }
    /*
    if (count == 10)
    {
      Serial.println("play 15-action10.png");
    }
    if (count == 11)
    {
      Serial.println("play 15-action11.png");
    }
    */
    
    bear_led_blink();
    bear_delay(200);
  }

}
