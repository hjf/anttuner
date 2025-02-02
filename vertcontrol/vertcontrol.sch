EESchema Schematic File Version 4
LIBS:vertcontrol-cache
EELAYER 29 0
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
L vertcontrol-rescue:ATtiny44-20SSU-MCU_Microchip_ATtiny U1
U 1 1 5DA400FE
P 4100 3150
F 0 "U1" H 3571 3196 50  0000 R CNN
F 1 "ATtiny44-20SSU" H 3571 3105 50  0000 R CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 4100 3150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8006.pdf" H 4100 3150 50  0001 C CNN
	1    4100 3150
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:Pololu_Breakout_DRV8825-Driver_Motor A1
U 1 1 5DA40908
P 6900 4300
F 0 "A1" H 6900 5081 50  0000 C CNN
F 1 "Pololu_Breakout_DRV8825" H 6900 4990 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 7100 3500 50  0001 L CNN
F 3 "https://www.pololu.com/product/2982" H 7000 4000 50  0001 C CNN
	1    6900 4300
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:NRF24L01_Breakout-RF U2
U 1 1 5DA416FA
P 9500 3350
F 0 "U2" H 9880 3396 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 9880 3305 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 9650 3950 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 9500 3250 50  0001 C CNN
	1    9500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3250 4950 3250
Wire Wire Line
	4700 3150 4950 3150
Wire Wire Line
	4950 3050 4700 3050
Wire Wire Line
	4700 2950 4950 2950
Wire Wire Line
	4700 2550 4950 2550
Wire Wire Line
	4700 2750 4950 2750
Text GLabel 4950 3150 2    50   Input ~ 0
MISO
Text GLabel 4950 3050 2    50   Input ~ 0
MOSI
Text GLabel 4950 2950 2    50   Input ~ 0
MCLK
Text GLabel 8800 3050 0    50   Input ~ 0
MOSI
Text GLabel 8800 3150 0    50   Input ~ 0
MISO
Text GLabel 8800 3250 0    50   Input ~ 0
MCLK
Text GLabel 8800 3350 0    50   Input ~ 0
CSN
Text GLabel 8800 3550 0    50   Input ~ 0
CE
$Comp
L vertcontrol-rescue:VDD-power #PWR0101
U 1 1 5DA448F9
P 9500 2050
F 0 "#PWR0101" H 9500 1900 50  0001 C CNN
F 1 "VDD" H 9517 2223 50  0000 C CNN
F 2 "" H 9500 2050 50  0001 C CNN
F 3 "" H 9500 2050 50  0001 C CNN
	1    9500 2050
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:GND-power #PWR0102
U 1 1 5DA44F3D
P 9500 4100
F 0 "#PWR0102" H 9500 3850 50  0001 C CNN
F 1 "GND" H 9505 3927 50  0000 C CNN
F 2 "" H 9500 4100 50  0001 C CNN
F 3 "" H 9500 4100 50  0001 C CNN
	1    9500 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 3950 9500 4100
Wire Wire Line
	8800 3550 9000 3550
Wire Wire Line
	9000 3350 8800 3350
Wire Wire Line
	8800 3250 9000 3250
Wire Wire Line
	9000 3150 8800 3150
Wire Wire Line
	8800 3050 9000 3050
$Comp
L vertcontrol-rescue:Q_PMOS_GSD-Device Q1
U 1 1 5DA46AE7
P 9600 2400
F 0 "Q1" H 9805 2354 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 9805 2445 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9800 2500 50  0001 C CNN
F 3 "~" H 9600 2400 50  0001 C CNN
	1    9600 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	9500 2050 9500 2200
Wire Wire Line
	9500 2600 9500 2750
Text GLabel 4950 2850 2    50   Input ~ 0
CSN
Text GLabel 4950 2750 2    50   Input ~ 0
CE
Wire Wire Line
	4950 2850 4700 2850
$Comp
L vertcontrol-rescue:VDD-power #PWR0103
U 1 1 5DA4C645
P 4100 2000
F 0 "#PWR0103" H 4100 1850 50  0001 C CNN
F 1 "VDD" H 4117 2173 50  0000 C CNN
F 2 "" H 4100 2000 50  0001 C CNN
F 3 "" H 4100 2000 50  0001 C CNN
	1    4100 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2000 4100 2150
