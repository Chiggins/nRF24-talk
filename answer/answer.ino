#include <SPI.h>
#include <AESLib.h>
#include "nRF24L01.h"
#include "macList.h"
#include "answer_strings.h"

#define CSN 10
#define CE 9
#define IRQ 8

#define MAX_RECORDS 50
#define MAC_SIZE 3
#define DATA_SIZE 16
#define PACKET_SIZE (MAC_SIZE + DATA_SIZE)
#define NUM_MACS (sizeof(mac) / MAC_SIZE)

#define STRING(x) (strcpy_P(tmp_string, (char *)x))
#define PRINT_STRING(y) (Serial.println(STRING(y)))

byte clickerMasterMAC[MAC_SIZE] = { 0x56, 0x34, 0x12 };
byte myMAC[MAC_SIZE] = { 0x99, 0x88, 0x77 };
byte oppositeMyMAC[MAC_SIZE] = { 0x77, 0x88, 0x99 };

struct {
  byte MAC[MAC_SIZE];
  byte answer[1];
} record[MAX_RECORDS];

int numAnswers;
byte maxAnswer;
byte channel;
char string[20];
char tmp_string[50];
byte stats[256];
byte statusByte;
byte answer = '1';
byte trigger;
byte oldAnswer;
unsigned long time;

void setup() { 
 //Initialize serial and wait for port to open:
  Serial.begin(115200); 
  pinMode (CSN, OUTPUT);
  pinMode (CE, OUTPUT);
  pinMode (IRQ, INPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);
  channel = 47;
  help();
  receiveAsClickerMasterStart();
  newQuestion();
  time = millis();
  PRINT_STRING(FreeMemory);
  Serial.println(freeRam());
} 

void serialEvent(){
  byte readByte;
  
  while(Serial.available()){
    readByte = Serial.read();
           if (readByte == 'r'){
      readAllRegisters();
    } else if (readByte == 'g'){
      PRINT_STRING(TrigRandMass);
      massSendAsClickerStart();
      trigger = 'r';
    } else if (readByte == 'c'){
      while(!Serial.available());
      answer = Serial.read();
      PRINT_STRING(ChangeAnswer);
      Serial.write(answer);
      PRINT_STRING(NewLine);
    } else if (readByte == 'm'){
      PRINT_STRING(TrigMass);
      massSendAsClickerStart();
      trigger = 'm';
    } else if (readByte == 's'){
      PRINT_STRING(TrigSingle);
      massSendAsClickerStart();
      trigger = 's';
    } else if (readByte == ';'){
      break;
    } else if (readByte == 't'){
      compileStats();
      showStats();
    } else if (readByte == 'n'){
      newQuestion();
      PRINT_STRING(ClearedStats);
    } else if (readByte == 'h'){
      help();
    } else if (readByte == 'f'){
      channel = 0;
      do {
        while(!Serial.available());
        readByte = Serial.read();
        if(readByte >= '0' && readByte <= '9')
          channel = (channel * 10) + (readByte - '0');
      } while(readByte != '.');
      PRINT_STRING(ChannelSet);
      Serial.println(channel);
      newQuestion();
      PRINT_STRING(ClearedStats);
      receiveAsClickerMasterStart();
    } else if (readByte == 'a'){
      trigger = 'a';
      PRINT_STRING(AutoAnswer);
    } else if (readByte == 'd'){
      trigger = 0;
      receiveAsClickerMasterStart();
      PRINT_STRING(DefaultMode);
    } else if (readByte == 'p'){
      dumpMACs();
    } else if (readByte == 'j'){
      trigger = 'j';
      jammer();
    }
  }
}

void help(){
  for(int i = 0; i < (sizeof(Help)/50); i++)
    PRINT_STRING(&Help[i][0]);
}

void loop() {
  byte tmp;
  unsigned long tmp_time;
  
  if(trigger == 'r')
  {
    for(int i = 0; i < NUM_MACS; i++){
      tmp = (rand() % 10) + '0';
      repeatSendPacket(mac+(i*MAC_SIZE), &tmp);
    }
    PRINT_STRING(FinRandMass);
    receiveAsClickerMasterStart();
  } 
  else if(trigger == 'm')
  {
    for(int i = 0; i < NUM_MACS; i++){
      repeatSendPacket(mac+(i*MAC_SIZE), &answer);
    }
    PRINT_STRING(FinMass);
    receiveAsClickerMasterStart();
  }
  else if(trigger == 's')
  {
//    repeatSendPacket(myMAC,&answer);
    repeatSendPacket(oppositeMyMAC,&answer);
    PRINT_STRING(FinSingle);
    receiveAsClickerMasterStart();
  } 
  
  if(trigger == 0){
    while(digitalRead(IRQ) == LOW){
      recordAnswer();
    }
  }
  else if (trigger == 'a')
  {
    while(digitalRead(IRQ) == LOW){
      recordAnswer();
    }
    tmp_time = millis();
    if(tmp_time - time > 1500 || tmp_time < time){
      time = tmp_time;
      compileStats();
      if(oldAnswer != maxAnswer){
        oldAnswer = maxAnswer;
        massSendAsClickerStart();
        repeatSendPacket(oppositeMyMAC,&maxAnswer);
        PRINT_STRING(ChangedByAA);
        Serial.write(maxAnswer);
        PRINT_STRING(NewLine);
        receiveAsClickerMasterStart();
        PRINT_STRING(NewLine);
        trigger = 'a';
      }
    }
  }
  else if(trigger != 'j')
  {
    digitalWrite(CE,LOW);
  }
}
