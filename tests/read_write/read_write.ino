/*
   Initial Author: ryand1011 (https://github.com/ryand1011)

   Commentaires ajoutés par Philippe Jadin

   En gros ce sketche demande à l'utilisateur d'entrer un nom (liaison série) et puis il l'écrit sur une carte mifare. 
   C'est le meilleur exemple (le plus simple) de la librairie que je commente ici




   Reads data written by a program such as "rfid_write_personal_data.ino"

   See: https://github.com/miguelbalboa/rfid/tree/master/examples/rfid_write_personal_data

   Uses MIFARE RFID card using RFID-RC522 reader
   Uses MFRC522 - Library
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15


  [--------------------------Exemple d'un dump mémoire-------------------------]
    -----------------------Secteur 0-------------------------
    Bloc 0 : 8E 02 6F 66 85 08 04 00 62 63 64 65 66 67 68 69  ?.of?...bcdefghi
    Bloc 1 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 2 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 3 : 00 00 00 00 00 00 FF 07 80 69 FF FF FF FF FF FF  ......ÿ.?iÿÿÿÿÿÿ
    -----------------------Secteur 1-------------------------
    Bloc 4 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 5 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 6 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 7 : 00 00 00 00 00 00 FF 07 80 69 FF FF FF FF FF FF  ......ÿ.?iÿÿÿÿÿÿ
    -----------------------Secteur 2-------------------------
    Bloc 8 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 9 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................  << utilisable
    Bloc 11: 00 00 00 00 00 00 FF 07 80 69 FF FF FF FF FF FF  ......ÿ.?iÿÿÿÿÿÿ
    [...]


   Sector >  Block >  Bytes
   16 secteurs de 4 blocs chacun (secteurs 0..15) > contenant 16 octets
   Nous allons utiliser les block 4, 5, 6, 8, 9, 10

   N'utiliser que ceux qui n'ont rien ci-dessus (ceux où tout est à 0)

*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//*****************************************************************************************//
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("# Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
}


/*
Ceci est nickel en fait : 
MFRC522::StatusCode MFRC522::MIFARE_Read(  byte blockAddr,   ///< MIFARE Classic: The block (0-0xff) number. MIFARE Ultralight: The first page to return data from.
                      byte *buffer,   ///< The buffer to store the data in
                      byte *bufferSize  ///< Buffer size, at least 18 bytes. Also number of bytes returned if STATUS_OK.
                    )
il ne retourne pas la valeur, il la stocke dans buffer!
il retourne un status par contre

*/



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
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return; 
    // return quitte la boucle loop qui se relance juste après. 
    // En d'autres mots la suite du code n'est pas exécutée tant qu'il n'y a pas de carte présentée. 
    // On pourrait mettre deux if impbriqués ce qui permettrait de gérer d'autres choses si nécessaire, commme les leds
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print(F(" Name: "));

  // on prépare des variables qui vont recevoir toutes les infos, dont un tableau, buffer, qui recevra les données du block sélectionné
  byte buffer1[18];

  block = 4; // numéro du block, le prénom est stocké dans le 4, le nom dans le 1
  len = 18; // on s'en fou (je crois), on peut toujours laisser 18

  //------------------------------------------- GET FIRST NAME

  // on s'authentifie avec l'uid de la carte trouvé ci-dessus ainsi qu'avec la clé initialisée ci-dessus aussi
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
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

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32) // je suppose que 32 est un code de fin de chaine. Ah non, c'est le code d'un espace.
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
  }


  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));

  delay(1000); //change value if you want to read cards faster

  // ne pas oublier ceci quand tout est fini :
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
//*****************************************************************************************//
