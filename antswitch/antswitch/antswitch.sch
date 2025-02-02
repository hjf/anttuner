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
L antswitch-rescue:ATmega168-20MU-MCU_Microchip_ATmega U1
U 1 1 5DA7E959
P 3900 3550
F 0 "U1" H 3900 1961 50  0000 C CNN
F 1 "ATmega168-20MU" H 3900 1870 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-32-1EP_5x5mm_P0.5mm_EP3.1x3.1mm" H 3900 3550 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2545-8-bit-AVR-Microcontroller-ATmega48-88-168_Datasheet.pdf" H 3900 3550 50  0001 C CNN
	1    3900 3550
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:NRF24L01_Breakout-RF U2
U 1 1 5DA7F3A2
P 6300 1650
F 0 "U2" H 6680 1696 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 6680 1605 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 6450 2250 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 6300 1550 50  0001 C CNN
	1    6300 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2850 4900 2850
Wire Wire Line
	4500 2750 4900 2750
Wire Wire Line
	4900 2650 4500 2650
Text GLabel 4900 2850 2    50   Input ~ 0
MCLK
Text GLabel 4900 2650 2    50   Input ~ 0
MOSI
Text GLabel 4900 2750 2    50   Input ~ 0
MISO
Text GLabel 5550 1350 0    50   Input ~ 0
MOSI
Text GLabel 5550 1450 0    50   Input ~ 0
MISO
Text GLabel 5550 1550 0    50   Input ~ 0
MCLK
Wire Wire Line
	5550 1350 5800 1350
Wire Wire Line
	5800 1450 5550 1450
Wire Wire Line
	5550 1550 5800 1550
Text GLabel 5550 1650 0    50   Input ~ 0
NRF_CS
Text GLabel 5550 1850 0    50   Input ~ 0
NRF_CE
Wire Wire Line
	5550 1650 5800 1650
Wire Wire Line
	5800 1850 5550 1850
Text GLabel 4900 2550 2    50   Input ~ 0
NRF_CS
Text GLabel 4900 2450 2    50   Input ~ 0
NRF_CE
Wire Wire Line
	4500 2450 4900 2450
Wire Wire Line
	4900 2550 4500 2550
$Comp
L antswitch-rescue:ULN2003-Transistor_Array U3
U 1 1 5DA84D1E
P 6300 3450
F 0 "U3" H 6300 4117 50  0000 C CNN
F 1 "ULN2003" H 6300 4026 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 6350 2900 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 6400 3250 50  0001 C CNN
	1    6300 3450
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:ULN2003-Transistor_Array U4
U 1 1 5DA86212
P 6300 4750
F 0 "U4" H 6300 5417 50  0000 C CNN
F 1 "ULN2003" H 6300 5326 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 6350 4200 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 6400 4550 50  0001 C CNN
	1    6300 4750
	1    0    0    -1  
$EndComp
Entry Wire Line
	5150 3350 5250 3450
Entry Wire Line
	5150 3450 5250 3550
Entry Wire Line
	5150 3550 5250 3650
Entry Wire Line
	5150 3650 5250 3750
Entry Wire Line
	5150 3750 5250 3850
Entry Wire Line
	5150 3250 5250 3350
Entry Wire Line
	5250 3350 5350 3250
Entry Wire Line
	5250 3450 5350 3350
Entry Wire Line
	5250 3550 5350 3450
Entry Wire Line
	5250 3650 5350 3550
Entry Wire Line
	5250 3750 5350 3650
Entry Wire Line
	5250 3850 5350 3750
Wire Wire Line
	4500 3250 5150 3250
Wire Wire Line
	4500 3350 5150 3350
Wire Wire Line
	4500 3450 5150 3450
Wire Wire Line
	5150 3550 4500 3550
Wire Wire Line
	4500 3650 5150 3650
Wire Wire Line
	5150 3750 4500 3750
Wire Wire Line
	5900 3250 5350 3250
Wire Wire Line
	5350 3350 5900 3350
