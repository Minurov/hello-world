

#include <EEPROM.h>
#include <ESP8266WiFi.h>
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


void setup() {
bool errase=false; // флаг стирания памяти
WiFi.softAPConfig(local_IP, gateway, subnet);
EEPROM.begin(1000);
Serial.begin(115200);

  if ( errase ){
  for (int i = 0; i < 1000; i++) {
    EEPROM.write(i, 0);
  }
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  EEPROM.end();
  }
}

void loop() {
for( int i=0; i<1000; i++ ) {
    int volt=(analogRead(A0)/2)-256; //ЗАГРУБЛЯЕМ в 2 раза точность
                                     // и отнимаем не измеряемую половину
    if(volt <=256){
      EEPROM.write(i, 1);
    }else {EEPROM.write(i, 0);}
    //---------------------------    
delay(1000*60*15);




    //---------------------------
}

  // stop
   for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(4, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(4);
  }
  while(1){}//висим
  
}
