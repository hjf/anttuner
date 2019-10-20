EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20SU U1
U 1 1 5DAC5434
P 3950 3150
F 0 "U1" H 3421 3196 50  0000 R CNN
F 1 "ATtiny85-20SU" H 3421 3105 50  0000 R CNN
F 2 "Package_SO:SOIJ-8_5.3x5.3mm_P1.27mm" H 3950 3150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 3950 3150 50  0001 C CNN
	1    3950 3150
	1    0    0    -1  
$EndComp
$Comp
L RF:NRF24L01_Breakout U2
U 1 1 5DAC5AE4
P 5450 2200
F 0 "U2" V 5967 2200 50  0000 C CNN
F 1 "NRF24L01_Breakout" V 5876 2200 50  0000 C CNN
F 2 "RF_Module:nRF24L01_Breakout" H 5600 2800 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 5450 2100 50  0001 C CNN
	1    5450 2200
	0    -1   -1   0   
$EndComp
$Comp
L Interface_Expansion:TPIC6595 U?
U 1 1 5DAC8AD3
P 6900 3000
F 0 "U?" H 6900 3781 50  0000 C CNN
F 1 "TPIC6595" H 6900 3690 50  0000 C CNN
F 2 "" H 7550 2350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tpic6595.pdf" H 6900 2950 50  0001 C CNN
	1    6900 3000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
