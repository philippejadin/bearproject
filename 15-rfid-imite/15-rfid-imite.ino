
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
unsigned long timeout;


void setup() {
  bear_init();
  Serial.println("loop 15-action1.h264");
  timeout = millis();
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {
    bear_stop();
    show_image();
    bear_led_blink();
    bear_delay(500);
  }

  if (millis() > timeout + 60000)
  {
    show_image();
    timeout = millis();
  }

}


void show_image() // affiche un des ours chaque fois un différent
{
  count ++;

  if (count > 9)
  {
    count = 1;
  }

  if (count == 1)
  {
    Serial.println("loop 15-action1.h264");
  }
  if (count == 2)
  {
    Serial.println("loop 15-action2.h264");
  }
  if (count == 3)
  {
    Serial.println("loop 15-action3.h264");
  }
  if (count == 4)
  {
    Serial.println("loop 15-action4.h264");
  }
  if (count == 5)
  {
    Serial.println("loop 15-action5.h264");
  }
  if (count == 6)
  {
    Serial.println("loop 15-action6.h264");
  }
  if (count == 7)
  {
    Serial.println("loop 15-action7.h264");
  }
  if (count == 8)
  {
    Serial.println("loop 15-action8.h264");
  }
  if (count == 9)
  {
    Serial.println("loop 15-action9.h264");
  }

   timeout = millis();

}

