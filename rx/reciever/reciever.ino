#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<stdlib.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10); // RX, TX

#define CE_PIN   7
#define CSN_PIN 8

const int buzz = 2 ;
const int red = 5 ;
const int green = 3 ;
const int blue = 4 ;

int wrongTime = 0;
const uint64_t pipe = 0xE8E8F0F0E1LL ;

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
unsigned int joystick[1];

void setup()
{
  pinMode(buzz, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(buzz, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);

  mySerial.begin(9600);
  char ATcscs[] = {'A', 'T', '+', 'C', 'S', 'C', 'S', '=', '"', 'G', 'S', 'M', '"'};
  mySerial.println(ATcscs);
  Serial.begin(9600);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  Serial.println("setup has done");
  delay(1000);
}

void loop()
{

  if ( radio.available() )
  {
    //Serial.println("nrf available...");
    radio.read( joystick, sizeof(joystick) );
    Serial.print("input is  = ");
    Serial.println(joystick[0]);
    if (joystick[0] == 11)
    {
      if (wrongTime >= 3)
    {
      digitalWrite(red, LOW);
      digitalWrite(buzz, LOW);
      delay(100);
    }
      digitalWrite(green, HIGH);
      digitalWrite(buzz, HIGH);
      delay(1000);
      digitalWrite(buzz, LOW);
      digitalWrite(green, LOW);
      wrongTime = 0;
    }
    else if (joystick[0] == 12)
    {
      if (wrongTime == 3)
      {
        digitalWrite(red, HIGH);
        digitalWrite(buzz, HIGH);
        mySerial.println("AT+CMGF=1");
        delay(500);
        mySerial.println();
        mySerial.print("AT+CMGS=\""); // send the SMS number
        mySerial.print("+989178700187");
        mySerial.println("\"");
        delay(1000);
        mySerial.print(" DANGER Alarm  :( "); // SMS body
        delay(500);
        mySerial.write(0x1A);
        Serial.print("sms sent");
      }

      else {
        digitalWrite(blue, HIGH);
        digitalWrite(buzz, HIGH);
        delay(450);
        digitalWrite(buzz, LOW);
        digitalWrite(blue, LOW);
        delay(100);
        digitalWrite(buzz, HIGH);
        digitalWrite(blue, HIGH);
        delay(450);
        digitalWrite(buzz, LOW);
        digitalWrite(blue, LOW);
        wrongTime++ ;
      }
    }
  }
}

