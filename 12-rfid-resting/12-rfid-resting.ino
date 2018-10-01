/*

  Cette version utilise fadeled

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)

   Cablage mosfet :
  - blanc : GND
  - brun : VCC
  - vert : mosfet 1 / pin 5
  - jaune : mosfet 2 / pin 6

*/

const char MODULE_NAME[] = "12-rfid-resting"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch
#include <bearlib.h> // à inclure en dernier

//----- config me
const int delay_battement = 5000; // ms
const int nbr_battement = 3;
const int coeur_active = 4; // intensité du coeur quand il est actif entre 2 battements
//-----------


void coeur()
{
  for (int battement = 0; battement <= nbr_battement; battement++)
  {

    Serial.println("play 12-resting.wav");

    // battement en fondu in:
    for (int intensite = coeur_active; intensite < 255; intensite = intensite + 8)
    {
      analogWrite (MOSFET_1, intensite);
      analogWrite (3, intensite);
      delay(2);
    }

    // battement en fondu out :
    for (int intensite = 255; intensite >= coeur_active; intensite--)
    {
      analogWrite (MOSFET_1, intensite );
      analogWrite (3, intensite );
      delay(1); // ici on peut faire un fondu plus lent
    }

    bear_delay(delay_battement);
  }

  analogWrite (MOSFET_1, 0);


}


void setup() {
  bear_init();
  Serial.println("play 00-start.wav"); // son de démarage pour confirmer que tout est ok
  delay(1000);
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby();

  // Attend une carte RFID
  if (bear_has_card()) {
    bear_stop();
    coeur();
  }
}


