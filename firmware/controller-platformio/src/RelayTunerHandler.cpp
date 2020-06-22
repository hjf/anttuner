#include "controller.h"

struct relaytuner_request rreq;
struct relaytuner_response rres;
float lastFreq;

void handleRelayTuner(struct switch_preset* presets, RF24* radio, antenna_switch_status* ant_switch_status, char pressedKey, char* encoderValue, RadioInfo* radioInfo) {


  char enc = 0;
  //Serial.println(*encoderValue,HEX);
  if (*encoderValue != 0) {
    enc = *encoderValue;
    *encoderValue = 0;
  }


  static char lastKey;
  if (pressedKey != 0 && pressedKey == lastKey)
    return;
  lastKey = pressedKey;

  if (ant_switch_status->selected_antenna < 0)
    return;
  struct tuner* tuner = (presets + ant_switch_status->selected_antenna)->tuner;

  if (tuner->type != RELAY_TUNER)
    return;

  if (pressedKey == 'L') {

    if (tuner->local_status == TUNER_STATUS_CHANGING_L) {
      tuner->local_status = TUNER_STATUS_CHANGING_SHUNT_L;


    }
    else {
      tuner->local_status = TUNER_STATUS_CHANGING_L;

    }
    tuner->next_L = tuner->L;
    tuner->next_shunt_L = tuner->shunt_L;
    tuner->next_shunt_C = tuner->shunt_C;
  }

  if (pressedKey == 'C') {

    tuner->local_status = TUNER_STATUS_CHANGING_SHUNT_C;
    tuner->next_shunt_C = tuner->shunt_C;

  }

  if (enc != 0) {
#define MAX_SHUNT_L 15
#define MAX_SERIES_L 63
#define MAX_SHUNT_C 1

    if (tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_L) {
      tuner->next_shunt_L = tuner->next_shunt_L + enc;
      if (tuner->next_shunt_L > MAX_SHUNT_L)
        tuner->next_shunt_L = MAX_SHUNT_L;
      if (tuner->next_shunt_L < 0)
        tuner->next_shunt_L = 0;
    }

    if (tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_C) {
      tuner->next_shunt_C = tuner->next_shunt_C + enc;
      if (tuner->next_shunt_C > MAX_SHUNT_C)
        tuner->next_shunt_C = MAX_SHUNT_C;
      if (tuner->next_shunt_C < 0)
        tuner->next_shunt_C = 0;
    }

    if (tuner->local_status == TUNER_STATUS_CHANGING_L) {
      tuner->next_L = tuner->next_L + enc;
      if (tuner->next_L > MAX_SERIES_L)
        tuner->next_L = MAX_SERIES_L;
      if (tuner->next_L < 0)
        tuner->next_L = 0;
    }

    rreq.command = RELAYTUNER_CHANGE;
    rreq.set_shunt_l = tuner->next_shunt_L;
    rreq.set_series_l = tuner->next_L;
    rreq.set_shunt_c = tuner->next_shunt_C;
    enc = 0;
  }

  if (pressedKey >= '0' &&   pressedKey <= '9') {

    int pk = pressedKey - 0x30;
    if (tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_L)
      tuner->next_shunt_L = tuner->next_shunt_L * 10 + pk;

    if (tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_C)
      tuner->next_shunt_C = tuner->next_shunt_C * 10 + pk;

    if (tuner->local_status == TUNER_STATUS_CHANGING_L)
      tuner->next_L = tuner->next_L * 10 + pk;
  }

  //ERASE
  if (pressedKey == 'E') {
    tuner->next_L = 0;
    tuner->next_C = 0;
    tuner->next_shunt_L = 0;
    tuner->next_shunt_C = 0;
  }

  if (pressedKey == 'N') {

    if (tuner->local_status == TUNER_STATUS_CHANGING_L
        || tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_L
        || tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_C) {
      rreq.command = RELAYTUNER_CHANGE;

      rreq.set_shunt_l = tuner->next_shunt_L;
      rreq.set_series_l = tuner->next_L;
      rreq.set_shunt_c = tuner->next_shunt_C;

      tuner->local_status = TUNER_STATUS_OK;
    }

  }

  ////////////semi auto tuner

  if (lastFreq != radioInfo->Frequency && tuner->local_status == TUNER_STATUS_OK && ant_switch_status->autoswitching) {
    rreq.command = RELAYTUNER_CHANGE;

    //    if (radioInfo->Frequency < 3540000.0) {
    //      rreq.set_shunt_l =  11;
    //      rreq.set_shunt_c =  0;
    //      rreq.set_series_l =  37;
    //    }
    //    else if (radioInfo->Frequency < 3580000.0) {
    //      rreq.set_shunt_l =  11;
    //      rreq.set_shunt_c =  0;
    //      rreq.set_series_l =  36;
    //    }
    //    else if (radioInfo->Frequency < 3600000.0) {
    //      rreq.set_shunt_l =  11;
    //      rreq.set_shunt_c =  0;
    //      rreq.set_series_l =  35;
    //    }
    //    else if (radioInfo->Frequency < 3650000.0) {
    //      rreq.set_shunt_l =  11;
    //      rreq.set_shunt_c =  0;
    //      rreq.set_series_l =  34;
    //    }
    //    else if (radioInfo->Frequency < 3675000.0) {
    //      rreq.set_shunt_l =  11;
    //      rreq.set_shunt_c =  0;
    //      rreq.set_series_l =  33;
    //    }
    //    else
    if (radioInfo->Frequency < 3900000.0) {

      double series = -0.027279369721526 * (radioInfo->Frequency / 1000.0) + 136.02289026677;
      rreq.set_shunt_l =  11;
      rreq.set_shunt_c =  0;
      rreq.set_series_l =  series + 0.5;
      rreq.set_series_l = rreq.set_series_l;// + 1;
    }
    else if (radioInfo->Frequency < 5400000.0) {
      rreq.set_shunt_l =  10;
      rreq.set_shunt_c =  0;
      rreq.set_series_l =  18;
    }
    else if (radioInfo->Frequency < 7040000.0) {
      rreq.set_shunt_l =  14;
      rreq.set_shunt_c =  0;
      rreq.set_series_l =  0;
    }
    else if (radioInfo->Frequency < 7300000.0) {
      rreq.set_shunt_l =  0;
      rreq.set_shunt_c =  0;
      rreq.set_series_l =  0;
    }
    else if (radioInfo->Frequency < 10200000.0) {
      rreq.set_shunt_l =  0;
      rreq.set_shunt_c = 1;
      rreq.set_series_l =  7;
    }else if (radioInfo->Frequency < 18200000.0) {
      rreq.set_shunt_l =  6;
      rreq.set_shunt_c = 0;
      rreq.set_series_l =  1;
    }

  }
  lastFreq = radioInfo->Frequency;


  rreq.magic = TUNER_MAGIC_NUMBER;
  radio->openWritingPipe(addresses[ROLE_RELAYTUNER]);
  if ( radio->write(&rreq, sizeof(relaytuner_request)) ) {
    tuner->status = REMOTE_STATUS_OK;
    rreq.command = RELAYTUNER_NOOP;
    while (radio->available() ) {                    // If an ack with payload was received

      radio->read( &rres, sizeof( struct relaytuner_response));                  // Read it, and display the response time
      //      if (rres.magic != TUNER_MAGIC_NUMBER) {
      //        tuner->status = REMOTE_STATUS_COMM_ERROR;
      //      } else {
      tuner->L = rres.series_l;
      tuner->shunt_C = rres.shunt_c;
      tuner->shunt_L = rres.shunt_l;
      //      }
    }
  } else {
    tuner->status = REMOTE_STATUS_COMM_ERROR;
  }
}