$Comp
L vertcontrol-rescue:GND-power #PWR0104
U 1 1 5DA4D1C9
P 4100 4300
F 0 "#PWR0104" H 4100 4050 50  0001 C CNN
F 1 "GND" H 4105 4127 50  0000 C CNN
F 2 "" H 4100 4300 50  0001 C CNN
F 3 "" H 4100 4300 50  0001 C CNN
	1    4100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4300 4100 4050
$Comp
L vertcontrol-rescue:C-Device C1
U 1 1 5DA4D956
P 4250 2150
F 0 "C1" V 3998 2150 50  0000 C CNN
F 1 "100n" V 4089 2150 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4288 2000 50  0001 C CNN
F 3 "~" H 4250 2150 50  0001 C CNN
	1    4250 2150
	0    1    1    0   
$EndComp
Connection ~ 4100 2150
Wire Wire Line
	4100 2150 4100 2250
$Comp
L vertcontrol-rescue:GND-power #PWR0105
U 1 1 5DA4E256
P 4400 2150
F 0 "#PWR0105" H 4400 1900 50  0001 C CNN
F 1 "GND" H 4405 1977 50  0000 C CNN
F 2 "" H 4400 2150 50  0001 C CNN
F 3 "" H 4400 2150 50  0001 C CNN
	1    4400 2150
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:R-Device R1
U 1 1 5DA4F7CB
P 10100 2400
F 0 "R1" V 9893 2400 50  0000 C CNN
F 1 "1K" V 9984 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 10030 2400 50  0001 C CNN
F 3 "~" H 10100 2400 50  0001 C CNN
	1    10100 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 2650 5150 2650
Wire Wire Line
	9800 2400 9950 2400
Wire Wire Line
	10250 2400 10400 2400
Text GLabel 10400 2400 2    50   Input ~ 0
NRF_PWR
Text GLabel 5150 2650 2    50   Input ~ 0
NRF_PWR
Text GLabel 4950 3450 2    50   Input ~ 0
MOT_EN
Text GLabel 6200 4300 0    50   Input ~ 0
MOT_EN
Wire Wire Line
	6200 4300 6500 4300
Wire Wire Line
	4700 3450 4950 3450
Wire Wire Line
	4700 3550 4950 3550
Wire Wire Line
	4700 3650 4950 3650
Wire Wire Line
	4700 3750 4800 3750
Wire Wire Line
	6500 4400 6200 4400
Wire Wire Line
	6500 4500 6200 4500
Text GLabel 6200 4400 0    50   Input ~ 0
MOT_STEP
Text GLabel 6200 4500 0    50   Input ~ 0
MOT_DIR
Text GLabel 4950 3650 2    50   Input ~ 0
MOT_STEP
Text GLabel 4950 3250 2    50   Input ~ 0
MOT_DIR
Wire Wire Line
	6500 4000 6250 4000
Wire Wire Line
	6250 4000 6250 4100
Wire Wire Line
	6250 4100 6500 4100
$Comp
L vertcontrol-rescue:VDD-power #PWR0106
U 1 1 5DA5F8E6
P 6250 4100
F 0 "#PWR0106" H 6250 3950 50  0001 C CNN
F 1 "VDD" V 6268 4227 50  0000 L CNN
F 2 "" H 6250 4100 50  0001 C CNN
F 3 "" H 6250 4100 50  0001 C CNN
	1    6250 4100
	0    -1   -1   0   
$EndComp
Connection ~ 6250 4100
Text GLabel 6200 3900 0    50   Input ~ 0
MOT_FLT
Wire Wire Line
	6200 3900 6500 3900
Text GLabel 4950 3550 2    50   Input ~ 0
MOT_FLT
$Comp
L vertcontrol-rescue:VDD-power #PWR0107
U 1 1 5DA61B84
P 7850 1550
F 0 "#PWR0107" H 7850 1400 50  0001 C CNN
F 1 "VDD" V 7867 1678 50  0000 L CNN
F 2 "" H 7850 1550 50  0001 C CNN
F 3 "" H 7850 1550 50  0001 C CNN
	1    7850 1550
	0    1    1    0   
