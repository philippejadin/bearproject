

/*

   Module de base à modifier pour les autres modules


   Stockage RFID :

   Sector >  Block >  Bytes
   16 secteurs de 4 blocs chacun (secteurs 0..15) > contenant 16 octets
   Nous allons utiliser le secteur 1 bloc 4 5 6
   et si nécessaire secteur 2 block 8 9 10

   N'utiliser que ceux qui n'ont rien ci-dessus (ceux où tout est à 0)

   block 4 = locale
   Valeurs :
   0 = fr
   1 = nl
   2 = en
   3 = de

   PINS arduino utilisées :

   - serial : 0, 1
   - leds : 3
   - mosfet et/ou relais : 4, 5, 6, 7
   - rfid : 9, 10, 11, 12, 13
   - i2c : A4 (SDA), A5 (SCL)



*/

#include <SPI.h>
#include <MFRC522.h>
#include <avr/wdt.h>
#include <FadeLed.h>


#define RST_PIN         9           // pin reset du lecteur rfid
#define SS_PIN          10          // pins slave select du lecteur rfid
#define LED_PIN         3

FadeLed led(3); //Fading status LED on pin 5

const char MODULE[]    =      "00-base"; // à changer pour chaque module, pour l'identifier facilement

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance


int ledLow = 20; // led semi allumée
int ledHigh = 200; // led full power (255 = réel maximum)

void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(MODULE);    //affiche le nom du module en debug série
  //pinMode(LED_PIN, OUTPUT);   // init pin leds
  led.setTime(1000, true);
  led.noGammaTable();
}



//*****************************************************************************************//
void loop() {

  // wdt_enable(WDTO_2S); // active le watchdog pour rebooter l'arduino si pas de réponse après 2 secondes
  FadeLed::update();

  if (led.done())
  {
    if (led.get() == 50)
    {
      led.set(255);
    } else
    {
      led.set(50);
    }
  }

}


