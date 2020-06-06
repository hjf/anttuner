#include "tuner.h"
#include "string.h"
#include <RF24.h>
#include <printf.h>

const char SERIES_L[] = { 7, 4, 5, 8, 9, 10};
const char SHUNT_L[] = { A3, A4, 2, 3 };
byte addresses[][6] = {"2Node", "1Node", "3Node", "4Node" };
unsigned long configTimer;
#define NRF_CE A2
#define NRF_CS A1
#define ENABLE_SHUNT_C 6
#define ENABLE_SHUNT_L A5
RF24 radio(NRF_CE, NRF_CS);


void setSeriesL(char lval);
void setShuntL(char lval);

struct relaytuner_request rreq;
struct relaytuner_response rres;

void setup() {
  Serial.begin(9600);
  printf_begin();
  pinMode(ENABLE_SHUNT_C, OUTPUT);
  digitalWrite(ENABLE_SHUNT_C, LOW);
  pinMode(ENABLE_SHUNT_L, OUTPUT);
  digitalWrite(ENABLE_SHUNT_L, LOW);

  for (char i = 0; i < sizeof(SERIES_L); i++) {
    pinMode(SERIES_L[i], OUTPUT);
    digitalWrite(SERIES_L[i], LOW);
  }
  for (char i = 0; i < sizeof(SHUNT_L); i++) {
    pinMode(SHUNT_L[i], OUTPUT);
    digitalWrite(SHUNT_L[i], LOW);
  }

  delay(100);
  initializeRadio();

}

void loop() {
  byte pipeNo;
  if (radio.failureDetected) {
    radio.failureDetected = false;
    initializeRadio();
  }
  while ( radio.available(&pipeNo)) {

    radio.read( &rreq, sizeof(struct relaytuner_request) );

    radio.writeAckPayload(pipeNo, &rres, sizeof(struct relaytuner_response) );

    if (rreq.command == RELAYTUNER_NOOP) {
      continue;
    }

    setSeriesL(rreq.set_series_l);
    setShuntC(rreq.set_shunt_c);
    setShuntL(rreq.set_shunt_l);

    rres.series_l = rreq.set_series_l;
    rres.shunt_c = rreq.set_shunt_c;
    rres.shunt_l = rreq.set_shunt_l;

    Serial.print("Series L: ");
    Serial.println(rreq.set_series_l);
    Serial.print("Shunt L: ");
    Serial.println(rreq.set_shunt_c);
    Serial.print("Shunt C: ");
    Serial.println(rreq.set_shunt_l);

  }

  if (millis() - configTimer > 5000) {
    configTimer = millis();
    if (radio.getDataRate() != RADIO_RATE) {
      radio.failureDetected = true;
      Serial.print("Radio configuration error detected");
    }
  }

}

void setShuntC(char lval) {
  if (lval)
    digitalWrite(ENABLE_SHUNT_C, HIGH);
  else
    digitalWrite(ENABLE_SHUNT_C, LOW);
}

void setSeriesL(char lval) {
  lval = lval & 0b00111111;
  for (char i = sizeof(SERIES_L) - 1; i >= 0; i--) {
    digitalWrite(SERIES_L[i], lval & 0x01);
    lval = lval >> 1;
  }
}


void setShuntL(char lval) {
  if (lval)
    digitalWrite(ENABLE_SHUNT_L, HIGH);
  else
    digitalWrite(ENABLE_SHUNT_L, LOW);

  lval = lval & 0b00111111;
  for (char i = sizeof(SHUNT_L) - 1; i >= 0; i--) {
    digitalWrite(SHUNT_L[i], lval & 0x01);
    lval = lval >> 1;
  }
}

void initializeRadio() {
  radio.begin();
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.setPALevel(RF24_PA_HIGH);



  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(5, 15);                 // Optionally, increase the delay between retries. Want the number of auto-retries as high as possible (15)
  radio.setCRCLength(RADIO_CRC);         // Set CRC length to 16-bit to ensure quality of data
  radio.setChannel(RADIO_CHANNEL);                     // Set the channel

  radio.setDataRate(RADIO_RATE);           // Raise the data rate to reduce transmission distance and increase lossiness

  radio.openWritingPipe(addresses[ROLE_CONTROLLER]);
  radio.openReadingPipe(1, addresses[ROLE_RELAYTUNER]);
  radio.startListening();
  radio.writeAckPayload(1, &rres, sizeof(struct relaytuner_response));
  radio.printDetails();
}
