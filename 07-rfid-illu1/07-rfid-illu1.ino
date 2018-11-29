/*


   Cette version utilise juste une boucle for

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

const char MODULE_NAME[] = "07-rfid-illu1"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier
unsigned long timeout;


void setup() {
  bear_init();
  randomSeed(analogRead(0));
  //timeout=10000+(random(5)*1000);// pour les 3 rfid du fond
  //ou
  timeout = random(3000, 6000); // entre 2 et 6 secondes / pour la rfid d'entrée
  analogWrite(LED_PIN, 0);
  yeux();

}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  if (millis() > timeout) {
    software_Reboot();
  }

  // Attend une carte RFID
  carte();
  delay(100);
}


void carte()
{
  if (bear_has_card()) {
    bear_stop();
    analogWrite(LED_PIN, 10);
    


    Serial.println("enable mosfet");
    for (int i = 0; i < 255; i++)
    {
      analogWrite(MOSFET_1, i);

      bear_delay(random(2, 10));
    }

    for (int i = 255; i > 10; i--)
    {
      analogWrite(MOSFET_1, i);
      bear_delay(random(2, 15));
    }

    analogWrite(MOSFET_1, 0);
    analogWrite(LED_PIN, 0);
    Serial.println("disable mosfet");
  }
}

void yeux()
{
  for (int i = 0; i < 10; i++)
  {
    carte();
    analogWrite(LED_PIN, i);
    bear_delay(100);
  }
 
  for (int i = 10; i > 0; i--)
  {
    carte();
    analogWrite(LED_PIN, i);
    bear_delay(100);
  }
  analogWrite(LED_PIN, 0);
}

void software_Reboot()
{
  Serial.println("reboot");
  wdt_enable(WDTO_15MS);
  delay(50);
}
