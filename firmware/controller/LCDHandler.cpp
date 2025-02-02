#include "controller.h"
#include <string.h>
bool cursorStatus;
long lcdnextupdate = 0;
void enableCursor(LiquidCrystal* lcd);
void disableCursor(LiquidCrystal* lcd);

void printPaddedNumber(LiquidCrystal* lcd, int n, int width, char pad);
void handleLCD(LiquidCrystal* lcd, RFInfo* rfInfo, antenna_switch_status* ant_switch_status, switch_preset* preset, char pressedKey, RadioInfo* radioInfo, switch_response* psres) {

  if (millis() < lcdnextupdate)
    return;
  lcdnextupdate = millis() + 200;

  if (ant_switch_status->selected_antenna == -1) {
    lcd->setCursor(0, 0);
    lcd->write(byte(1));
    lcd->print(F(" "));

    lcd->print(F("      **NONE**    "));

    lcd->setCursor(0, 1);
    lcd->print(F("T "));

    lcd->print(F("N/A               "));
  } else {
    switch_preset* wpreset = preset + ant_switch_status->selected_antenna;

    //seccion Antena
    lcd->setCursor(0, 0);
    lcd->write(byte(1));
    lcd->print(F(" "));
    if (ant_switch_status->status == REMOTE_STATUS_FAULT)
      lcd->print(F("   *** FAULT ***  "));
    else if     (ant_switch_status->status == REMOTE_STATUS_COMM_ERROR)
      lcd->print(F("  **COMM ERROR**  "));
    else {
      lcd->print(ant_switch_status->selected_antenna + 1);
      lcd->print(F(" "));
      lcd->print(wpreset->description);
    }

    char nbuf[50];
    //seccion Tuner
    lcd->setCursor(0, 1);
    lcd->print(F("T "));
    if (wpreset->tuner->type == NO_TUNER) {
      lcd->print(F("N/A               "));
    } else if (wpreset->tuner->status == REMOTE_STATUS_FAULT) {
      lcd->print(F("   *** FAULT ***  "));
    } else if (wpreset->tuner->status == REMOTE_STATUS_COMM_ERROR) {
      lcd->print(F("  **COMM ERROR**  "));
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
    } else if (wpreset->tuner->type == RELAY_TUNER) {

      if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_L) {
        lcd->write(byte(2));
        lcd->print(F("serie: "));
        printPaddedNumber(lcd, wpreset->tuner->next_L, 5, '_');
      } else if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_L) {
        lcd->write(byte(2));
        lcd->print(F("shunt: "));
        printPaddedNumber(lcd, wpreset->tuner->next_shunt_L, 5, '_');
      }  else if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_C) {
        lcd->write(byte(3));
        lcd->print(F("shunt: "));
        printPaddedNumber(lcd, wpreset->tuner->next_shunt_C, 5, '_');
      }      else {
        lcd->write(byte(2));
        sprintf(nbuf, "Se %2d,", wpreset->tuner->L);
        lcd->print(nbuf);
        lcd->write(byte(2));
        sprintf(nbuf, "Sh %2d,", wpreset->tuner->shunt_L);
        lcd->print(nbuf);
        lcd->write(byte(3));
        sprintf(nbuf, "Sh%1d", wpreset->tuner->shunt_C);
        lcd->print(nbuf);
      }
    }




    if (wpreset->tuner->status == REMOTE_STATUS_OK && (wpreset->tuner->type == TUNER_L || preset->tuner->type == TUNER_C)) {
      lcd->print(F("        "));
    }
  }
  //seccion RF

  lcd->setCursor(0, 2);
  lcd->print(F("F "));
  if (radioInfo->Frequency < 10000)
    lcd->print(F(" "));
  if (radioInfo->Frequency < 100000)
    lcd->print(F(" "));
  if (radioInfo->Frequency < 1000000)
    lcd->print(F(" "));
  if (radioInfo->Frequency < 10000000)
    lcd->print(F(" "));
  lcd->print(radioInfo->Frequency / 1000.0);
  lcd->print(F(" "));
  lcd->print(radioInfo->Mode);
  lcd->print(F(" "));



  lcd->setCursor(0, 3);
  if (rfInfo->rfDetected == true) {
    lcd->print(F("P "));
    int p = rfInfo->Pfwd + 0.5;
    if(p<100)
    lcd->print(F(" "));
    lcd->print(p);
    lcd->print(F("W SWR "));
    lcd->print(rfInfo->SWR, 2);
    if (ant_switch_status->autoswitching)
      lcd->print(F(" AUTO"));
    else
      lcd->print(F(" MANU"));
  } else {

    if (ant_switch_status->autoswitching)
      lcd->print(F("No RF           AUTO"));
    else
      lcd->print(F("No RF           MANU"));
    //lcd->print(psres->temperature);
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
