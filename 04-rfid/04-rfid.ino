
/*
   Module de base à modifier pour les autres modules

   PINS arduino utilisées :
   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)
*/

const char MODULE_NAME[] = "04-rfid"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch


#include <bearlib.h> // à inclure en dernier

const int n_max_relay = 3;//nbre de relay
int n_relay = 0;
int relay_pin[4] = {RELAY_1, RELAY_2, RELAY_3, RELAY_4};

void setup() {
  bear_init();
  Serial.println("loop 01-fr-idle.mp4");
  pinMode (RELAY_1, OUTPUT);
  pinMode (RELAY_2, OUTPUT);
  pinMode (RELAY_3, OUTPUT);
  pinMode (RELAY_4, OUTPUT);
}


//*****************************************************************************************//
void loop() {

  wdt_reset(); //  à appeller régulièrement, au moins toutes les 8 secondes sinon reboot

  bear_led_standby(); // les leds se mettent à clignoter doucement, mode attente,


  // Attend une carte RFID
  if (bear_has_card()) {
    //coupe tous les relais
    for (int i = 0; i < n_max_relay; i++) {
      digitalWrite (relay_pin[i], LOW);
    }

   
    // selectionne le relais suivant
    if (n_relay < n_max_relay) {
      n_relay++;
    }
    else {
      n_relay = 0;
    }
    //allume le relais selectionné
    digitalWrite (relay_pin[n_relay], HIGH );
    Serial.print("Enable relay ");
    Serial.println(n_relay);

    //bling bling
    bear_led_blink();
    bear_stop();
  }

}
