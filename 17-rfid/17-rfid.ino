/*
   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "17-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

int count = 0;

void setup() {
  bear_init();
  Serial.println("play 17-background.png");
  Serial.println("loop 17-idle.h264");
  
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    bear_stop();

    count ++;

    if (count == 6)
    {
      count = 1;
    }

    analogWrite(LED_PIN, LED_HIGH);

    if (count == 1)
    {
      Serial.println("play 17-option1.wav");
      Serial.println("play 17-option1.h264");
      bear_delay(25000);
    }
    if (count == 2)
    {
      Serial.println("play 17-option2.wav");
      Serial.println("play 17-option2.h264");
      bear_delay(28000);
    }
    if (count == 3)
    {
      Serial.println("play 17-option3.wav");
      Serial.println("play 17-option3.h264");
      bear_delay(30000);
    }
    if (count == 4)
    {
      Serial.println("play 17-option4.wav");
      Serial.println("play 17-option4.h264");
      bear_delay(25000);
    }
    if (count == 5)
    {
      Serial.println("play 17-option5.wav");
      Serial.println("play 17-option5.h264");
      bear_delay(25000);
    }

    
    analogWrite(LED_PIN, LED_LOW);


    Serial.println("loop 17-idle.h264");


  }

}
