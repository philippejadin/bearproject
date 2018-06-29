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


#include <bearlib.h> // à inclure en dernier

void setup() {
  bear_init();
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot
  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,

  // Attend une carte RFID
  if (bear_has_card()) {

    // code exemple qui rempli la position 1 et 2
    //bear_write(6, 1, 1);
    //bear_write(6, 2, 1);

    bear_read_block(6, data);
    int locale = bear_get_locale();
    bear_stop();

    // construction du nom de fichier en regardant chaque case si elle contient un 1 ou pas
    filename = "08-result";
    for (int i = 1; i < 9; i++)
    {
      if (data[i] == 1)
      {
        filename = filename + i;
      }
    }

    // ajout de la locale
    if (locale == LOCALE_FR)
    {
      filename = filename + "-fr.h264";
    }
    if (locale == LOCALE_EN)
    {
      filename = filename + "-en.h264";
    }
    if (locale == LOCALE_NL)
    {
      filename = filename + "-nl.h264";
    }
    if (locale == LOCALE_DE)
    {
      filename = filename + "-de.h264";
    }

    Serial.println(filename);

    bear_led_blink();
  }



}
