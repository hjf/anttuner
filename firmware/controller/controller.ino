#include "controller.h"
#include "tuner.h"
#include "string.h"

byte addresses[][6] = {"2Node", "1Node", "3Node", "4Node" };

unsigned long configTimer;

const int rs = 0, rw = 1, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7, ioFrom8574(0x27));
RF24 radio(NRF_CE, NRF_CS);


struct RFInfo rfInfo;
struct switch_preset presets[3];
struct antenna_switch_status ant_switch_status;

struct tuner no_tuner;
struct tuner tuner_vertical_4080;
struct tuner tuner_relay;

struct RadioInfo radioInfo;


char selectedAntenna;
char encoderValue;


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

        case 'y':
          ant_switch_status.autoswitching = !ant_switch_status.autoswitching;
          break;

        default:
          return;
      }
    }

    void keyReleased(char key) override {
    }
} myListener;

void onEncoderChange(int newValue) {
#define CUR 50

  encoderValue = newValue - CUR;

  switches.getEncoder()->setCurrentReading(CUR);
  //Serial.println(newValue);
  struct tuner* tuner = (presets + selectedAntenna)->tuner;
  if (tuner->type == NO_TUNER || tuner->local_status == TUNER_STATUS_OK) {
    if (newValue > 50) {
      if (selectedAntenna < 2)
        selectedAntenna++;
    }
    else if (newValue < 50) {
      if (selectedAntenna > 0) {
        selectedAntenna--;
      }
    }
  }


}


KeyboardLayout keyLayout(4, 7, pgmLayout);
MatrixKeyboardManager keyboard;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.configureBacklightPin(3);
  lcd.backlight();
  const char antena[8] PROGMEM = {
    B10101,
    B10101,
    B01110,
    B00100,
    B00100,
    B00100,
    B00100,
  };

  const char coil[8] PROGMEM = {
    B11110,
    B00001,
    B00110,
    B00001,
    B00110,
    B00001,
    B11110,
  };

  const char cap[8] PROGMEM = {
    B00100,
    B00100,
    B11111,
    B00000,
    B11111,
    B00100,
    B00100,
  };


  Wire.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  lcd.createChar(1, antena);
  lcd.createChar(2, coil);
  lcd.createChar(3, cap);
  //lcd.print("Inicializado");
  lcd.clear();
  configureRadio();
  multiIoAddExpander(multiIo, outputOnlyFromShiftRegister(SR_CLK, SR_DAT, SR_LAT), 64);
  keyLayout.setColPin(0, 133);
  keyLayout.setColPin(1, 134);
  keyLayout.setColPin(2, 135);
  keyLayout.setColPin(3, 136);
  keyLayout.setColPin(4, 137);
  keyLayout.setColPin(5, 138);
  keyLayout.setColPin(6, 139);

  keyLayout.setRowPin(0, 7);
  keyLayout.setRowPin(1, A0);
  keyLayout.setRowPin(2, 3);
  keyLayout.setRowPin(3, A2);
  keyboard.initialise(multiIo, &keyLayout, &myListener);
  keyboard.setRepeatKeyMillis(850, 350);
  no_tuner.type = NO_TUNER;
  tuner_vertical_4080.type = TUNER_L;
  tuner_relay.type = RELAY_TUNER;

  presets[0].tuner = &no_tuner;
  presets[0].description = "YAGI 10-20M     ";

  presets[1].tuner = &no_tuner;
  presets[1].description = "                ";

  //presets[2].tuner = &tuner_vertical_4080;
  presets[2].tuner = &tuner_relay;
  presets[2].description = "VERTICAL        ";

  ant_switch_status.selected_antenna = -1;
  ant_switch_status.autoswitching = !0;
  selectedAntenna = -1;
  setupRotaryEncoderWithInterrupt(2, A3, onEncoderChange);
  switches.changeEncoderPrecision(100, 0);
  //radioBufPtr = 0;
  altSerial.begin(4800);
  //  f_query_timer = millis() + 1000;
}



void configureRadio() {
  radio.begin();
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.setPALevel(RF24_PA_MAX);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(15, 15);                 // Optionally, increase the delay between retries. Want the number of auto-retries as high as possible (15)
  radio.setCRCLength(RADIO_CRC);         // Set CRC length to 16-bit to ensure quality of data
  radio.setChannel(RADIO_CHANNEL);                     // Set the channel

  radio.setDataRate(RADIO_RATE);           // Raise the data rate to reduce transmission distance and increase lossiness

  radio.openWritingPipe(addresses[ROLE_SWITCH]);
  radio.openReadingPipe(1, addresses[ROLE_CONTROLLER]);

  radio.startListening();
}
void loop() {
  if (radio.failureDetected) {
    radio.failureDetected = false;
    configureRadio();
  }
  // doSerial();
  taskManager.runLoop();

  radio.stopListening();

  queuedKey = pressedKey;
  pressedKey = 0;


  handleSwitch(&ant_switch_status, &radio, selectedAntenna, queuedKey, &radioInfo, &sres);

  HandleSerial(&radioInfo);

  //handleTuner(presets, &radio, ant_switch_status.selected_antenna, queuedKey);
  //doSerial();
  handleRelayTuner(presets, &radio, &ant_switch_status, queuedKey, &encoderValue, &radioInfo);
  HandleSerial(&radioInfo);
  handleRF(&rfInfo);
  HandleSerial(&radioInfo);
  handleLCD(&lcd, &rfInfo, &ant_switch_status, presets, queuedKey, &radioInfo, &sres);
  HandleSerial(&radioInfo);

  //radio.startListening();
  //taskManager.runLoop();
  queuedKey = 0;

  if (millis() - configTimer > 5000) {
    configTimer = millis();
    if (radio.getDataRate() != RADIO_RATE) {
      radio.failureDetected = true;
      Serial.print("Radio configuration error detected");
    }
  }

  //delay(50);
}