$EndComp
$Comp
L vertcontrol-rescue:R-Device R2
U 1 1 5DA63062
P 7250 1750
F 0 "R2" H 7180 1704 50  0000 R CNN
F 1 "1K" H 7180 1795 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7180 1750 50  0001 C CNN
F 3 "~" H 7250 1750 50  0001 C CNN
	1    7250 1750
	-1   0    0    1   
$EndComp
$Comp
L vertcontrol-rescue:R-Device R3
U 1 1 5DA63600
P 7250 2200
F 0 "R3" H 7180 2154 50  0000 R CNN
F 1 "1K" H 7180 2245 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7180 2200 50  0001 C CNN
F 3 "~" H 7250 2200 50  0001 C CNN
	1    7250 2200
	-1   0    0    1   
$EndComp
$Comp
L vertcontrol-rescue:C-Device C3
U 1 1 5DA63C09
P 7600 1800
F 0 "C3" H 7485 1754 50  0000 R CNN
F 1 "100n" H 7485 1845 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7638 1650 50  0001 C CNN
F 3 "~" H 7600 1800 50  0001 C CNN
	1    7600 1800
	-1   0    0    1   
$EndComp
$Comp
L vertcontrol-rescue:C-Device C2
U 1 1 5DA65BFA
P 6250 1750
F 0 "C2" H 6135 1704 50  0000 R CNN
F 1 "100n" H 6135 1795 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6288 1600 50  0001 C CNN
F 3 "~" H 6250 1750 50  0001 C CNN
	1    6250 1750
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 1600 5850 1600
Wire Wire Line
	6250 1600 6500 1600
Connection ~ 6250 1600
Wire Wire Line
	7100 1600 7250 1600
Wire Wire Line
	7600 1600 7600 1650
Wire Wire Line
	7250 1600 7600 1600
Connection ~ 7250 1600
Connection ~ 7600 1600
Wire Wire Line
	7250 1900 7250 2000
Wire Wire Line
	7250 2000 6800 2000
Wire Wire Line
	6800 2000 6800 1900
Connection ~ 7250 2000
Wire Wire Line
	7250 2000 7250 2050
Wire Wire Line
	7600 1950 7600 2350
Wire Wire Line
	7600 2350 7250 2350
$Comp
L vertcontrol-rescue:GND-power #PWR0108
U 1 1 5DA6BD5E
P 6250 2100
F 0 "#PWR0108" H 6250 1850 50  0001 C CNN
F 1 "GND" H 6255 1927 50  0000 C CNN
F 2 "" H 6250 2100 50  0001 C CNN
F 3 "" H 6250 2100 50  0001 C CNN
	1    6250 2100
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:GND-power #PWR0109
U 1 1 5DA6C148
P 7600 2350
F 0 "#PWR0109" H 7600 2100 50  0001 C CNN
F 1 "GND" H 7605 2177 50  0000 C CNN
F 2 "" H 7600 2350 50  0001 C CNN
F 3 "" H 7600 2350 50  0001 C CNN
	1    7600 2350
	1    0    0    -1  
$EndComp
Connection ~ 7600 2350
Wire Wire Line
	6250 2100 6250 1900
$Comp
L vertcontrol-rescue:LM317_3PinPackage-Regulator_Linear U3
U 1 1 5DA6EB60
P 6800 1600
F 0 "U3" H 6800 1842 50  0000 C CNN
F 1 "LM317_3PinPackage" H 6800 1751 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 6800 1850 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 6800 1600 50  0001 C CNN
	1    6800 1600
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:R-Device R4
U 1 1 5DA7555B
P 4950 4000
F 0 "R4" H 5020 4046 50  0000 L CNN
F 1 "1K" H 5020 3955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4880 4000 50  0001 C CNN
F 3 "~" H 4950 4000 50  0001 C CNN
	1    4950 4000
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:VDD-power #PWR0110
U 1 1 5DA772B9
P 4950 4250
F 0 "#PWR0110" H 4950 4100 50  0001 C CNN
F 1 "VDD" H 4968 4423 50  0000 C CNN
F 2 "" H 4950 4250 50  0001 C CNN
F 3 "" H 4950 4250 50  0001 C CNN
	1    4950 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 3750 4950 3850
