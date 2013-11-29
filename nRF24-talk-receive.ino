#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);

int fourBits[4];

void setup() {
	Serial.begin(9600);
	delay(1000);
	Serial.println("nRF24L01 receiver starting!");
	radio.begin();
	radio.openReadingPipe(1, pipe);
	radio.startListening();
}

void loop() {
	if (radio.available()) {
		bool done = false;
		while (!done) {
			done = radio.read(fourBits, sizeof(fourBits));
			Serial.println("Data received: ");
			Serial.println(fourBits[0]);
			Serial.println(fourBits[1]);
			Serial.println(fourBits[2]);
			Serial.println(fourBits[3]);
			Serial.println("=============================");
		}
	} else {
		Serial.println("No radio available!");
	}
}