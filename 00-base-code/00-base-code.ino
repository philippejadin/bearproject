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

#define RST_PIN         9           // pin reset du lecteur rfid
#define SS_PIN          10          // pins slave select du lecteur rfid
#define LED_PIN         3

const char MODULE[]    =      "00-base"; // à changer pour chaque module, pour l'identifier facilement

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance


int ledLow = 15; // led semi allumée
int ledHigh = 200; // led full power (255 = réel maximum)

void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(MODULE);    //affiche le nom du module en debug série
  pinMode(LED_PIN, OUTPUT);   // init pin leds

}



//*****************************************************************************************//
void loop() {

  analogWrite(LED_PIN, ledLow);


  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  // Cette clé est utilisée pour s'authentifier avec la carte mifare. Mais nous n'allons pas utiliser cette fonctionalité (ou plutôt : nous allons garder la clé d'origine pour ne pas compliqer)
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;



  // on prépare des variables qui vont recevoir toutes les infos, dont un tableau, data, qui recevra les données du block sélectionné

  MFRC522::StatusCode status;
  byte data[72];
  byte block = 4; // numéro du block, que l'on interroge, ici la locale
  byte len = sizeof(data);

  //-------------------------------------------

  // Look for new cards
  if ( mfrc522.PICC_IsNewCardPresent()) {

    // Select one of the cards
    if ( mfrc522.PICC_ReadCardSerial()) {

      analogWrite(LED_PIN, ledHigh);


      //-------------------------------------------
      //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card
      //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

      // on s'authentifie avec l'uid de la carte trouvé ci-dessus ainsi qu'avec la clé initialisée ci-dessus aussi
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        Serial.println(F("REBOOTING"));
        wdt_enable(WDTO_60MS); // active le watchdog pour rebooter l'arduino
        delay(300);
        return;
      }


      // là on lit les données
      len = sizeof(data);
      status = mfrc522.MIFARE_Read(block, data, &len);
      len = sizeof(data);
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        Serial.println(F("REBOOTING"));
        wdt_enable(WDTO_60MS); // active le watchdog pour rebooter l'arduino
        delay(300);
        return;
      }

      // Cloturer au plus vite la lecture de la carte
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();


      // en fonction de la locale on écrit en série ce que l'on veut faire :
      if (data[0] == 0)
      {
        Serial.println(F("play fr.h264"));
      }

      if (data[0] == 1)
      {
        Serial.println(F("play nl.h264"));
      }

      if (data[0] == 2)
      {
        Serial.println(F("play en.h264"));
      }

      if (data[0] == 3)
      {
        Serial.println(F("play de.h264"));
      }

      /*
            delay(100);
            analogWrite(LED_PIN, 0);
            delay(100);
            analogWrite(LED_PIN, ledHigh);
            delay(100);
            analogWrite(LED_PIN, 0);
            delay(100);
            analogWrite(LED_PIN, ledHigh);
            delay(100);
            analogWrite(LED_PIN, 0);
            delay(100);
            analogWrite(LED_PIN, ledHigh);
            delay(100);
            analogWrite(LED_PIN, ledLow);


            delay(500); // attente totale : 1300 ms
      */

    }

  }


}

