 
#include <SD.h>
#include <PN532.h>
#include <SPI.h>
#include <Wire.h>
#include <Ethernet.h>
const int chipSelect = 4;
int buzzer = 3;
#define PN532_CS 9
#define SCK  13  
#define MOSI 11  
#define MISO 12
#define SS 9
File myFile;
PN532 nfc(PN532_CS);
File dataFile;
#define  NFC_DEMO_DEBUG 1
char buffer[50];



void setup(void) {
  pinMode(buzzer, OUTPUT);
   Serial.begin(9600);
   Serial.println("Bradley But");
   Serial.println("No arduinos were euthanised during development of this product");
   SPI.setDataMode(SPI_MODE1);
#ifdef NFC_DEMO_DEBUG
    Serial.print("Initializing SD card...");
    analogWrite(buzzer, 20);
    delay(70);
    analogWrite(buzzer, 0);
    delay(30);
    analogWrite(buzzer, 20);
    delay(70);
    analogWrite(buzzer, 0);
        delay(30);
    analogWrite(buzzer, 20);
    delay(70);
    analogWrite(buzzer, 0);
#endif
  pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
#ifdef NFC_DEMO_DEBUG
    Serial.println("Card failed, or not present");
#endif
    return;
  }
  Serial.println("card initialized.");
  //++++++++++++++++++++++++++++++++++++++++++++++-- SD bestand openen--++++++
   dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (dataFile) {
    Serial.print("Writing to datalog.txt...");
    dataFile.println("Reboot");
	// close the file:
    dataFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  //++++++++++++++++++++++++++++++++++++++++++++++-- SD bestand openen--++++++
  }
   
#ifdef NFC_DEMO_DEBUG
  Serial.println("Hello!");
#endif
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
#ifdef NFC_DEMO_DEBUG  
  if (! versiondata)
    Serial.print("Didn't find PN53x board");
#endif
  
#ifdef NFC_DEMO_DEBUG
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); 
  Serial.println(versiondata & 0xFF, HEX);
#endif
  nfc.SAMConfig();
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if(!dataFile)
#ifdef NFC_DEMO_DEBUG
    Serial.println("Couldn't open datafile on sd card"); 
#endif
}


void loop(void) {
    nfc.begin();
  uint32_t id;
  //++++++++++++++++++++++++++++++++++--zoeken naar de nfc--++++++++++++++++++++++
  id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);

  if (id != 0) 
  analogWrite(buzzer, 20);
  delay(150);
  analogWrite(buzzer, 0);

#ifdef NFC_DEMO_DEBUG
    Serial.print("Read card #"); 
    Serial.println(id);
#endif
    //++++++++++++++++++++++++++++++++--schrijfen naar SD kaart--+++++++++++++++++
   
 
 /* uint8_t keys[]= { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };// default key of a fresh card
    for(uint8_t blockn=0;blockn<64;blockn++) 
    {
      if(nfc.authenticateBlock(1, id ,blockn,KEY_A,keys)) //authenticate block blockn
      {
        //if authentication successful
        uint8_t block[16];
        //read memory block blockn
        if(nfc.readMemoryBlock(1,blockn,block))
        {
#ifdef NFC_DEMO_DEBUG
          //if read operation is successful
          for(uint8_t i=0;i<16;i++)
          {
            //print memory block
            Serial.print(block[i],HEX);
            if(block[i] <= 0xF)
            
            #endif
        **/  
               
            
            
    {
        String strLab = "ID card =#";
    dtostrf(id,1,0,buffer);
    String strOut = strLab + buffer;
    Serial.println(strOut);
    SD.begin(4); 
    dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(strOut);
    delay(10);
    dataFile.close();
   delay(10); 
   
  }
    }
          }     //}}}}}

