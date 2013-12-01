void dumpMACs(){
  int digit;
  
  PRINT_STRING(Macs);
  for(int i = 0; i < numAnswers; i++){
    for(int j = 0; j < MAC_SIZE; j++){
      digit = (int)record[i].MAC[j];
      sprintf(string, STRING(MacsFormat), digit);
      Serial.print(string);
    }
    PRINT_STRING(NewLine);
  }
  PRINT_STRING(MacsN);
}

void showStats(){
  byte tmp;
  double percent;
  
  PRINT_STRING(Stats);
  for(int i = 0; i < sizeof(stats); i++){
    if(stats[i] != 0){
      tmp = i;
      percent = ((double)stats[i] * 100.0 ) / (double)numAnswers;
      sprintf(string, STRING(StatFormat), tmp, stats[i], percent);
      Serial.print(string);
      Serial.print(dtostrf(percent, 6, 2, string));
      PRINT_STRING(Percent);
    }
  }
  PRINT_STRING(Total);
  Serial.println(numAnswers);
  PRINT_STRING(PopularAnswer);
  Serial.write(maxAnswer);
  PRINT_STRING(StatsN);
}

void newQuestion(){
  memset(stats, 0, sizeof(stats));
  numAnswers = 0;
  maxAnswer = '1';
  oldAnswer = 255;
}

void compileStats(){
  memset(stats, 0, sizeof(stats));
  for(int i = 0; i < numAnswers; i++){
    if(++stats[record[i].answer[0]] > stats[maxAnswer])
      maxAnswer = record[i].answer[0];
  }
}

void recordAnswer(){
  byte buf[PACKET_SIZE];
  byte data[DATA_SIZE];
  uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

  digitalSpiRead(R_RX_PAYLOAD, buf, PACKET_SIZE);

  digitalSpiWrite(W_REGISTER | STATUS, 0x70);    // Clear interrupts
  for(int i = 0; i < numAnswers; i++){
    if(memcmp(buf, record[i].MAC, MAC_SIZE) == 0){

      memcpy(data, buf+MAC_SIZE, DATA_SIZE);
      aes128_dec_single(key, data);

      memcpy(record[i].answer, &data[0], DATA_SIZE);
      return;
    }
  }
  if(numAnswers < MAX_RECORDS){
    memcpy(record[numAnswers].MAC, buf, MAC_SIZE);
    memcpy(record[numAnswers].answer, buf+MAC_SIZE, DATA_SIZE);
    numAnswers++;
  }
}

void receiveAsClickerMasterStart(){
    PRINT_STRING(EnterReceiveMode);
    digitalWrite(CE,LOW);                          // Modify configuration Registers
    digitalSpiWrite(W_REGISTER | CONFIG, 0x0A);    // Power On
    delay(2);
    digitalSpiWrite(W_REGISTER | CONFIG, 0x3F);    // 2-bit CRC, Receive mode
    digitalSpiWrite(W_REGISTER | EN_RXADDR, 0x01); // Only enable rx data pipe 1
    digitalSpiWrite(W_REGISTER | RX_PW_P0, PACKET_SIZE);     // Set size of Receive pipe
    digitalSpiWrite(W_REGISTER | EN_AA, 0x00);     // Disable Auto-Acknowledge on all pipes
    digitalSpiWrite(W_REGISTER | RF_CH, channel);  // Select the channel to receive on
    digitalSpiWrite(W_REGISTER | SETUP_AW, 0x01);  // Select 3-byte MAC length
    digitalSpiWrite(W_REGISTER | RF_SETUP, 0x06);  // Set data rate to 1Mbps at high power
    digitalSpiWrite(FLUSH_RX);                     // Flush the receive buffer
    digitalSpiWrite(W_REGISTER | STATUS, 0x70);    // Clear interrupts
    digitalSpiWrite(W_REGISTER | RX_ADDR_P0, clickerMasterMAC, MAC_SIZE);  // Set the MAC address to listen on
    digitalWrite(CE,HIGH);                         //Finish modifying configuration Registers
    trigger = 0;
}
