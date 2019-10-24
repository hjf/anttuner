#include "controller.h"
#include <string.h>
bool cursorStatus;
void enableCursor(LiquidCrystal* lcd);
void disableCursor(LiquidCrystal* lcd);

void printPaddedNumber(LiquidCrystal* lcd, int n, int width, char pad);
void handleLCD(LiquidCrystal* lcd, RFInfo* rfInfo, antenna_switch_status* ant_switch_status, switch_preset* preset, char pressedKey) {
  if (ant_switch_status->selected_antenna == -1) {
    lcd->setCursor(0, 0);
    lcd->print(F("ANT: "));

    lcd->print(F("   **NONE**    "));

    lcd->setCursor(0, 1);
    lcd->print(F("TUN: "));

    lcd->print(F("N/A            "));
  } else {
    switch_preset* wpreset = preset + ant_switch_status->selected_antenna;

    //seccion Antena
    lcd->setCursor(0, 0);
    lcd->print(F("ANT: "));
    if (ant_switch_status->status == REMOTE_STATUS_FAULT)
      lcd->print(F("*** FAULT ***  "));
    else if     (ant_switch_status->status == REMOTE_STATUS_COMM_ERROR)
      lcd->print(F("**COMM ERROR** "));
    else {
      lcd->print(ant_switch_status->selected_antenna + 1);
      lcd->print(F(" "));
      lcd->print(wpreset->description);
    }

    char nbuf[50];
    //seccion Tuner
    lcd->setCursor(0, 1);
    lcd->print(F("TUN: "));
    if (wpreset->tuner->type == NO_TUNER) {
      lcd->print(F("N/A            "));
    } else if (wpreset->tuner->status == REMOTE_STATUS_FAULT) {
      lcd->print(F("*** FAULT ***  "));
    } else if (wpreset->tuner->status == REMOTE_STATUS_COMM_ERROR) {
      lcd->print(F("**COMM ERROR** "));
    }  else if (wpreset->tuner->type == TUNER_L || preset->tuner->type == TUNER_LC) {
      lcd->print(F("L:"));
      if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_L) {
        //enableCursor(lcd);
        printPaddedNumber(lcd, wpreset->tuner->next_L, 5, '_');
      }    else {
        sprintf(nbuf, "%5d", wpreset->tuner->L);
        lcd->print(nbuf);
      }
    } else if (wpreset->tuner->type == TUNER_C || preset->tuner->type == TUNER_LC) {
      lcd->print(F(" C:"));
      sprintf(nbuf, "%5d", wpreset->tuner->C);
      lcd->print(nbuf);
    }


    if (wpreset->tuner->status == REMOTE_STATUS_OK && (wpreset->tuner->type == TUNER_L || preset->tuner->type == TUNER_C)) {
      lcd->print(F("        "));
    }
  }
  //seccion RF
  lcd->setCursor(0, 3);
  if (rfInfo->rfDetected == true) {
    lcd->print(F("P: "));
    lcd->print(rfInfo->Pfwd, 0);
    lcd->print(F("W SWR: "));
    lcd->print(rfInfo->SWR, 1);
    lcd->print(F("   "));
  } else {
    lcd->print(F("No RF               "));
  }
}

void printPaddedNumber(LiquidCrystal * lcd, int n, int width, char pad) {
  int count = 0;
  int num = n;
  while (num != 0)
  {
    count++;
    num /= 10;
  }
  if (count == 0)
    count++;
  for (int i = 0; i < width - count; i++)
    lcd->print(pad);
  lcd->print(n);

}

void enableCursor(LiquidCrystal * lcd) {
  if (cursorStatus)
    return;

  lcd->cursor();
  lcd->blink();

}

void disableCursor(LiquidCrystal * lcd) {
  if (!cursorStatus)
    return;
  lcd->blink();
  lcd->cursor();

}