Wire Wire Line
	5900 3450 5350 3450
Wire Wire Line
	5350 3550 5900 3550
Wire Wire Line
	5900 3650 5350 3650
Wire Wire Line
	5350 3750 5750 3750
Text Label 4700 3450 0    50   ~ 0
AD2
Text Label 5550 3750 0    50   ~ 0
AD0
Text Label 5550 3650 0    50   ~ 0
AD1
Text Label 5550 3450 0    50   ~ 0
AD3
Text Label 5550 3550 0    50   ~ 0
AD2
Text Label 5550 3350 0    50   ~ 0
AD4
Text Label 5550 3250 0    50   ~ 0
AD5
Wire Wire Line
	5900 3850 5750 3850
Wire Wire Line
	5750 3850 5750 3750
Connection ~ 5750 3750
Wire Wire Line
	5750 3750 5900 3750
Wire Wire Line
	6700 3850 6950 3850
Wire Wire Line
	6950 3850 6950 3750
Wire Wire Line
	6950 3750 6700 3750
Wire Wire Line
	6950 3750 7100 3750
Connection ~ 6950 3750
Wire Wire Line
	6700 3650 7100 3650
Wire Wire Line
	7100 3550 6700 3550
Wire Wire Line
	6700 3450 7100 3450
Wire Wire Line
	7100 3350 6700 3350
Wire Wire Line
	6700 3250 7100 3250
$Comp
L antswitch-rescue:Conn_01x06_Female-Connector J1
U 1 1 5DA9751B
P 7300 3450
F 0 "J1" H 7328 3426 50  0000 L CNN
F 1 "Conn_01x06_Female" H 7328 3335 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7300 3450 50  0001 C CNN
F 3 "~" H 7300 3450 50  0001 C CNN
	1    7300 3450
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:Conn_01x06_Female-Connector J2
U 1 1 5DA9E264
P 7300 4750
F 0 "J2" H 7328 4726 50  0000 L CNN
F 1 "Conn_01x06_Female" H 7328 4635 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7300 4750 50  0001 C CNN
F 3 "~" H 7300 4750 50  0001 C CNN
	1    7300 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 4550 7100 4550
Wire Wire Line
	7100 4650 6700 4650
Wire Wire Line
	6700 4750 7100 4750
Wire Wire Line
	7100 4850 6700 4850
Wire Wire Line
	6700 4950 7100 4950
Wire Wire Line
	7100 5050 6850 5050
Wire Wire Line
	6700 5150 6850 5150
Wire Wire Line
	6850 5150 6850 5050
Connection ~ 6850 5050
Wire Wire Line
	6850 5050 6700 5050
Text Label 4700 3550 0    50   ~ 0
AD3
Text Label 4700 3350 0    50   ~ 0
AD1
Text Label 4700 3650 0    50   ~ 0
AD4
Text Label 4700 3750 0    50   ~ 0
AD5
Text Label 4700 3250 0    50   ~ 0
AD0
Wire Wire Line
	4500 4550 5150 4550
Wire Wire Line
	4500 4650 5150 4650
Wire Wire Line
	5150 4750 4500 4750
Entry Wire Line
	5150 4550 5250 4650
Entry Wire Line
	5150 4650 5250 4750
Entry Wire Line
	5150 4750 5250 4850
Entry Wire Line
	5250 4750 5350 4650
Entry Wire Line
	5250 4650 5350 4550
Entry Wire Line
	5250 4850 5350 4750
Text Label 4800 4550 0    50   ~ 0
5
Text Label 4800 4650 0    50   ~ 0
6
Text Label 4800 4750 0    50   ~ 0
7
Wire Wire Line
	5350 4550 5900 4550
Wire Wire Line
	5350 4650 5900 4650
Wire Wire Line
	5350 4750 5900 4750
Text Label 5700 4750 0    50   ~ 0
5
Text Label 5700 4650 0    50   ~ 0
6
Text Label 5700 4550 0    50   ~ 0
7
Wire Wire Line
	5900 4850 5350 4850
