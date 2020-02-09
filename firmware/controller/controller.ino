#include "controller.h"
#include "tuner.h"
#include "string.h"

byte addresses[][6] = {"2Node", "1Node", "3Node" };
unsigned long f_query_timer;
char radioBuf[64];
char radioBufPtr;
const int rs = 0, rw = 1, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7, ioFrom8574(0x27));
RF24 radio(NRF_CE, NRF_CS);
AltSoftSerial altSerial;

struct RFInfo rfInfo;
struct switch_preset presets[3];
struct antenna_switch_status ant_switch_status;

struct tuner no_tuner;
struct tuner tuner_vertical_4080;

struct RadioInfo radioInfo;


int selectedAntenna;



//{
//  'a', 'b', 'c', 'd', 'T', 'r', 'q',
//  '1', '4', '7', 'E', 'L', 't', 'w',
//  '2', '5', '8', '0', 'C', 'y', 'e',
//  '3', '6', '9', 'N', 'K', 'i', 'u'
//};


IoAbstractionRef multiIo = multiIoExpander(100);

char pressedKey;
char queuedKey;
class MyKeyboardListener : public KeyboardListener {
  public:
    void keyPressed(char key, bool held) override {
      pressedKey = key;
      //Serial.println(key);
      //delay(50);
      switch (key) {
        case 'q':
          selectedAntenna = 0;
          break;
        case 'w':
          selectedAntenna = 1;
          break;
        case 'e':
          selectedAntenna = 2;
          break;

        default:
          return;
      }
    }

    void keyReleased(char key) override {
    }
} myListener;

void onEncoderChange(int newValue) {
  switches.getEncoder()->setCurrentReading(50);

}


KeyboardLayout keyLayout(4, 7, pgmLayout);
MatrixKeyboardManager keyboard;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);

  lcd.configureBacklightPin(3);
  lcd.backlight();

  Wire.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  //lcd.print("Inicializado");
  lcd.clear();
  radio.begin();
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.setPALevel(RF24_PA_MAX);

  radio.openWritingPipe(addresses[ROLE_SWITCH]);
  radio.openReadingPipe(1, addresses[ROLE_CONTROLLER]);

  radio.startListening();

  multiIoAddExpander(multiIo, outputOnlyFromShiftRegister(SR_CLK, SR_DAT, SR_LAT), 64);

  keyLayout.setColPin(0, 133);
  keyLayout.setColPin(1, 134);
  keyLayout.setColPin(2, 135);
  keyLayout.setColPin(3, 136);
  keyLayout.setColPin(4, 137);
  keyLayout.setColPin(5, 138);
  keyLayout.setColPin(6, 139);

  keyLayout.setRowPin(0, 7);
  keyLayout.setRowPin(1, 2);
  keyLayout.setRowPin(2, 3);
  keyLayout.setRowPin(3, A2);

  keyboard.initialise(multiIo, &keyLayout, &myListener);
  keyboard.setRepeatKeyMillis(850, 350);

  no_tuner.type = NO_TUNER;
  tuner_vertical_4080.type = TUNER_L;

  presets[0].tuner = &no_tuner;
  presets[0].description = "YAGI 20M     ";

  presets[1].tuner = &no_tuner;
  presets[1].description = "MORGAIN 20-40";

  presets[2].tuner = &tuner_vertical_4080;
  presets[2].description = "VERT 40-60-80";
  ant_switch_status.selected_antenna = -1;
  selectedAntenna = -1;
  setupRotaryEncoderWithInterrupt(2, 3, onEncoderChange);
  switches.changeEncoderPrecision(100, 0);
  radioBufPtr = 0;
  altSerial.begin(4800);
  f_query_timer = millis() + 1000;
}

void doSerial() {
  for (char i = 0; i < 10; i++) {
REDO:
    if (radioBufPtr > sizeof(radioBuf))
      radioBufPtr = 0;

    while (altSerial.available()) {
      f_query_timer = millis() + 5000;
      byte alt = altSerial.read();
      Serial.write(alt);
      radioBuf[radioBufPtr++] = alt;

      if (alt == ';') {

        radioBufPtr = 0;
        if (radioBuf[0] == 'I' && radioBuf[1] == 'F') {
          radioBuf[13] = 0;
          radioInfo.Frequency = atol(radioBuf + 2);
          String mode;
          switch (radioBuf[29]) {
            case '1':
              mode = F("LSB");
              break;
            case '2':
              mode = F("USB");
              break;
            case '3':
              mode = F("CW ");
              break;
            case '4':
              mode = F("FM ");
              break;
            case '5':
              mode = F("AM ");
              break;
            case '6':
              mode = F("FSK");
              break;
            case '7':
              mode = F("CWR");
              break;
            case '8':
              mode = F("TUN");
              break;
            case '9':
              mode = F("FSR");
              break;

            default:
              mode = F("UNK");
              break;
          }
          mode.toCharArray(radioInfo.Mode, 4);
        }
      }

    }

    while (Serial.available()) {
      f_query_timer = millis() + 5000;
      byte real = Serial.read();
      altSerial.write(real);
      if (real == ';') {
        unsigned long bail = millis() + 5;
        while (!altSerial.available()) {
          if (millis() > bail)
            goto BAIL;
        }
        goto REDO;
      }

    }
BAIL:
    if (millis() > f_query_timer) {
      f_query_timer = millis() + 2000;
      altSerial.print("IF;");
    }
    taskManager.runLoop();
  }
}
void loop() {

  radio.stopListening();

  queuedKey = pressedKey;
  pressedKey = 0;

 
  handleSwitch(&ant_switch_status, &radio, selectedAntenna, queuedKey);
 
  handleTuner(presets, &radio, ant_switch_status.selected_antenna, queuedKey);
 
  handleRF(&rfInfo);
 
  handleLCD(&lcd, &rfInfo, &ant_switch_status, presets, queuedKey, &radioInfo);
  doSerial();

  radio.startListening();
  taskManager.runLoop();
  queuedKey = 0;

  //delay(50);
}