Wire Wire Line
	4950 4150 4950 4250
$Comp
L vertcontrol-rescue:GND-power #PWR0111
U 1 1 5DA7D4E9
P 6900 5300
F 0 "#PWR0111" H 6900 5050 50  0001 C CNN
F 1 "GND" H 6905 5127 50  0000 C CNN
F 2 "" H 6900 5300 50  0001 C CNN
F 3 "" H 6900 5300 50  0001 C CNN
	1    6900 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5100 6900 5100
Wire Wire Line
	6900 5100 6900 5200
Connection ~ 6900 5100
$Comp
L vertcontrol-rescue:Conn_01x06-Connector_Generic J1
U 1 1 5DA80647
P 8150 4300
F 0 "J1" H 8230 4292 50  0000 L CNN
F 1 "Conn_01x06" H 8230 4201 50  0000 L CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MCV_1,5_6-G-5.08_1x06_P5.08mm_Vertical" H 8150 4300 50  0001 C CNN
F 3 "~" H 8150 4300 50  0001 C CNN
	1    8150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4300 7650 4300
Wire Wire Line
	7650 4300 7650 4100
Wire Wire Line
	7650 4100 7950 4100
Wire Wire Line
	7300 4200 7950 4200
Wire Wire Line
	7300 4500 7700 4500
Wire Wire Line
	7700 4500 7700 4300
Wire Wire Line
	7700 4300 7950 4300
Wire Wire Line
	7300 4600 7750 4600
Wire Wire Line
	7750 4600 7750 4400
Wire Wire Line
	7750 4400 7950 4400
Wire Wire Line
	7950 4500 7800 4500
Wire Wire Line
	7800 4500 7800 4800
Wire Wire Line
	7950 4600 7950 4800
$Comp
L vertcontrol-rescue:GND-power #PWR0112
U 1 1 5DA8C118
P 7800 4800
F 0 "#PWR0112" H 7800 4550 50  0001 C CNN
F 1 "GND" H 7805 4627 50  0000 C CNN
F 2 "" H 7800 4800 50  0001 C CNN
F 3 "" H 7800 4800 50  0001 C CNN
	1    7800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3700 6900 3450
Text GLabel 6900 3450 1    50   Input ~ 0
VMOT
Text GLabel 7950 4800 3    50   Input ~ 0
VMOT
$Comp
L vertcontrol-rescue:CP-Device C4
U 1 1 5DA90224
P 8800 5450
F 0 "C4" H 8918 5496 50  0000 L CNN
F 1 "CP" H 8918 5405 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P5.00mm" H 8838 5300 50  0001 C CNN
F 3 "~" H 8800 5450 50  0001 C CNN
	1    8800 5450
	1    0    0    -1  
$EndComp
Text GLabel 8700 5150 0    50   Input ~ 0
VMOT
$Comp
L vertcontrol-rescue:GND-power #PWR0113
U 1 1 5DA90D28
P 8800 5750
F 0 "#PWR0113" H 8800 5500 50  0001 C CNN
F 1 "GND" H 8805 5577 50  0000 C CNN
F 2 "" H 8800 5750 50  0001 C CNN
F 3 "" H 8800 5750 50  0001 C CNN
	1    8800 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 5150 8800 5150
Wire Wire Line
	8800 5150 8800 5300
Wire Wire Line
	8800 5600 8800 5750
$Comp
L vertcontrol-rescue:L-Device L1
U 1 1 5DA94BE9
P 5600 1600
F 0 "L1" V 5790 1600 50  0000 C CNN
F 1 "L" V 5699 1600 50  0000 C CNN
F 2 "Inductor_SMD:L_Taiyo-Yuden_MD-3030" H 5600 1600 50  0001 C CNN
F 3 "~" H 5600 1600 50  0001 C CNN
	1    5600 1600
	0    -1   -1   0   
