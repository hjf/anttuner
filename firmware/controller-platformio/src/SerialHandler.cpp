#include "controller.h"

unsigned long f_query_timer;
char radioBuf[64];
unsigned char radioBufPtr;
AltSoftSerial altSerial;

void HandleSerial(RadioInfo *radioInfo)
{
  static byte prevread;
  //  if (!altSerial.available() && !Serial.available())
  //    return;
  for (char i = 0; i < 64; i++)
  {
  REDO:
    if (radioBufPtr > sizeof(radioBuf))
      radioBufPtr = 0;

    while (altSerial.available())
    {
      i = 0;
      f_query_timer = millis() + 5000;
      byte alt = altSerial.read();
      Serial.write(alt);
      radioBuf[radioBufPtr++] = alt;

      if (alt == ';')
      {

        radioBufPtr = 0;

        if (radioBuf[0] == 'I' && radioBuf[1] == 'F')
        {
          radioBuf[13] = 0;
          radioInfo->Frequency = atol(radioBuf + 2);

          String mode;
          switch (radioBuf[29])
          {
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
          mode.toCharArray(radioInfo->Mode, 4);
        }
      }
    }

    while (Serial.available())
    {
      f_query_timer = millis() + 5000;
      byte cur_read = Serial.read();
      if (prevread == 'T' && cur_read == 'X')
      {
        radioInfo->tx = true;
      }
      if (prevread == 'R' && cur_read == 'X')
      {
        radioInfo->tx = false;
      }
      altSerial.write(cur_read);
      prevread = cur_read;
      if (cur_read == ';')
      {
        //        unsigned long bail = millis() + 500;
        //        while (!altSerial.available()) {
        //          if (millis() > bail)
        //            goto BAIL;
        //        }
        goto REDO;
      }
    }
    if (millis() > f_query_timer)
    {
      f_query_timer = millis() + 2000;
      altSerial.print("IF;");
    }
    delayMicroseconds(250);
    //taskManager.runLoop();
  }
}