Wire Wire Line
	5900 4950 5350 4950
Wire Wire Line
	5900 5050 5750 5050
Wire Wire Line
	5900 5150 5750 5150
Wire Wire Line
	5750 5150 5750 5050
Connection ~ 5750 5050
Wire Wire Line
	5750 5050 5350 5050
Entry Wire Line
	5250 4950 5350 4850
Entry Wire Line
	5250 5050 5350 4950
Entry Wire Line
	5250 5150 5350 5050
Entry Wire Line
	5150 4450 5250 4550
Entry Wire Line
	5150 4350 5250 4450
Entry Wire Line
	5150 4250 5250 4350
Wire Wire Line
	4500 4250 5150 4250
Wire Wire Line
	5150 4350 4500 4350
Wire Wire Line
	4500 4450 5150 4450
Text Label 4800 4250 0    50   ~ 0
2
Text Label 4850 4350 0    50   ~ 0
3
Text Label 4800 4450 0    50   ~ 0
4
Text Label 5700 5050 0    50   ~ 0
2
Text Label 5700 4950 0    50   ~ 0
3
Text Label 5700 4850 0    50   ~ 0
4
$Comp
L antswitch-rescue:VDD-power #PWR0101
U 1 1 5DAE89D2
P 3900 1850
F 0 "#PWR0101" H 3900 1700 50  0001 C CNN
F 1 "VDD" H 3917 2023 50  0000 C CNN
F 2 "" H 3900 1850 50  0001 C CNN
F 3 "" H 3900 1850 50  0001 C CNN
	1    3900 1850
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:VDD-power #PWR0102
U 1 1 5DAE91CC
P 6500 950
F 0 "#PWR0102" H 6500 800 50  0001 C CNN
F 1 "VDD" H 6517 1123 50  0000 C CNN
F 2 "" H 6500 950 50  0001 C CNN
F 3 "" H 6500 950 50  0001 C CNN
	1    6500 950 
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0104
U 1 1 5DAE9B0C
P 3900 5200
F 0 "#PWR0104" H 3900 4950 50  0001 C CNN
F 1 "GND" H 3905 5027 50  0000 C CNN
F 2 "" H 3900 5200 50  0001 C CNN
F 3 "" H 3900 5200 50  0001 C CNN
	1    3900 5200
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0105
U 1 1 5DAEB6C0
P 6300 5450
F 0 "#PWR0105" H 6300 5200 50  0001 C CNN
F 1 "GND" H 6305 5277 50  0000 C CNN
F 2 "" H 6300 5450 50  0001 C CNN
F 3 "" H 6300 5450 50  0001 C CNN
	1    6300 5450
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0106
U 1 1 5DAEBA97
P 6300 4100
F 0 "#PWR0106" H 6300 3850 50  0001 C CNN
F 1 "GND" H 6305 3927 50  0000 C CNN
F 2 "" H 6300 4100 50  0001 C CNN
F 3 "" H 6300 4100 50  0001 C CNN
	1    6300 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 5450 6300 5350
Wire Wire Line
	6300 4100 6300 4050
Wire Wire Line
	3900 5050 3900 5200
$Comp
L antswitch-rescue:GND-power #PWR0107
U 1 1 5DAF5A6D
P 6300 2350
F 0 "#PWR0107" H 6300 2100 50  0001 C CNN
F 1 "GND" H 6305 2177 50  0000 C CNN
F 2 "" H 6300 2350 50  0001 C CNN
F 3 "" H 6300 2350 50  0001 C CNN
	1    6300 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2250 6300 2350
Wire Wire Line
	6500 950  6300 1050
Wire Wire Line
	4000 2050 3900 2050
Wire Wire Line
	3900 2050 3900 1900
Connection ~ 3900 2050
$Comp
L antswitch-rescue:C-Device C1
U 1 1 5DB013B5
P 4050 1900
F 0 "C1" V 3798 1900 50  0000 C CNN
F 1 "C" V 3889 1900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4088 1750 50  0001 C CNN
F 3 "~" H 4050 1900 50  0001 C CNN
	1    4050 1900
	0    1    1    0   