$EndComp
Text GLabel 5450 1600 0    50   Input ~ 0
VMOT
$Comp
L vertcontrol-rescue:CP-Device C5
U 1 1 5DA97C44
P 5850 1750
F 0 "C5" H 5968 1796 50  0000 L CNN
F 1 "CP" H 5968 1705 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.8" H 5888 1600 50  0001 C CNN
F 3 "~" H 5850 1750 50  0001 C CNN
	1    5850 1750
	1    0    0    -1  
$EndComp
Connection ~ 5850 1600
Wire Wire Line
	5850 1600 6250 1600
$Comp
L vertcontrol-rescue:GND-power #PWR0114
U 1 1 5DA98171
P 5850 2100
F 0 "#PWR0114" H 5850 1850 50  0001 C CNN
F 1 "GND" H 5855 1927 50  0000 C CNN
F 2 "" H 5850 2100 50  0001 C CNN
F 3 "" H 5850 2100 50  0001 C CNN
	1    5850 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1900 5850 2100
$Comp
L vertcontrol-rescue:CAPACITOR3PIN-murata C6
U 1 1 5DAA4947
P 9000 1100
F 0 "C6" V 8884 1338 60  0000 L CNN
F 1 "CAPACITOR3PIN" V 8990 1338 60  0000 L CNN
F 2 "mura:MURATA_SUPERCAP" H 9000 1100 60  0001 C CNN
F 3 "" H 9000 1100 60  0001 C CNN
	1    9000 1100
	0    1    1    0   
$EndComp
$Comp
L vertcontrol-rescue:VDD-power #PWR0115
U 1 1 5DAA5E6A
P 8650 1750
F 0 "#PWR0115" H 8650 1600 50  0001 C CNN
F 1 "VDD" H 8668 1923 50  0000 C CNN
F 2 "" H 8650 1750 50  0001 C CNN
F 3 "" H 8650 1750 50  0001 C CNN
	1    8650 1750
	-1   0    0    1   
$EndComp
$Comp
L vertcontrol-rescue:GND-power #PWR0116
U 1 1 5DAA692E
P 9150 1600
F 0 "#PWR0116" H 9150 1350 50  0001 C CNN
F 1 "GND" H 9155 1427 50  0000 C CNN
F 2 "" H 9150 1600 50  0001 C CNN
F 3 "" H 9150 1600 50  0001 C CNN
	1    9150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 1300 9150 1450
$Comp
L vertcontrol-rescue:R-Device R6
U 1 1 5DAABF1B
P 4450 5550
F 0 "R6" H 4520 5596 50  0000 L CNN
F 1 "1K" H 4520 5505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4380 5550 50  0001 C CNN
F 3 "~" H 4450 5550 50  0001 C CNN
	1    4450 5550
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:R-Device R5
U 1 1 5DAAC2AB
P 4450 5150
F 0 "R5" H 4520 5196 50  0000 L CNN
F 1 "1K" H 4520 5105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4380 5150 50  0001 C CNN
F 3 "~" H 4450 5150 50  0001 C CNN
	1    4450 5150
	1    0    0    -1  
$EndComp
$Comp
L vertcontrol-rescue:GND-power #PWR0117
U 1 1 5DAAC68F
P 4450 5800
F 0 "#PWR0117" H 4450 5550 50  0001 C CNN
F 1 "GND" H 4455 5627 50  0000 C CNN
F 2 "" H 4450 5800 50  0001 C CNN
F 3 "" H 4450 5800 50  0001 C CNN
	1    4450 5800
	1    0    0    -1  
$EndComp
Text GLabel 4450 4900 1    50   Input ~ 0
VMOT
Wire Wire Line
	4450 4900 4450 5000
Wire Wire Line
	4450 5300 4450 5350
Wire Wire Line
	4450 5700 4450 5800
Wire Wire Line
	4450 5350 4750 5350
Connection ~ 4450 5350
Wire Wire Line
	4450 5350 4450 5400
