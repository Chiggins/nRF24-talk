void readAllRegisters(){
  byte readByte[10];
  int tmp;
  
  PRINT_STRING(Registers);
  for(int i = 0; i < 10; i++){
    digitalSpiRead(R_REGISTER | i, readByte, 1);
    Serial.print(i, HEX);
    PRINT_STRING(Colen);
    tmp = readByte[0];
    Serial.println(tmp, BIN);
  }
  PRINT_STRING(RegistersN);
}

byte digitalSpiRead(byte command, byte* result, int length) {
  byte val = 0;
  // take the SS pin low to select the chip:
  digitalWrite(CSN,LOW);
  //  send in the address and value via SPI:
  statusByte = SPI.transfer(command);
  for(int i = 0; i < length; i++){
    result[i] = SPI.transfer(0x00);
  }
  // take the SS pin high to de-select the chip:
  digitalWrite(CSN,HIGH); 
}

byte digitalSpiWrite(byte command, byte* value, int length) {
  byte val = 0;
  // take the SS pin low to select the chip:
  digitalWrite(CSN,LOW);
  //  send in the address and value via SPI:
  statusByte = SPI.transfer(command);
  for(int i = 0; i < length; i++){
    SPI.transfer(value[i]);
  }
  // take the SS pin high to de-select the chip:
  digitalWrite(CSN,HIGH);  
}

byte digitalSpiWrite(byte command, byte value) {
  digitalSpiWrite(command, &value, 1);
}

byte digitalSpiWrite(byte command) {
  digitalSpiWrite(command, 0, 0);
}
