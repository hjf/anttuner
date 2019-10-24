#include "controller.h"

struct antenna_request req;
struct antenna_response res;

void handleTuner(struct switch_preset* presets, RF24* radio, int selectedPreset, char pressedKey) {
  if (selectedPreset < 0)
    return;
  struct tuner* tuner = (presets + selectedPreset)->tuner;
  if (tuner->type == NO_TUNER)
    return;

  if (pressedKey == 'L') {
    tuner->local_status = TUNER_STATUS_CHANGING_L;
    tuner->next_L = tuner->L;
  }

  if (pressedKey >= '0' &&   pressedKey <= '9') {

    int pk = pressedKey - 0x30;
    if (tuner->local_status == TUNER_STATUS_CHANGING_L)
      tuner->next_L = tuner->next_L * 10 + pk;
    else if (tuner->local_status == TUNER_STATUS_CHANGING_C)
      tuner->next_C = tuner->next_C * 10 + pk;
  }

  //ERASE
  if (pressedKey == 'E') {
    tuner->next_L = 0;
    tuner->next_C = 0;
  }

  if (pressedKey == 'N') {

    if (tuner->local_status == TUNER_STATUS_CHANGING_L || tuner->local_status == TUNER_STATUS_CHANGING_C) {
      req.command = GOTO;
      req.relative = false;
      req.motion_value = tuner->next_L;
      if (tuner->local_status == TUNER_STATUS_CHANGING_C)
        req.motion_value = tuner->next_C;
      tuner->local_status = TUNER_STATUS_OK;
    }

  }

  radio->openWritingPipe(addresses[ROLE_ANTENNA]);
  if ( radio->write(&req, sizeof(antenna_request)) ) {
    tuner->status = REMOTE_STATUS_OK;
    req.command = NOOP;
    while (radio->available() ) {                    // If an ack with payload was received

      radio->read( &res, sizeof( struct antenna_response));                  // Read it, and display the response time
      if (res.status == FAULT) {
        tuner->status = REMOTE_STATUS_FAULT;
        return;
      }
      tuner->L = res.current_step;
    }
  } else {
    tuner->status = REMOTE_STATUS_COMM_ERROR;
  }
}
