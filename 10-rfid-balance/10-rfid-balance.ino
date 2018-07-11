/*
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
int locale;
unsigned long chrono;


//------------------ config -------
const long timeout = 18000; // en ms
//---------------------------------


void setup() {
  bear_init();
  pinMode(switchPin, INPUT);
  Serial.println("play 10-bkg.png");
  Serial.println("loop 10-idle.h264");
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // attente carte rfid
  if (bear_has_card())
  {

    // lit la langue
    locale = bear_get_locale();
    bear_delay(50);
    bear_stop();


    // stocke temps de départ
    chrono = millis();

    // joue la séquence départ (1)
    if (locale == LOCALE_FR)
    {
      Serial.println("play 10-action1-fr.h264");
    }

    if (locale == LOCALE_EN)
    {
      Serial.println("play 10-action1-en.h264");
    }

    if (locale == LOCALE_DE)
    {
      Serial.println("play 10-action1-de.h264");

    }

    if (locale == LOCALE_NL)
    {
      Serial.println("play 10-action1-nl.h264");
    }

    bear_delay(1000);

    // attends bouton on pour jouer séquence suivante et clignote

    for (int i = 2; i < 6; i++)
    {
      // reste bloqué tant que le bouton n'est pas pressé
      while (digitalRead(switchPin) == LOW)
      {
        analogWrite(5, 255);
        bear_delay(50);

        analogWrite(5, 0);
        bear_delay(50);

        if (millis() - chrono >= timeout)
        {
          Serial.println("timeout");
          Serial.println("loop 10-idle.h264");
          return;
        }
      }

      // relance le timeout
      chrono = millis();


      String command = "play 10-action";
      command = command + i + "-";

      if (locale == LOCALE_FR)
      {
        command = command + "fr";
      }

      if (locale == LOCALE_EN)
      {
        command = command + "en";
      }

      if (locale == LOCALE_DE)
      {
        command = command + "de";
      }

      if (locale == LOCALE_NL)
      {
        command = command + "nl";
      }

      command = command + ".h264";

      Serial.println(command);

      bear_delay(200); // TODO

    }
    bear_delay(7500); // à tester TODO
    
    Serial.println("loop 10-idle.h264");

  }


}




