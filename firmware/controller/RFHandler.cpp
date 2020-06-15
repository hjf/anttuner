#include "controller.h"

float Vfwd;
float Vrev;
float last_Vfwd;
float last_Vrev;
float Afwd;
float Arev;
int RFoff;
#define DIODE_DROP 0.25
//Turn factor: (Vueltas *0,707)/50  para 13 vueltas=.18384  sino grande 0.42426406871

#define TURN_FACTOR 0.18384
void handleRF(RFInfo* rfInfo) {
  static long nextupdate = 0;
  if (millis() < nextupdate)
    return;
  nextupdate = millis() + 200;
  // reads inputs before actions can be taken
  Vfwd = analogRead(Vfwdpin_Anlg) * 2.207; // read forward voltage from RF remote directional detector
  Vfwd = constrain(Vfwd, 1, 2257); // Vfwd values must be greater than zero to rfInfo->Prevent divide by zero in rfInfo->SWR Calc
  Vrev = analogRead(Vrevpin_Anlg) * 2.207; // read forward voltage from RF remote directional detector

  /////////////////////////////////////////////////////////////////////////////////////////////
  //                RF Forward / Reverse Power and VrfInfo->SWR Calculations
  /////////////////////////////////////////////////////////////////////////////////////////////

  /*
      Step 1 = Convert Arduino A/D steps to current
         Arduino Voltage = Steps X 5 Volts / 1023
            Add Arduino V corrections for diode drop of DIODE_DROP V
          Arduino Voltage = Arduino Voltage + DIODE_DROP0
            Arduino V corrections for Vpeak to Vrms is factor of 0.707
                Tx Line V = Arduino V X 0.707 X TURN_RATIO turns ratio
        Amps = Tx Line V / 50 Ohm Termination Resistor
                     Amps = [ Steps X 5 ) / 1023 )  + DIODE_DROP0 ]  X  [ TURN_RATIO  X  0.707 /  50 ]   =  ( ( (Steps X 5) / 1023 ) + DIODE_DROP0 )  *  0.18382

    Step 2 = Convert Line current to power
      Power = 50 Ohm Line X current squared
        Power = 50 X Amps X Amps

     Step 3 = Convert forward and reverse power to VrfInfo->SWR
     VrfInfo->SWR = (1+SQRT(rfInfo->Prev/rfInfo->Pfwd)) / (1-SQRT(rfInfo->Prev/rfInfo->Pfwd))
  */
  /////////////////////////////////////////////////////////////////////////////////////////////
  float Vdiode = ( Vfwd / 1000 ); // gradual diode drop
  // Gradual diode drop factor was tested for 40M, 30M, 20M, 17M, 21M
  // Fowards Watts 0 to 25 W valid +/- 0.5 W  // 12M and 10M valid + 0 to - 1.5 W
  Vdiode = constrain(Vdiode, 0, DIODE_DROP); // limit drop to DIODE_DROP V
  Afwd =  ( (Vfwd * 5) / 1023 ) + Vdiode; // split up calculation
  Afwd =  Afwd *  TURN_FACTOR; // split up calculation
  rfInfo->Pfwd = 50 * Afwd * Afwd;
  Vdiode = ( Vrev / 1000 ); // gradual diode drop
  Vdiode = constrain(Vdiode, 0, DIODE_DROP); // limit drop to DIODE_DROP V
  Arev =  ( (Vrev * 5) / 1023 ) + Vdiode;  // split up calculation
  Arev =  Arev *  TURN_FACTOR; // split up calculation
  rfInfo->Prev = 50 * Arev * Arev;
  float fp = sqrt ( rfInfo->Prev / rfInfo->Pfwd );
  rfInfo->SWR = ( 1 + fp ) / ( 1 - fp );
  rfInfo->SWR = constrain(rfInfo->SWR, 1, 99.9); // some more than 100
  if ( rfInfo->Pfwd > 0.2 )  //  peak sample timer and no RF time out timer
  {
    if ( RFoff > 10000 )  //  average and peak timer see text (10000 long for SSB, 2000 short for QSK)
    {
      //lcd.init();  // this extra init clears and cleans up trash when on battery operation
      //lcd.clear(); // clear all
      rfInfo->MaxPfwd = 0;    // clears past peaks and averages
      rfInfo->AvgPfwd = 0;
      rfInfo->MaxPrev = 0;
      rfInfo->AvgPrev = 0;
      rfInfo->MaxSWR = 1;
      rfInfo->AvgSWR = 1;
    }

    RFoff = 1000;
  }  else {
    RFoff = RFoff + 1;  // Countdown timer
  }

  if ((( Vfwd - last_Vfwd ) > 3) ||
      (( Vfwd - last_Vfwd ) <  -3) ||
      (( Vrev - last_Vrev ) > 3) ||
      (( Vrev - last_Vrev ) <  -3)  )  // rfInfo->Previous reads are checked to reduce display flicker  // +/- 3 to filter A/D noise
  {
    //////////// Peak Hold ///////////
    if ( rfInfo->Pfwd > rfInfo->MaxPfwd )    {
      rfInfo->MaxPfwd = rfInfo->Pfwd;
    }

    if ( rfInfo->Prev > rfInfo->MaxPrev )    {
      rfInfo->MaxPrev = rfInfo->Prev;
    }

    if ( rfInfo->SWR > rfInfo->MaxSWR )    {
      rfInfo->MaxSWR = rfInfo->SWR;
    }

    ////////////////////////////////// average value integrator   Select % values to add up to 100% //   10 / 90 is fast,  5 / 95 is medium,   2 / 98 is slow

    rfInfo->AvgPfwd = ( rfInfo->AvgPfwd * 0.95 ) + ( rfInfo->Pfwd * 0.05 );   // average value integrator
    rfInfo->AvgPrev = ( rfInfo->AvgPrev * 0.95 ) + ( rfInfo->Prev * 0.05 );   // average value integrator
    rfInfo->AvgSWR = ( rfInfo->AvgSWR * 0.95 ) + ( rfInfo->SWR * 0.05 );   // average value integrator


    last_Vfwd = Vfwd;
    last_Vrev = Vrev;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////

  if ( RFoff > 10000 )  //  no RF time out
  {
    //  delay (200);     // delay
    RFoff = 12000;  //     rfInfo->Prevents overflow at 32000 and flags average, peak and display clean up on next transmit


  }
  if (rfInfo->Pfwd > 0.2) {
    rfInfo->rfDetected = true;
  }
  else {
    rfInfo->rfDetected = false;
  }
}