Text GLabel 4750 5350 2    50   Input ~ 0
VSENSE
Text GLabel 4950 2550 2    50   Input ~ 0
VSENSE
$Comp
L vertcontrol-rescue:TestPoint-Connector TP1
U 1 1 5DAC23D8
P 4800 3750
F 0 "TP1" H 4742 3776 50  0000 R CNN
F 1 "TestPoint" H 4742 3867 50  0000 R CNN
F 2 "TestPoint:TestPoint_Pad_2.5x2.5mm" H 5000 3750 50  0001 C CNN
F 3 "~" H 5000 3750 50  0001 C CNN
	1    4800 3750
	-1   0    0    1   
$EndComp
Connection ~ 4800 3750
Wire Wire Line
	4800 3750 4950 3750
$Comp
L vertcontrol-rescue:R-Device R7
U 1 1 5DAC5D69
P 8650 1500
F 0 "R7" H 8580 1454 50  0000 R CNN
F 1 "1K" H 8580 1545 50  0000 R CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 8580 1500 50  0001 C CNN
F 3 "~" H 8650 1500 50  0001 C CNN
	1    8650 1500
	-1   0    0    1   
$EndComp
$Comp
L vertcontrol-rescue:D_Schottky-Device D1
U 1 1 5DAC672D
P 8350 1450
F 0 "D1" V 8396 1371 50  0000 R CNN
F 1 "D_Schottky" V 8305 1371 50  0000 R CNN
F 2 "Diode_SMD:D_SMA" H 8350 1450 50  0001 C CNN
F 3 "~" H 8350 1450 50  0001 C CNN
	1    8350 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8650 1750 8650 1650
Wire Wire Line
	8650 1350 8650 1300
Wire Wire Line
	8650 1300 8350 1300
Connection ~ 8650 1300
Wire Wire Line
	8350 1600 8350 1650
Wire Wire Line
	8350 1650 8650 1650
Connection ~ 8650 1650
$Comp
L vertcontrol-rescue:R-Device R8
U 1 1 5DAD3D9C
P 8700 750
F 0 "R8" V 8907 750 50  0000 C CNN
F 1 "1K" V 8816 750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8630 750 50  0001 C CNN
F 3 "~" H 8700 750 50  0001 C CNN
	1    8700 750 
	0    -1   -1   0   
$EndComp
$Comp
L vertcontrol-rescue:R-Device R9
U 1 1 5DAD41C9
P 9100 750
F 0 "R9" V 9307 750 50  0000 C CNN
F 1 "1K" V 9216 750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9030 750 50  0001 C CNN
F 3 "~" H 9100 750 50  0001 C CNN
	1    9100 750 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9250 750  9400 750 
Wire Wire Line
	9400 750  9400 1450
Wire Wire Line
	9400 1450 9150 1450
Connection ~ 9150 1450
Wire Wire Line
	9150 1450 9150 1600
Wire Wire Line
	8350 1300 8350 800 
Wire Wire Line
	8350 800  8550 800 
Wire Wire Line
	8550 800  8550 750 
Connection ~ 8350 1300
Wire Wire Line
	8900 1300 8900 750 
Wire Wire Line
	8900 750  8850 750 
Wire Wire Line
	8950 750  8900 750 
Connection ~ 8900 750 
$Comp
L vertcontrol-rescue:D_Schottky-Device D2
U 1 1 5DAED8B2
P 7700 1300
F 0 "D2" V 7746 1221 50  0000 R CNN
F 1 "D_Schottky" V 7655 1221 50  0000 R CNN
F 2 "Diode_SMD:D_SMA" H 7700 1300 50  0001 C CNN
F 3 "~" H 7700 1300 50  0001 C CNN
	1    7700 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	7850 1550 7850 1300
Wire Wire Line
	7550 1300 7550 1500
Wire Wire Line
	7550 1500 7600 1500
Wire Wire Line
	7600 1500 7600 1600
Wire Wire Line
	6500 4700 6200 4700
Wire Wire Line
	6200 4700 6200 4800
Wire Wire Line
	6200 5200 6900 5200
Connection ~ 6900 5200
Wire Wire Line
	6900 5200 6900 5300
Wire Wire Line
	6500 4900 6200 4900
Connection ~ 6200 4900
Wire Wire Line
	6200 4900 6200 5200
Wire Wire Line
	6500 4800 6200 4800
Connection ~ 6200 4800
Wire Wire Line
	6200 4800 6200 4900
$EndSCHEMATC
