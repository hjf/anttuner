/**
   This example shows how to use the matrix keyboard support that's built into IoAbstraction,
   it can be used out the box with either a 3x4 or 4x4 keypad, but you can modify it to use
   any matrix keyboard quite easily.
   It just sends the characters that are typed on the keyboard to Serial. The keyboard in This
   example is connected directly to Arduino pins, but could just as easily be connected over
   a PCF8574, MCP23017 or other IoAbstraction.
*/
#include <Wire.h>
#include <IoAbstraction.h>
#include <IoAbstractionWire.h>

#include <KeyboardManager.h>

const char pgmLayout[] PROGMEM = {
  'a', 'b', 'c', 'd', 'T', 'r', 'q',
  '1', '4', '7', 'E', 'L', 't', 'w',
  '2', '5', '8', '0', 'C', 'y', 'e',
  '3', '6', '9', 'N', 'K', 'i', 'u'
};
KeyboardLayout keyLayout(4, 7, pgmLayout);

MatrixKeyboardManager keyboard;


#define SR_CLK 5
#define SR_DAT 4
#define SR_LAT 6
IoAbstractionRef multiIo = multiIoExpander(100);
//IoAbstractionRef shiftregIo = outputOnlyFromShiftRegister(SR_CLK, SR_DAT, SR_LAT);
//
// We need a class that extends from KeyboardListener. this gets notified when
// there are changes in the keyboard state.
//
class MyKeyboardListener : public KeyboardListener {
  public:
    void keyPressed(char key, bool held) override {
      Serial.print("Key ");
      Serial.print((byte)key, HEX);
      Serial.print(" is pressed, held = ");
      Serial.println(held);
    }

    void keyReleased(char key) override {
      Serial.print("Released ");
      Serial.println(key);
    }
} myListener;

void setup() {
  while (!Serial);
  Serial.begin(115200);

  //multiIoAddExpander(multiIo, ioFrom8574(0x27), 8);
  multiIoAddExpander(multiIo, outputOnlyFromShiftRegister(SR_CLK, SR_DAT, SR_LAT), 64);

  keyLayout.setColPin(0, 133);
  keyLayout.setColPin(1, 134);
  keyLayout.setColPin(2, 135);
  keyLayout.setColPin(3, 136);
  keyLayout.setColPin(4, 137);
  keyLayout.setColPin(5, 138);
  keyLayout.setColPin(6, 139);
  //k//eyLayout.setColPin(7, 132);

  keyLayout.setRowPin(0, 7);
  keyLayout.setRowPin(1, 8);
  keyLayout.setRowPin(2, 9);
  keyLayout.setRowPin(3, 10);




  // create the keyboard mapped to arduino pins and with the layout chosen above.
  // it will callback our listener
  keyboard.initialise(multiIo, &keyLayout, &myListener);

  // start repeating at 850 millis then repeat every 350ms
  keyboard.setRepeatKeyMillis(850, 350);

  Serial.println("Keyboard is initialised!");
}

void loop() {
  // as this indirectly uses taskmanager, we must include this in loop.
  taskManager.runLoop();
}
