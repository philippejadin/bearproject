
/*
   Ce module communique avec un axoloti en midi.
   En envoyant différentes notes midi,
   - il déclenche l'enregistrement (note midi 64)
   - la reproduction déformée du son (note midi 65)
   - il joue différents sons d'introduction (aide dans les différentes langues).

    // 60 = fr
    // 61 = nl
    // 62 = en
    // 63 = de

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

   Ce module est connecté en midi à la carte axoloti
    https://www.arduino.cc/en/Tutorial/Midi

  Connecteur midi :
  - digital in 1 connected to MIDI jack pin 5 : cable jaune
  - MIDI jack pin 2 connected to ground : cable blanc
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor : cable brun


  Connection micro et axoloti
  Il s'agit d'un microphone électret amplifié avec gain variable (mini pot à l'arrière) https://www.adafruit.com/product/1063
  Le gros jack est cablé comme ceci :
  Blanc : masse
  Jaune : left
  Vert : right
  Brun : sort sur un jumper à connecter sur une sortie VCC de l'axoloti en direct pour alimenter le microphone


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
  if (bear_has_card())
  {

    // lecture de la langue
    locale = bear_get_locale();
    bear_stop();


    // jouer le son d'explication selon la langue
    // note midi
    // 60 = fr
    // 61 = nl
    // 62 = en
    // 63 = de

    if (locale)
    {
      if (locale == LOCALE_FR)
      {
        note(60);
      }

      if (locale == LOCALE_NL)
      {
        note(61);
      }

      if (locale == LOCALE_EN)
      {
        note(62);
      }

      if (locale == LOCALE_DE)
      {
        note(63);
      }

      bear_led_blink();

      bear_delay(1000);

      // active l'effet pendant 10 secondes
      note_on(64);
      analogWrite(LED_PIN, LED_HIGH);
      bear_delay(10000);
      analogWrite(LED_PIN, LED_LOW);
      note_off(64);
    }

  }

}

//send MIDI message
void note(int note) {
  Serial.write(144);//send note on
  Serial.write(note);//send pitch data
  Serial.write(100);//send velocity data
  delay(10);
  Serial.write(128);//send note off command
  Serial.write(note);//send pitch data
  Serial.write(100);//send velocity data
  delay(10);
}

void note_on(int note)
{
  Serial.write(144);//send note on
  Serial.write(note);//send pitch data
  Serial.write(100);//send velocity data
  delay(10);
}


void note_off(int note)
{
  Serial.write(128);//send note off command
  Serial.write(note);//send pitch data
  Serial.write(100);//send velocity data
  delay(10);
}


