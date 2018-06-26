
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

   Ce module est connecté en midi à la carte axoloti
    https://www.arduino.cc/en/Tutorial/Midi

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor


*/

const char MODULE_NAME[] = "05-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier

int locale;

void setup() {
  Serial.begin(31250); // communication midi avec axoloti

}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {


    // lecture de la langue

    locale = bear_get_locale();
    bear_stop();


    // jouer le son d'explication selon la langue
    // note midi
    // 60 = fr
    // 61 = nl
    // 62 = en
    // 63 = de

    // record xx secondes
    // note midi : 64

    // play xx secondes
    // note midi : 65

    bear_led_blink();

  }

}
