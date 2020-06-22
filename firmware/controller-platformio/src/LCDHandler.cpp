#include "controller.h"
#include <string.h>
bool cursorStatus;
unsigned long lcdnextupdate = 0;
void enableCursor(LiquidCrystal *lcd);
void disableCursor(LiquidCrystal *lcd);

void printPaddedNumber(LiquidCrystal *lcd, int n, int width, char pad);

void handleLCD(LiquidCrystal *lcd, RFInfo *rfInfo, antenna_switch_status *ant_switch_status, switch_preset *preset, char pressedKey, RadioInfo *radioInfo, switch_response *psres)
{

  if (millis() < lcdnextupdate)
    return;
  lcdnextupdate = millis() + 100;

  char screenbuf[90];
  char *screenbuf_p = screenbuf;
  memset(screenbuf, 0, sizeof(screenbuf));

  sprintf(screenbuf_p, "%c ", 0x01);
  screenbuf_p = screenbuf + strlen(screenbuf);

  if (ant_switch_status->selected_antenna == -1)
  {
    sprintf(screenbuf_p, "%S", (const char *)F("       **NONE**     T N/A               "));
    screenbuf_p = screenbuf + strlen(screenbuf);
  }
  else
  {
    switch_preset *wpreset = preset + ant_switch_status->selected_antenna;

    if (ant_switch_status->status == REMOTE_STATUS_FAULT)
    {
      sprintf(screenbuf_p, "%S", (const char *)F("   *** FAULT ***  "));
      screenbuf_p = screenbuf + strlen(screenbuf);
    }
    else if (ant_switch_status->status == REMOTE_STATUS_COMM_ERROR)
    {
      sprintf(screenbuf_p, "%S", (const char *)F("  **COMM ERROR**  "));
      screenbuf_p = screenbuf + strlen(screenbuf);
    }

    else
    {
      if (ant_switch_status->rxant < 0)
        sprintf(screenbuf_p, "%d %s   ", ant_switch_status->selected_antenna + 1, wpreset->description);
      else
        sprintf(screenbuf_p, "%d %s R%d",
                ant_switch_status->selected_antenna + 1,
                wpreset->description,
                ant_switch_status->rxant + 1);
      screenbuf_p = screenbuf + strlen(screenbuf);
    }

    sprintf(screenbuf_p, "F %5d.%02d %s    %s",
            (int)(radioInfo->Frequency / 1000.0),
            (int)(((long)(radioInfo->Frequency / 10.0)) % 100),
            radioInfo->Mode,
            radioInfo->tx ? "TX" : "RX");
    screenbuf_p = screenbuf + strlen(screenbuf);

    //seccion Tuner

    sprintf(screenbuf_p, "T ");
    screenbuf_p = screenbuf + strlen(screenbuf);

    if (wpreset->tuner->type == NO_TUNER)
    {
      sprintf(screenbuf_p, "%S", (const char *)F("N/A               "));
      screenbuf_p = screenbuf + strlen(screenbuf);
    }
    else if (wpreset->tuner->status == REMOTE_STATUS_FAULT)
    {
      sprintf(screenbuf_p, "%S", (const char *)F("   *** FAULT ***  "));
      screenbuf_p = screenbuf + strlen(screenbuf);
    }
    else if (wpreset->tuner->status == REMOTE_STATUS_COMM_ERROR)
    {
      sprintf(screenbuf_p, "%S", (const char *)F("  **COMM ERROR**  "));
      screenbuf_p = screenbuf + strlen(screenbuf);
    }
    // else if (wpreset->tuner->type == TUNER_L || preset->tuner->type == TUNER_LC)
    // {
    //   lcd->print(F("L:"));
    //   if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_L)
    //   {
    //     //enableCursor(lcd);
    //     printPaddedNumber(lcd, wpreset->tuner->next_L, 5, '_');
    //   }
    //   else
    //   {
    //     sprintf(nbuf, "%5d", wpreset->tuner->L);
    //     lcd->print(nbuf);
    //   }
    // }
    // else if (wpreset->tuner->type == TUNER_C || preset->tuner->type == TUNER_LC)
    // {
    //   lcd->print(F(" C:"));
    //   sprintf(nbuf, "%5d", wpreset->tuner->C);
    //   lcd->print(nbuf);
    // }
    else if (wpreset->tuner->type == RELAY_TUNER)
    {

      if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_L)
      {
        sprintf(screenbuf_p, "%cserie: %05d      ", 0x02, wpreset->tuner->next_L);
        screenbuf_p = screenbuf + strlen(screenbuf);
      }
      else if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_L)
      {
        sprintf(screenbuf_p, "%cshunt: %05d       ", 0x02, wpreset->tuner->next_shunt_L);
        screenbuf_p = screenbuf + strlen(screenbuf);
      }
      else if (wpreset->tuner->local_status == TUNER_STATUS_CHANGING_SHUNT_C)
      {
        sprintf(screenbuf_p, "%cshunt: %05d       ", 0x03, wpreset->tuner->next_shunt_C);
        screenbuf_p = screenbuf + strlen(screenbuf);
      }
      else
      {
        sprintf(screenbuf_p, "%cSe %2d %cSh %2d %cSh%1d",
                0x02, wpreset->tuner->L,
                0x02, wpreset->tuner->shunt_L,
                0x03, wpreset->tuner->shunt_C);

        screenbuf_p = screenbuf + strlen(screenbuf);
      }
    }

    // if (wpreset->tuner->status == REMOTE_STATUS_OK &&
    //     (wpreset->tuner->type == TUNER_L || preset->tuner->type == TUNER_C))
    // {
    //   lcd->print(F("        "));
    // }
  }

  if (rfInfo->rfDetected == true)
  {
    int p = rfInfo->Pfwd + 0.5;
    sprintf(screenbuf_p, "P%3dW SWR %2d.%02d %s",
            p,
            (int)rfInfo->SWR,
            (int)(rfInfo->SWR * 100) % 100,
            ant_switch_status->autoswitching ? "AUTO" : "MANU");
    screenbuf_p = screenbuf + strlen(screenbuf);
  }
  else
  {
    sprintf(screenbuf_p, "No RF           %s",
            ant_switch_status->autoswitching ? "AUTO" : "MANU");
    screenbuf_p = screenbuf + strlen(screenbuf);
  }

  //  Serial.print(screenbuf);
  lcd->setCursor(0, 0);
  // //screenbuf[80]=0;
  lcd->write(screenbuf, 80);
}

void printPaddedNumber(LiquidCrystal *lcd, int n, int width, char pad)
{
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

void enableCursor(LiquidCrystal *lcd)
{
  if (cursorStatus)
    return;

  lcd->cursor();
  lcd->blink();
}

void disableCursor(LiquidCrystal *lcd)
{
  if (!cursorStatus)
    return;
  lcd->blink();
  lcd->cursor();
}