$EndComp
Connection ~ 3900 1900
Wire Wire Line
	3900 1900 3900 1850
$Comp
L antswitch-rescue:GND-power #PWR0103
U 1 1 5DB01812
P 4200 1900
F 0 "#PWR0103" H 4200 1650 50  0001 C CNN
F 1 "GND" H 4205 1727 50  0000 C CNN
F 2 "" H 4200 1900 50  0001 C CNN
F 3 "" H 4200 1900 50  0001 C CNN
	1    4200 1900
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:C-Device C2
U 1 1 5DB030B7
P 3750 1900
F 0 "C2" V 4002 1900 50  0000 C CNN
F 1 "C" V 3911 1900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3788 1750 50  0001 C CNN
F 3 "~" H 3750 1900 50  0001 C CNN
	1    3750 1900
	0    -1   -1   0   
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0108
U 1 1 5DB0353D
P 3600 1900
F 0 "#PWR0108" H 3600 1650 50  0001 C CNN
F 1 "GND" H 3605 1727 50  0000 C CNN
F 2 "" H 3600 1900 50  0001 C CNN
F 3 "" H 3600 1900 50  0001 C CNN
	1    3600 1900
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:LM317_3PinPackage-Regulator_Linear U5
U 1 1 5DB05C1E
P 2050 1800
F 0 "U5" H 2050 2133 50  0000 C CNN
F 1 "LM317_3PinPackage" H 2050 2042 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 2050 1951 50  0000 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 2050 1800 50  0001 C CNN
	1    2050 1800
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:VDD-power #PWR0109
U 1 1 5DB064AE
P 2500 1650
F 0 "#PWR0109" H 2500 1500 50  0001 C CNN
F 1 "VDD" H 2517 1823 50  0000 C CNN
F 2 "" H 2500 1650 50  0001 C CNN
F 3 "" H 2500 1650 50  0001 C CNN
	1    2500 1650
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:C-Device C3
U 1 1 5DB06E94
P 1500 2050
F 0 "C3" H 1615 2096 50  0000 L CNN
F 1 "C" H 1615 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1538 1900 50  0001 C CNN
F 3 "~" H 1500 2050 50  0001 C CNN
	1    1500 2050
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:C-Device C4
U 1 1 5DB07505
P 2500 2050
F 0 "C4" H 2615 2096 50  0000 L CNN
F 1 "C" H 2615 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2538 1900 50  0001 C CNN
F 3 "~" H 2500 2050 50  0001 C CNN
	1    2500 2050
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0110
U 1 1 5DB0B93A
P 1500 2200
F 0 "#PWR0110" H 1500 1950 50  0001 C CNN
F 1 "GND" H 1505 2027 50  0000 C CNN
F 2 "" H 1500 2200 50  0001 C CNN
F 3 "" H 1500 2200 50  0001 C CNN
	1    1500 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1800 2500 1800
Wire Wire Line
	2500 1800 2500 1900
Wire Wire Line
	1750 1800 1500 1800
Wire Wire Line
	1500 1800 1500 1900
$Comp
L antswitch-rescue:GND-power #PWR0111
U 1 1 5DB10410
P 2500 2200
F 0 "#PWR0111" H 2500 1950 50  0001 C CNN
F 1 "GND" H 2505 2027 50  0000 C CNN
F 2 "" H 2500 2200 50  0001 C CNN
F 3 "" H 2500 2200 50  0001 C CNN
	1    2500 2200
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:C-Device C5
U 1 1 5DB11D57
P 2750 2050
F 0 "C5" H 2865 2096 50  0000 L CNN
F 1 "C" H 2865 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2788 1900 50  0001 C CNN
F 3 "~" H 2750 2050 50  0001 C CNN
	1    2750 2050
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0112
U 1 1 5DB11FAF
P 2750 2200
F 0 "#PWR0112" H 2750 1950 50  0001 C CNN
F 1 "GND" H 2755 2027 50  0000 C CNN
F 2 "" H 2750 2200 50  0001 C CNN
F 3 "" H 2750 2200 50  0001 C CNN
	1    2750 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1800 2750 1800
