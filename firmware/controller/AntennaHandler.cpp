#include "controller.h"

struct antenna_request req;
struct antenna_response res;

void handleAntenna(LiquidCrystal* lcd, RF24* radio) {
  lcd->setCursor(0, 0);
  radio->openWritingPipe(addresses[ROLE_ANTENNA]);
  if ( radio->write(&req, sizeof(antenna_request)) ) {
    req.command = NOOP;
    if (!radio->available()) {
      Serial.print(F("Got blank response"));
    } else {
      while (radio->available() ) {                    // If an ack with payload was received
        radio->read( &res, sizeof( struct antenna_response));                  // Read it, and display the response time

        lcd->setCursor(0, 0);

        char line[21];

        switch (res.status) {
          case STOPPED:
            lcd->print( "STOPPED    ");
            break;
          case GOING_UP:
            lcd->print( "GOING UP   ");
            break;
          case GOING_DOWN:
            lcd->print( "GOING DOWN ");

        };
        sprintf(line, "%02dC %05d", res.temperature, res.current_step);
        lcd->print(line);

      }
    }

  } else {
    lcd->print("Tuner timeout       ");
  }
}
