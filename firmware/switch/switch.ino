#define NRF_CE 9
#define NRF_CS 10

#include <RF24.h>
#include "tuner.h"
unsigned long configTimer;

char output_map[SWITCH_MAX_OUTPUTS][SWITCH_MAX_ANTENNAS] = {
  { A0, A1, A2, A3, A4, A5, -1, -1, -1, -1, -1, -1 },
  { 02, 03, 04, 05, 06, 07, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
};

bool await_adc;
RF24 radio(NRF_CE, NRF_CS);

struct switch_response response;

void setup() {
  Serial.begin(115200);

  initializeRadio();

  for (int i = 0; i < SWITCH_MAX_OUTPUTS; i++) {

    //marco mi status como todo OFF
    response.current_output[i] = 0xff;

    //seteo los pines
    for (int j = 0; j < SWITCH_MAX_ANTENNAS; j++) {
      if (output_map[i][j] == -1)
        continue;

      pinMode(output_map[i][j], OUTPUT);
    }
  }


  ADCSRA |= _BV(ADEN);  // enable the ADC
}

void loop() {

  byte pipeNo;
  struct switch_request req;
  if (radio.failureDetected) {
    radio.failureDetected = false;
    initializeRadio();
  }
  while ( radio.available(&pipeNo)) {
    radio.read( &req, sizeof(struct switch_request) );
    radio.writeAckPayload(pipeNo, &response, sizeof(struct switch_response) );

    if (req.command == SWITCH_NOOP) {
      continue;
    }

    if (req.command == SWITCH_CHANGE) {
      for (int i = 0; i < SWITCH_MAX_OUTPUTS; i++) {

        //me piden apagar
        if (req.set_output[i] == -1)
        {
          if (response.current_output[i] != -1)
            digitalWrite(output_map[i][response.current_output[i]], LOW);
          response.current_output[i] = -1;
          continue;
        }

        //sanity
        if (req.set_output[i] > SWITCH_MAX_ANTENNAS)
          continue;

        //miro en el LUT a que pin corresponde
        char setout = output_map[i][req.set_output[i]];

        //veo si la antena existe ( si el pin es -1, no existe)
        if (setout == -1)
          continue;

        //si esta encendida la apago
        if (response.current_output[i] != -1)
          digitalWrite(output_map[i][response.current_output[i]], LOW);

        //guardo el nuevo valor
        response.current_output[i] = req.set_output[i];

        //enciendo la salida
        digitalWrite(setout, HIGH);
      }

    }

    if (!await_adc) {
      ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
      ADCSRA |= _BV(ADSC);  // Start the ADC
      await_adc = true;
    }
  }

  if (await_adc && !bit_is_set(ADCSRA, ADSC)) {
    unsigned int wADC;
    double t;
    // Reading register "ADCW" takes care of how to read ADCL and ADCH.
    wADC = ADCW;

    // The offset of 324.31 could be wrong. It is just an indication.
    t = (wADC - 324.31 ) / 1.22;

    response.temperature = t * 10;
    await_adc = false;
  }
  if (millis() - configTimer > 5000) {
    configTimer = millis();
    if (radio.getDataRate() != RADIO_RATE) {
      radio.failureDetected = true;
      Serial.print("Radio configuration error detected");
    }
  }

}

void initializeRadio() {
  radio.begin();
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.setPALevel(RF24_PA_LOW);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(5, 15);                 // Optionally, increase the delay between retries. Want the number of auto-retries as high as possible (15)
  radio.setCRCLength(RADIO_CRC);         // Set CRC length to 16-bit to ensure quality of data
  radio.setChannel(RADIO_CHANNEL);                     // Set the channel

  radio.setDataRate(RADIO_RATE);           // Raise the data rate to reduce transmission distance and increase lossiness

  radio.openWritingPipe(addresses[ROLE_CONTROLLER]);
  radio.openReadingPipe(1, addresses[ROLE_SWITCH]);
  radio.startListening();
  radio.writeAckPayload(1, &response, sizeof(struct switch_response));
}
