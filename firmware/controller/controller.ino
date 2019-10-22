#include "controller.h"
#include "tuner.h"
#include "string.h"

byte addresses[][6] = {"2Node", "1Node", "3Node" };
const int rs = 0, rw = 1, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7, ioFrom8574(0x27));
RF24 radio(NRF_CE, NRF_CS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  lcd.configureBacklightPin(3);
  lcd.backlight();

  Wire.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  lcd.print("Inicializado");

  radio.begin();
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.setPALevel(RF24_PA_MAX);

  radio.openWritingPipe(addresses[ROLE_SWITCH]);
  radio.openReadingPipe(1, addresses[ROLE_CONTROLLER]);

  radio.startListening();

}

void loop() {
  radio.stopListening();
  handleAntenna(&lcd, &radio);
  handleSwitch(&lcd, &radio);
  radio.startListening();
  taskManager.runLoop();
  delay(100);
}
