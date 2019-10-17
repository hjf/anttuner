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
  radio.setPALevel(RF24_PA_LOW);

  radio.openWritingPipe(addresses[ROLE_CONTROLLER]);
  radio.openReadingPipe(1, addresses[ROLE_ANTENNA]);
  //radio.openReadingPipe(2, addresses[ROLE_SWITCH]);
  radio.startListening();

}
bool wait = false;
void loop() {
  // put your main code here, to run repeatedly:

  struct antenna_request req;
  struct antenna_response res;
  if (!wait) {
    req.command = GOTO;
    req.motion_value = 9000;
  } else {
    //req.command = NOOP;

  }
  wait = true;
  radio.stopListening();
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
        sprintf(line, "%02dC %05d        ", res.temperature, res.current_step);
        lcd.print(line);

        lcd.setCursor(0, 2);

        int r = myEnc.read();
        if (r) {
          req.motion_value = r * 2; //res.current_step + 5 * r;
          req.command = GOTO;
          req.relative = true;
          lcd.print(r);
        }
        myEnc.write(0);

        lcd.print("    ");
      }
    }

  } else {
    lcd.setCursor(0, 0);
    lcd.print("Tuner timeout");
  }
  radio.startListening();

  delay(100);

}
