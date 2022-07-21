#include <SPI.h> // This library allows you to communicate with SPI devices
#include <MFRC522.h> // This library is to Read/Write a RFID Card or Tag 
#include <Servo.h> // This library allows to control servo motor
 
#define SS_PIN 10
#define RST_PIN 9
#define BUZZER 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "AA E0 EB AE") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    myServo.write(80);
    delay(5000);
    myServo.write(0);
  }

else if (content.substring(1) == "CC B0 EB DE") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    myServo.write(80);
    delay(5000);
    myServo.write(0);
  }

else if (content.substring(1) == "9A 70 3D B4") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    myServo.write(80);
    delay(5000);
    myServo.write(0);
  }

else if (content.substring(1) == "CC 24 8C 18") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    myServo.write(80);
    delay(5000);
    myServo.write(0);
  }

 
 else   {
    Serial.println(" Access denied");
    digitalWrite(2, HIGH);
    delay(1000);
    noTone(BUZZER);
  }
} 