Wire Wire Line
	2750 1800 2750 1900
Connection ~ 2500 1800
$Comp
L antswitch-rescue:R-Device R1
U 1 1 5DB16EB8
P 2350 2000
F 0 "R1" H 2420 2046 50  0000 L CNN
F 1 "R" H 2420 1955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2280 2000 50  0001 C CNN
F 3 "~" H 2350 2000 50  0001 C CNN
	1    2350 2000
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0113
U 1 1 5DB1AB90
P 2350 2500
F 0 "#PWR0113" H 2350 2250 50  0001 C CNN
F 1 "GND" H 2355 2327 50  0000 C CNN
F 2 "" H 2350 2500 50  0001 C CNN
F 3 "" H 2350 2500 50  0001 C CNN
	1    2350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 2100 2050 2150
Wire Wire Line
	2050 2150 2350 2150
Wire Wire Line
	2350 2200 2350 2150
Connection ~ 2350 2150
Wire Wire Line
	2350 1850 2350 1800
Connection ~ 2350 1800
$Comp
L antswitch-rescue:R-Device R2
U 1 1 5DB21B31
P 2350 2350
F 0 "R2" H 2420 2396 50  0000 L CNN
F 1 "R" H 2420 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2280 2350 50  0001 C CNN
F 3 "~" H 2350 2350 50  0001 C CNN
	1    2350 2350
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:CP-Device C6
U 1 1 5DB2361D
P 1200 1950
F 0 "C6" H 1318 1996 50  0000 L CNN
F 1 "CP" H 1318 1905 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 1238 1800 50  0001 C CNN
F 3 "~" H 1200 1950 50  0001 C CNN
	1    1200 1950
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:GND-power #PWR0114
U 1 1 5DB23A20
P 1200 2200
F 0 "#PWR0114" H 1200 1950 50  0001 C CNN
F 1 "GND" H 1205 2027 50  0000 C CNN
F 2 "" H 1200 2200 50  0001 C CNN
F 3 "" H 1200 2200 50  0001 C CNN
	1    1200 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1800 1200 1800
Connection ~ 1500 1800
Wire Wire Line
	1200 2100 1200 2200
$Comp
L antswitch-rescue:VDD-power #PWR0115
U 1 1 5DB2ABF0
P 2750 1800
F 0 "#PWR0115" H 2750 1650 50  0001 C CNN
F 1 "VDD" H 2767 1973 50  0000 C CNN
F 2 "" H 2750 1800 50  0001 C CNN
F 3 "" H 2750 1800 50  0001 C CNN
	1    2750 1800
	1    0    0    -1  
$EndComp
Connection ~ 2750 1800
$Comp
L antswitch-rescue:Conn_01x03_Female-Connector J3
U 1 1 5DB2B23E
P 700 1850
F 0 "J3" H 592 1525 50  0000 C CNN
F 1 "Conn_01x03_Female" H 592 1616 50  0000 C CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MCV_1,5_3-G-5.08_1x03_P5.08mm_Vertical" H 700 1850 50  0001 C CNN
F 3 "~" H 700 1850 50  0001 C CNN
	1    700  1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	900  1750 1050 1750
Wire Wire Line
	1200 1750 1200 1800
Connection ~ 1200 1800
Wire Wire Line
	1200 2100 1050 2100
Wire Wire Line
	900  2100 900  1950
Connection ~ 1200 2100
Wire Wire Line
	900  1850 900  1950
