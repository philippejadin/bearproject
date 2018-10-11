
/*
   Module est le même pour 14 box 1 et 14 box 2

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "14-rfid-box"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

int locale;
unsigned long timeout = 0;
int playing = false;

void setup() {
  bear_init();
  Serial.println("loop 14-idle.h264");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {
    bear_stop();

    Serial.println("play 14-action.wav");
    Serial.println("play 14-action.h264");

    bear_led_blink();

    timeout = millis();
    playing = true;



  }

  if (millis() > timeout + 72000 && playing)
  {
    Serial.println("loop 14-idle.h264");
    playing = false;
  }



}
