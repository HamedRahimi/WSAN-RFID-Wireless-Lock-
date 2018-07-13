#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN  7
#define CSN_PIN 8

String a = "67971141003284121112101584852484832453277105102971141019579110101408353484110831011141051011153278117109981011145854536552506753651067971141003284121";
String b = "67971141003284121112101584852484832453277105102971141019579110101408353484110831011141051011153278117109981011145865545250506551661067971141003284121";

RF24 radio(CE_PIN, CSN_PIN); // Create a R
SoftwareSerial RC522(9, 10); // RX, TX


const uint64_t pipe = 0xE8E8F0F0E1LL;
unsigned int joystick[1];
String tag="" ;
int t ;

void setup() {
  Serial.begin(115200);
  RC522.begin(115200);
  radio.begin();
  radio.openWritingPipe(pipe);
  delay(500);
  Serial.println("setup finished");
}


void loop() {

  while (RC522.available()) {
     tag += String(RC522.read());
     t=1;
  }
    if(t==1)
    {
      
    if(tag.length()==149)
    {
       Serial.println(tag); 
    if (tag == a )
    {
      joystick[0] = 11 ;
      Serial.println("Welcome ,Your Tag is OK ");
      delay(500);
      radio.write( joystick, sizeof(joystick) );
    } 
    else if (tag == b )
    {
      joystick[0] = 11 ;
      Serial.println("Welcome ,Your Tag is OK ");
      delay(500);
      radio.write( joystick, sizeof(joystick) );
    }
   
    else
    {
      joystick[0] = 12 ;
      Serial.println("GFY ,Your Tag is NOT OK ");
      delay(500);
      radio.write( joystick, sizeof(joystick) );
    }
    }
    t=0;
    tag="";
    // RC522.flush();
    delay(500);
    }
}
