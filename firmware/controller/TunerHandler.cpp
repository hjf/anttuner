#include "controller.h"

struct antenna_request req;
struct antenna_response res;

void handleTuner(struct switch_preset* presets, RF24* radio, int selectedPreset) {
  if (selectedPreset < 0)
    return;
  struct tuner* tuner = (presets + selectedPreset)->tuner;
  if (tuner->type == NO_TUNER)
    return;

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
