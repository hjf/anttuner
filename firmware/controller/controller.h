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

void handleAntenna(LiquidCrystal* lcd, RF24* radio);
void handleSwitch(LiquidCrystal* lcd, RF24* radio);

#endif
