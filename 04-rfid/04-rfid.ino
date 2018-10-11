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

int relay = 4;
int changement = 100;
unsigned long timeout = 60000;
float R;
void setup() {
  bear_init();

  pinMode (RELAY_1, OUTPUT);
  pinMode (RELAY_2, OUTPUT);
  pinMode (RELAY_3, OUTPUT);
  pinMode (RELAY_4, OUTPUT);

  randomSeed(analogRead(0));
  //coupe tous les relais sauf 1
  relayOff();
  delay(100);

  relay = random(4) + 4;
  
  digitalWrite (relay, HIGH);
  Serial.println("hello");
}


//*****************************************************************************************//
void loop() {

  //wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot
  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,
  // Attend une carte RFID
  if (bear_has_card()) {

    bear_stop();
    //bling bling
    bear_led_blink();

    Serial.println ("carte");
    relayOff(); // coupe tous les relais

    relay++;

    delay(100);

    // selectionne le relais suivant
    if (relay  > 7) {
      wdt_reset();
      relay = 4;
      digitalWrite (relay, HIGH);
      delay(100);
      digitalWrite (7, LOW);
      delay(100);
    }
    else {

      wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot
     
      digitalWrite (relay - 1, LOW);
      delay(100);
      digitalWrite (relay, HIGH);
      delay(100);
      
    }
    Serial.print("pin relais n° ");
    Serial.println(relay);


  }
}



void relayOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite (4 + i, LOW);
    delay(100);
  }
}
