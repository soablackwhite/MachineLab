#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#define SHIELD_RESET  -1
#define SHIELD_CS     7
#define SHIELD_DCS    6
#define CARDCS 4
#define DREQ 3

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  
void setup() {
  if(!musicPlayer.begin()) while(1);
  if(!SD.begin(CARDCS)) while (1);
  Serial.begin(9600);
  musicPlayer.setVolume(20,20);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  pinMode(8,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  musicPlayer.startPlayingFile("/track001.mp3");
  while(musicPlayer.playingMusic){
    digitalWrite(13,HIGH);
  }
  digitalWrite(13,LOW);
}
