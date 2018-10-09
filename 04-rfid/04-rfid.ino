/*

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)


   RELAIS :
   - Blanc : GND
   - Rose : VCC
   - Brun : Relais 1
   - Vert : Relais 2
   - Gris : Relais 3
   - Jaune : Relais 4

*/

const char MODULE_NAME[] = "04-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier

int relay = 0;
int relay_pin[4] = {RELAY_1, RELAY_2, RELAY_3, RELAY_4};
unsigned long timeout = 0;

void setup() {
  bear_init();

  pinMode (RELAY_1, OUTPUT);
  pinMode (RELAY_2, OUTPUT);
  pinMode (RELAY_3, OUTPUT);
  pinMode (RELAY_4, OUTPUT);

  //coupe tous les relais sauf 1
  digitalWrite (RELAY_1, HIGH);
  digitalWrite (RELAY_2, LOW);
  digitalWrite (RELAY_3, LOW);
  digitalWrite (RELAY_4, LOW);

  delay(500);
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {

    bear_stop();

    // coupe tous les relais
    digitalWrite (RELAY_1, LOW);
    digitalWrite (RELAY_2, LOW);
    digitalWrite (RELAY_3, LOW);
    digitalWrite (RELAY_4, LOW);


    relay++;

    // selectionne le relais suivant
    if (relay  == 4) {
      relay = 0;
    }

    //allume le relais selectionné
    digitalWrite (relay_pin[relay], HIGH );
    Serial.print("Enable relay ");
    Serial.println(relay);

    //bling bling
    bear_led_blink();
    bear_delay(100);
  }

  bear_delay(100);



  if (millis() > timeout + 10000)
  {
    software_Reboot();
    timeout = millis();
  }

}



void software_Reboot()
{
  wdt_enable(WDTO_15MS);
  delay(50);
}
