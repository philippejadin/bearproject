/*
   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

  Numéro de block : 6

  Position :
  08-rfid-panda :  1
  08-rfid-lippu : 2
  08-rfid-malais : 3
  08-rfid-collier : 4
  08-rfid-lunette : 5
  08-rfid-noir : 6
  08-rfid-polaire : 7
  08-rfid-brun : 8

*/

const char MODULE_NAME[] = "08-rfid-result"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
byte data[18]; // va contenir toutes les données
String filename;
String filecount;
int count = 0;


#include <bearlib.h> // à inclure en dernier

void setup() {
  bear_init();
  randomSeed(analogRead(0));
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot
  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,

  // Attend une carte RFID
  if (bear_has_card()) {
    int data_read = bear_read_block(6, data);
    int locale = bear_get_locale();
    bear_stop();

    if (locale && data_read) // on ne lance la machine que si on a bien une locale ET les données de la carte
    {
      // construction du nom de fichier en regardant chaque case si elle contient un 1 ou pas

      count = 0;
      filename = "";
      filecount = "";

      for (int i = 1; i < 9; i++)
      {
        if (data[i] == 1)
        {
          filecount = filecount + i;
          count ++;
        }
      }


      if (count == 0) // si rien sélectionné, tuto pour expliquer ce qu'il faut en sélectionner au moins un
      {
        filename = "08-wrong-";
        // ajout de la locale
        if (locale == LOCALE_FR)
        {
          filename = filename + "fr";
        }
        if (locale == LOCALE_EN)
        {
          filename = filename + "en";
        }
        if (locale == LOCALE_NL)
        {
          filename = filename + "nl";
        }
        if (locale == LOCALE_DE)
        {
          filename = filename + "de";
        }
        filename = filename + ".h264";
      }
      else if (count < 4)  // si max 3 animaux sélectionnés on génère le nom de fichier :
      {
        filename = "08-result" + filecount;

        // ajout de la locale
        if (locale == LOCALE_FR)
        {
          filename = filename + "-fr.png";
        }
        if (locale == LOCALE_EN)
        {
          filename = filename + "-en.png";
        }
        if (locale == LOCALE_NL)
        {
          filename = filename + "-nl.png";
        }
        if (locale == LOCALE_DE)
        {
          filename = filename + "-de.png";
        }
      }
      else // sinon on tire au sort un animal chimérique (oui, chimérique!)
      {
        filename = "08-resultmore";
        filename = filename + random(1, 8);

        // ajout de la locale
        if (locale == LOCALE_FR)
        {
          filename = filename + "-fr.png";
        }
        if (locale == LOCALE_EN)
        {
          filename = filename + "-en.png";
        }
        if (locale == LOCALE_NL)
        {
          filename = filename + "-nl.png";
        }
        if (locale == LOCALE_DE)
        {
          filename = filename + "-de.png";
        }
      }

      Serial.println("play " + filename);
      bear_led_blink();
      bear_delay(2000);
    }
  }
}
