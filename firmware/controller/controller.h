#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SPI.h>
#include <Wire.h>

#include <RF24.h>
#include "tuner.h"

#include <IoAbstraction.h>
#include <IoAbstractionWire.h>

#include <KeyboardManager.h>
#include "LiquidCrystalIO.h"


//Pines del 74HC595
#define SR_CLK 5
#define SR_DAT 4
#define SR_LAT 6

//Pines del NRF24L01
#define NRF_CE A0
#define NRF_CS A1

//Pines del roimetro
#define Vfwdpin_Anlg 6   // Forward Voltage Vfwd VDC A6
#define Vrevpin_Anlg 7   // Reverse Voltage Vrev VDC A7


enum tuner_type {
  NO_TUNER,
  TUNER_LC,
  TUNER_L,
  TUNER_C

};

enum remote_module_status {
  REMOTE_STATUS_OK,
  REMOTE_STATUS_FAULT,
  REMOTE_STATUS_COMM_ERROR
};

struct tuner {
  enum tuner_type type;
  enum remote_module_status status;
  
  int L;
  int C;
};

struct antenna_switch_status {
  enum remote_module_status status;
  int selected_antenna;
};

struct switch_preset {
  char* description;
  struct tuner* tuner;
};

struct RFInfo {
  bool rfDetected;
  float Pfwd;
  float Prev;
  float SWR;

  float AvgPfwd;
  float AvgPrev;
  float AvgSWR;

  float MaxPfwd;
  float MaxPrev;
  float MaxSWR;
};

void handleTuner(struct switch_preset* presets, RF24* radio, int selectedPreset);
void handleSwitch(antenna_switch_status* ant_switch_status, RF24* radio, int selectedAntenna);
void handleRF(RFInfo* rfInfo);
void handleLCD(LiquidCrystal* lcd, RFInfo* rfInfo, antenna_switch_status* ant_switch_status, switch_preset* preset);
#endif
