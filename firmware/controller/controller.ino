#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "tuner.h"
#define NRF_CE A0
#define NRF_CS A1
#include "string.h"
#include <Encoder.h>

RF24 radio(NRF_CE, NRF_CS);
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
Encoder myEnc(2, 3);
struct antenna_request req;
struct antenna_response res;

struct switch_request sreq;
struct switch_response sres;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializado");

  radio.begin();
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.setPALevel(RF24_PA_MAX);

  radio.openWritingPipe(addresses[ROLE_SWITCH]);
  radio.openReadingPipe(1, addresses[ROLE_CONTROLLER]);

  radio.startListening();

  req.command = GOTO;
  req.motion_value = 9000;

  sreq.command = SWITCH_CHANGE;
  sreq.set_output[0] = -1;
  sreq.set_output[1] = 2;
  sreq.set_output[2] = 1;
  sreq.set_output[3] = 1;

}
bool wait = false;
void loop() {
  wait = true;
  radio.stopListening();

  lcd.setCursor(0, 0);
  radio.openWritingPipe(addresses[ROLE_ANTENNA]);
  if ( radio.write(&req, sizeof(antenna_request)) ) {
    req.command = NOOP;
    if (!radio.available()) {
      Serial.print(F("Got blank response"));
    } else {
      while (radio.available() ) {                    // If an ack with payload was received
        radio.read( &res, sizeof( struct antenna_response));                  // Read it, and display the response time

        lcd.setCursor(0, 0);

        char line[21];



        switch (res.status) {
          case STOPPED:
            lcd.print( "STOPPED    ");
            break;
          case GOING_UP:
            lcd.print( "GOING UP   ");
            break;
          case GOING_DOWN:
            lcd.print( "GOING DOWN ");

        };
        sprintf(line, "%02dC %05d", res.temperature, res.current_step);
        lcd.print(line);

        lcd.setCursor(0, 1);

        int r = myEnc.read();
        if (r) {
          req.motion_value = r * 2; //res.current_step + 5 * r;
          req.command = GOTO;
          req.relative = true;
          lcd.print(r);
        }
        myEnc.write(0);

       // lcd.print("    ");
      }
    }

  } else {
    lcd.print("Tuner timeout        ");
  }

  lcd.setCursor(0, 2);
  radio.openWritingPipe(addresses[ROLE_SWITCH]);
  if ( radio.write(&sreq, sizeof(switch_request)) ) {
   // sreq.set_output[0]++;
    //sreq.set_output[1]++;

    lcd.print(F("SW: "));


    if (!radio.available()) {
      Serial.print(F("Got blank response"));
    } else {
      while (radio.available() ) {
        radio.read( &sres, sizeof( struct switch_response));
        for (int i = 0; i < SWITCH_MAX_OUTPUTS; i++) {

          lcd.print("[");
          if (sres.current_output[i] == -1) {
            lcd.print("--]");
            continue;
          }

          //off by one
          sres.current_output[i]++;
          if (sres.current_output[i] < 10)
            lcd.print("0");
          lcd.print(sres.current_output[i], DEC);
          lcd.print("]");
        }
      }
    }

  } else {
    lcd.print(F("Switch timeout      "));
  }

  radio.startListening();

  delay(100);

}
