#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);

void setup() {
	Serial.begin(9600);
	radio.begin();
	radio.openWritingPipe(pipe);
}

void loop() {
	int fourBits[4];
	fourBits[0] = 1991;
	fourBits[1] = 0;
	fourBits[2] = 1;
	fourBits[3] = 0;

	radio.write(fourBits, sizeof(fourBits));
	Serial.println("Broadcasted four bits!");
}