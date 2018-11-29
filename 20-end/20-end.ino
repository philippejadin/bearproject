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

const char MODULE_NAME[] = "20-end"; // à changer pour chaque module, pour l'identifier facilement, à mettre en début de sketch

const unsigned int TRIG_PIN = 2;
const unsigned int ECHO_PIN = 4;

//------------------ config ----------
int min_distance = 30; // distance en dessous de laquelle on déclenche (en cm)
//------------------------------------


void setup() {
  Serial.begin(9600);

  Serial.println(MODULE_NAME);
  Serial.print("Distance de declenchement : ");
  Serial.println(min_distance);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //Serial.println("play 00-start.wav"); // son de démarage pour confirmer que tout est ok
  Serial.println("play 20-growl.wav");
  delay(1000);
}


//*****************************************************************************************//
void loop() {

  // interoge l'ultrason
  if (distance() < min_distance)
  {
    Serial.println("play 20-growl.wav");
    Serial.println(distance());
    delay(3000);
  }

  delay(20);

  //Serial.println(distance());

}

int distance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration / 29 / 2;

  return distance;
}


