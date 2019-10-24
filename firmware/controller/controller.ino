#include "controller.h"
#include "tuner.h"
#include "string.h"

byte addresses[][6] = {"2Node", "1Node", "3Node" };

const int rs = 0, rw = 1, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7, ioFrom8574(0x27));
RF24 radio(NRF_CE, NRF_CS);
struct RFInfo rfInfo;
struct switch_preset presets[3];
struct antenna_switch_status ant_switch_status;

struct tuner no_tuner;
struct tuner tuner_vertical_4080;


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


KeyboardLayout keyLayout(4, 7, pgmLayout);
MatrixKeyboardManager keyboard;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

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
  keyLayout.setRowPin(1, 8);
  keyLayout.setRowPin(2, 9);
  keyLayout.setRowPin(3, A2);

  keyboard.initialise(multiIo, &keyLayout, &myListener);
  keyboard.setRepeatKeyMillis(850, 350);

  no_tuner.type = NO_TUNER;
  tuner_vertical_4080.type = TUNER_L;

  presets[0].tuner = &no_tuner;
  presets[0].description = "VERTICAL 20M ";

  presets[1].tuner = &no_tuner;
  presets[1].description = "DIPOLO 20M   ";

  presets[2].tuner = &tuner_vertical_4080;
  presets[2].description = "VERT 40-60-80";
  ant_switch_status.selected_antenna = -1;
  selectedAntenna = -1;
}

void loop() {

  radio.stopListening();

  queuedKey = pressedKey;
  pressedKey = 0;
  
    handleSwitch(&ant_switch_status, &radio, selectedAntenna, queuedKey);


  handleTuner(presets, &radio, ant_switch_status.selected_antenna, queuedKey);

  handleRF(&rfInfo);
  handleLCD(&lcd, &rfInfo, &ant_switch_status, presets, queuedKey);

  radio.startListening();
  taskManager.runLoop();
  queuedKey = 0;

  delay(50);
}
