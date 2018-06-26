
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
  bear_init();
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
    bear_led_blink();


    // jouer le son d'explication selon la langue
    // note midi
    // 60 = fr
    // 61 = nl
    // 62 = en
    // 63 = de

    if (locale == LOCALE_FR)
    {
      MIDI_note(60);
    }

    if (locale == LOCALE_NL)
    {
      MIDI_note(61);
    }

    if (locale == LOCALE_EN)
    {
      MIDI_note(62);
    }

    if (locale == LOCALE_DE)
    {
      MIDI_note(63);
    }

    bear_delay(5000);

    // record xx secondes
    // note midi : 64
    MIDI_note(64);
    bear_delay(5000);

    // play xx secondes
    // note midi : 65

    MIDI_note(65);
    bear_delay(5000);

  }

}

//send MIDI message
void MIDI_note(int note) {
  Serial.write(144);//send note on
  Serial.write(note);//send pitch data
  Serial.write(100);//send velocity data
  delay(100);
  Serial.write(128);//send note off command
  Serial.write(note);//send pitch data
  Serial.write(100);//send velocity data
  delay(100);


}
