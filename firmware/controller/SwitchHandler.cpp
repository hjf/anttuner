#include "controller.h"

struct switch_request sreq;
struct switch_response sres;

void handleSwitch(antenna_switch_status* ant_switch_status, RF24* radio, int selectedAntenna, char pressedKey) {
  radio->openWritingPipe(addresses[ROLE_SWITCH]);
  if (selectedAntenna > -1 && ant_switch_status->selected_antenna != selectedAntenna) {
    sreq.command = SWITCH_CHANGE;
    sreq.set_output[0] = selectedAntenna;
  }
  if ( radio->write(&sreq, sizeof(switch_request)) ) {
    sreq.command = SWITCH_NOOP;
    ant_switch_status->status = REMOTE_STATUS_OK;
    while (radio->available() ) {
      radio->read( &sres, sizeof( struct switch_response));
      ant_switch_status->selected_antenna = sres.current_output[0];
    }
  } else {
    ant_switch_status->status = REMOTE_STATUS_COMM_ERROR;
    
    sreq.command = SWITCH_NOOP;
  }
}