Connection ~ 900  1950
$Comp
L antswitch-rescue:+12V-power #PWR0116
U 1 1 5DB33FE3
P 1500 1800
F 0 "#PWR0116" H 1500 1650 50  0001 C CNN
F 1 "+12V" H 1515 1973 50  0000 C CNN
F 2 "" H 1500 1800 50  0001 C CNN
F 3 "" H 1500 1800 50  0001 C CNN
	1    1500 1800
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:+12V-power #PWR0117
U 1 1 5DB3455B
P 6700 4350
F 0 "#PWR0117" H 6700 4200 50  0001 C CNN
F 1 "+12V" H 6715 4523 50  0000 C CNN
F 2 "" H 6700 4350 50  0001 C CNN
F 3 "" H 6700 4350 50  0001 C CNN
	1    6700 4350
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:+12V-power #PWR0118
U 1 1 5DB35E8E
P 6700 3050
F 0 "#PWR0118" H 6700 2900 50  0001 C CNN
F 1 "+12V" H 6715 3223 50  0000 C CNN
F 2 "" H 6700 3050 50  0001 C CNN
F 3 "" H 6700 3050 50  0001 C CNN
	1    6700 3050
	1    0    0    -1  
$EndComp
$Comp
L antswitch-rescue:R-Device R3
U 1 1 5DB37E37
P 4750 3850
F 0 "R3" V 4543 3850 50  0000 C CNN
F 1 "R" V 4634 3850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4680 3850 50  0001 C CNN
F 3 "~" H 4750 3850 50  0001 C CNN
	1    4750 3850
	0    1    1    0   
$EndComp
$Comp
L antswitch-rescue:VDD-power #PWR0119
U 1 1 5DB383E8
P 4900 3850
F 0 "#PWR0119" H 4900 3700 50  0001 C CNN
F 1 "VDD" V 4917 3978 50  0000 L CNN
F 2 "" H 4900 3850 50  0001 C CNN
F 3 "" H 4900 3850 50  0001 C CNN
	1    4900 3850
	0    1    1    0   
$EndComp
Text GLabel 4550 3850 3    50   Input ~ 0
RESET
$Comp
L Connector:Conn_01x05_Male J4
U 1 1 5DA93AEE
P 5650 4150
F 0 "J4" H 5622 4082 50  0000 R CNN
F 1 "Conn_01x05_Male" H 5622 4173 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 5650 4150 50  0001 C CNN
F 3 "~" H 5650 4150 50  0001 C CNN
	1    5650 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3850 4900 3950
Wire Wire Line
	4900 3950 5450 3950
Connection ~ 4900 3850
Wire Wire Line
	4500 3850 4600 3850
Wire Wire Line
	4600 3850 4600 4000
Wire Wire Line
	4600 4000 5450 4000
Wire Wire Line
	5450 4000 5450 4050
Connection ~ 4600 3850
Wire Wire Line
	4500 4050 5350 4050
Wire Wire Line
	5350 4050 5350 4150
Wire Wire Line
	5350 4150 5450 4150
Wire Wire Line
	4500 4150 5300 4150
Wire Wire Line
	5300 4150 5300 4250
Wire Wire Line
	5300 4250 5450 4250
$Comp
L power:GND #PWR0120
U 1 1 5DAA576C
P 5450 4350
F 0 "#PWR0120" H 5450 4100 50  0001 C CNN
F 1 "GND" H 5455 4177 50  0000 C CNN
F 2 "" H 5450 4350 50  0001 C CNN
F 3 "" H 5450 4350 50  0001 C CNN
	1    5450 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:Varistor RV1
U 1 1 5DABB5D8
P 1050 1950
F 0 "RV1" H 1153 1996 50  0000 L CNN
F 1 "Varistor" H 1153 1905 50  0000 L CNN
F 2 "Varistor:RV_Disc_D15.5mm_W4mm_P7.5mm" V 980 1950 50  0001 C CNN
F 3 "~" H 1050 1950 50  0001 C CNN
	1    1050 1950
	1    0    0    -1  
$EndComp
Connection ~ 1050 2100
Wire Wire Line
	1050 2100 900  2100
Wire Wire Line
	1050 1800 1050 1750
Wire Bus Line
	5250 3050 5250 5300
Connection ~ 1050 1750
Wire Wire Line
	1050 1750 1200 1750
$EndSCHEMATC
