#include "controller.h"

struct switch_request sreq;
struct switch_response sres;

void handleSwitch(LiquidCrystal* lcd, RF24* radio) {


  lcd->setCursor(0, 2);
  radio->openWritingPipe(addresses[ROLE_SWITCH]);
  if ( radio->write(&sreq, sizeof(switch_request)) ) {
    // sreq.set_output[0]++;
    //sreq.set_output[1]++;

    lcd->print(F("SW: "));


    if (!radio->available()) {
      Serial.print(F("Got blank response"));
    } else {
      while (radio->available() ) {
        radio->read( &sres, sizeof( struct switch_response));
        for (int i = 0; i < SWITCH_MAX_OUTPUTS; i++) {

          lcd->print("[");
          if (sres.current_output[i] == -1) {
            lcd->print("--]");
            continue;
          }

          //off by one
          sres.current_output[i]++;
          if (sres.current_output[i] < 10)
            lcd->print("0");
          lcd->print(sres.current_output[i], DEC);
          lcd->print("]");
        }
      }
    }

  } else {
    lcd->print(F("Switch timeout      "));
  }
}
