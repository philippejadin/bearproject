/*

  Cette version utilise fadeled

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

   Cablage switch :
  - Brun : Switch 5V
  - Jaune : Switch (pin 6)
  - Blanc : LED -
  - Vert : LED + (12V!) (pin 5 en pwm sur l'arduino)



*/

const char MODULE_NAME[] = "10-rfid-balance"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

const int switchPin = 6; // switch déclencheur de la balance
int buttonState = 0; 

void setup() {
  bear_init();
  pinMode(switchPin, INPUT);
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // code debug
  buttonState = digitalRead(switchPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    analogWrite(LED_PIN, LED_HIGH);
  } else {
    // turn LED off:
    analogWrite(LED_PIN, LED_LOW);
  }
  // fin code debug

  // Attend une carte RFID
  if (bear_has_card()) {

    analogWrite(LED_PIN, LED_HIGH);
    bear_stop();
    bear_led_blink();

    for (int i = 0; i < 10; i++)
    {
      analogWrite(5, 255);
      delay(500);

      analogWrite(5, 0);
      delay(500);

    }

  }

}


