/*

   Affiche en liaison série la locale encodée sur la carte mifare
   
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

*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance


void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read locale"));    //shows in serial that it is ready to read
}



//*****************************************************************************************//
void loop() {

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  // Cette clé est utilisée pour s'authentifier avec la carte mifare. Mais nos n'allons pas utiliser cette fonctionalité (ou plutôt : nous allons garder la clé d'origine pour ne pas compliqer)
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;



  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Look for new cards
  if ( mfrc522.PICC_IsNewCardPresent()) {

    // Select one of the cards
    if ( mfrc522.PICC_ReadCardSerial()) {


      Serial.println(F("**Card Detected:**"));

      //-------------------------------------------
      mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card
     //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex


      // on prépare des variables qui vont recevoir toutes les infos, dont un tableau, buffer, qui recevra les données du block sélectionné
      byte buffer1[18];

      block = 4; // numéro du block, le prénom est stocké dans le 4, le nom dans le 1
      len = 18; // on s'en fou (je crois), on peut toujours laisser 18


      // on s'authentifie avec l'uid de la carte trouvé ci-dessus ainsi qu'avec la clé initialisée ci-dessus aussi
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("#Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }


      // là on lit les données
      status = mfrc522.MIFARE_Read(block, buffer1, &len);
      if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }

      Serial.print(F("Locale code is "));
      Serial.println(buffer1[0]);

      if (buffer1[0] == 0)
      {
        Serial.println(F("Français"));
        Serial.println(F("play fr.h264"));
      }

      if (buffer1[0] == 1)
      {
        Serial.println(F("Neederlands"));
        Serial.println(F("play nl.h264"));
      }

      if (buffer1[0] == 2)
      {
        Serial.println(F("English"));
        Serial.println(F("play en.h264"));
      }

      if (buffer1[0] == 3)
      {
        Serial.println(F("Deutsh"));
        Serial.println(F("play de.h264"));
      }

      

      //----------------------------------------

      Serial.println(F("\n**End Reading**\n"));

      delay(1000); //change value if you want to read cards faster

      // ne pas oublier ceci quand tout est fini :
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();

    }

  }


}

