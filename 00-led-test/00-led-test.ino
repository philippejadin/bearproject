
/*
   Module test qui lance en boulce 2 video l'une derrière l'autre assez vite pour voir si tout va bien après plusieurs heures

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "00-led-test"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier

void setup() {
  bear_init();
  //sSerial.println("loop 01-fr-idle.h264");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,

  int i;

  for (i = 0; i <= 255; i++) {
    analogWrite(MOSFET_1, i);
    delay(1);
  }

  for (i = 255; i >= 0; i--) {
    analogWrite(MOSFET_1, i);
    delay(2);
  }

  delay(400);
  
  if (bear_has_card())
  {
    Serial.println("play test.wav");
    Serial.println("loop 01-fr-idle.h264");
    bear_delay(1000);
  }



}
