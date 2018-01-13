EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:symbols
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
Title "Feedback signal conditioning circuit"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LM321 U2
U 1 1 5A3C02BD
P 5900 3550
F 0 "U2" H 5900 3850 50  0000 L CNN
F 1 "LM321" H 5900 3750 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 5900 3550 50  0001 C CNN
F 3 "" H 5900 3550 50  0001 C CNN
	1    5900 3550
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 5A3C035E
P 5050 4600
F 0 "RV1" V 4875 4600 50  0000 C CNN
F 1 "10k" V 4950 4600 50  0000 C CNN
F 2 "Local:Citec_CB10LV103M" H 5050 4600 50  0001 C CNN
F 3 "" H 5050 4600 50  0001 C CNN
	1    5050 4600
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 5A3C040F
P 5050 5000
F 0 "R10" V 5130 5000 50  0000 C CNN
F 1 "10k" V 5050 5000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4980 5000 50  0001 C CNN
F 3 "" H 5050 5000 50  0001 C CNN
	1    5050 5000
	-1   0    0    1   
$EndComp
$Comp
L R R8
U 1 1 5A3C04B2
P 4200 3250
F 0 "R8" V 4280 3250 50  0000 C CNN
F 1 "1k" V 4200 3250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4130 3250 50  0001 C CNN
F 3 "" H 4200 3250 50  0001 C CNN
	1    4200 3250
	-1   0    0    1   
$EndComp
$Comp
L R R9
U 1 1 5A3C0507
P 4200 3650
F 0 "R9" V 4280 3650 50  0000 C CNN
F 1 "1k" V 4200 3650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4130 3650 50  0001 C CNN
F 3 "" H 4200 3650 50  0001 C CNN
	1    4200 3650
	-1   0    0    1   
$EndComp
$Comp
L R R31
U 1 1 5A3C0552
P 6850 3800
F 0 "R31" V 6930 3800 50  0000 C CNN
F 1 "68k" V 6850 3800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6780 3800 50  0001 C CNN
F 3 "" H 6850 3800 50  0001 C CNN
	1    6850 3800
	-1   0    0    1   
$EndComp
$Comp
L R R32
U 1 1 5A3C05C5
P 6850 4200
F 0 "R32" V 6930 4200 50  0000 C CNN
F 1 "18k" V 6850 4200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6780 4200 50  0001 C CNN
F 3 "" H 6850 4200 50  0001 C CNN
	1    6850 4200
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5A3C0612
P 9200 5450
F 0 "C7" H 9225 5550 50  0000 L CNN
F 1 "100n" H 9225 5350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9238 5300 50  0001 C CNN
F 3 "" H 9200 5450 50  0001 C CNN
	1    9200 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3450 4850 3450
Connection ~ 4200 3450
$Comp
L +15V #PWR037
U 1 1 5A3C0DAA
P 4200 3050
F 0 "#PWR037" H 4200 2900 50  0001 C CNN
F 1 "+15V" H 4200 3190 50  0000 C CNN
F 2 "" H 4200 3050 50  0001 C CNN
F 3 "" H 4200 3050 50  0001 C CNN
	1    4200 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 5A3C0E60
P 4200 3850
F 0 "#PWR038" H 4200 3600 50  0001 C CNN
F 1 "GND" H 4200 3700 50  0000 C CNN
F 2 "" H 4200 3850 50  0001 C CNN
F 3 "" H 4200 3850 50  0001 C CNN
	1    4200 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3050 4200 3100
Wire Wire Line
	4200 3400 4200 3500
Wire Wire Line
	4200 3800 4200 3850
Text GLabel 4850 3250 1    60   BiDi ~ 0
SYNC_COIL-
Text GLabel 5000 3250 1    60   BiDi ~ 0
SYNC_COIL+
Wire Wire Line
	4850 3450 4850 3250
Wire Wire Line
	5000 3250 5000 3450
Wire Wire Line
	5000 3450 5600 3450
$Comp
L +15V #PWR039
U 1 1 5A3C1520
P 5800 3200
F 0 "#PWR039" H 5800 3050 50  0001 C CNN
F 1 "+15V" H 5800 3340 50  0000 C CNN
F 2 "" H 5800 3200 50  0001 C CNN
F 3 "" H 5800 3200 50  0001 C CNN
	1    5800 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR040
U 1 1 5A3C1544
P 5800 3900
F 0 "#PWR040" H 5800 3650 50  0001 C CNN
F 1 "GND" H 5800 3750 50  0000 C CNN
F 2 "" H 5800 3900 50  0001 C CNN
F 3 "" H 5800 3900 50  0001 C CNN
	1    5800 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3200 5800 3250
Wire Wire Line
	5800 3850 5800 3900
Wire Wire Line
	5050 4750 5050 4850
$Comp
L GND #PWR041
U 1 1 5A3C19BB
P 5050 5200
F 0 "#PWR041" H 5050 4950 50  0001 C CNN
F 1 "GND" H 5050 5050 50  0000 C CNN
F 2 "" H 5050 5200 50  0001 C CNN
F 3 "" H 5050 5200 50  0001 C CNN
	1    5050 5200
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR042
U 1 1 5A3C19E7
P 5050 4400
F 0 "#PWR042" H 5050 4250 50  0001 C CNN
F 1 "+15V" H 5050 4540 50  0000 C CNN
F 2 "" H 5050 4400 50  0001 C CNN
F 3 "" H 5050 4400 50  0001 C CNN
	1    5050 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4400 5050 4450
Wire Wire Line
	5050 5150 5050 5200
Wire Wire Line
	5200 4600 5400 4600
Wire Wire Line
	5400 3650 5400 4650
Wire Wire Line
	5400 3650 5600 3650
Text Label 5400 4500 1    60   ~ 0
SYNC_THRESHOLD
Text Notes 9500 5550 0    60   ~ 0
Op-amp decoupling\ncapacitor. Place next\nto supply pin.
$Comp
L +15V #PWR043
U 1 1 5A3C4041
P 9200 5250
F 0 "#PWR043" H 9200 5100 50  0001 C CNN
F 1 "+15V" H 9200 5390 50  0000 C CNN
F 2 "" H 9200 5250 50  0001 C CNN
F 3 "" H 9200 5250 50  0001 C CNN
	1    9200 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR044
U 1 1 5A3C4065
P 9200 5650
F 0 "#PWR044" H 9200 5400 50  0001 C CNN
F 1 "GND" H 9200 5500 50  0000 C CNN
F 2 "" H 9200 5650 50  0001 C CNN
F 3 "" H 9200 5650 50  0001 C CNN
	1    9200 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 5250 9200 5300
Wire Wire Line
	9200 5600 9200 5650
Text Notes 4350 2550 0    60   ~ 0
The tape punch feedback\ncoil is connected between\nSYNC_COIL- and SYNC_COIL+.
Text Notes 2250 3700 0    60   ~ 0
This voltage divider holds SYNC_COIL-\nat 7.5V. Since the feedback coil\nis wired in series with the op-amp's\nhigh impedance input, negligible\ncurrent is drawn, and so this voltage\nshould be very stable.
Text Notes 3550 4750 0    60   ~ 0
The threshold voltage\ncan be adjusted between\n7.5V and 15V.
Text Notes 6200 2800 0    60   ~ 0
The op-amp, acting as a comparator, will produce just\nless than 15V on the output when SYNC_COIL+ is greater\nthan the threshold voltage, and just above 0V when it\nis less than the threshold voltage.
Wire Wire Line
	6850 3950 6850 4050
Wire Wire Line
	6200 3550 6850 3550
Wire Wire Line
	6850 3500 6850 3650
$Comp
L GND #PWR045
U 1 1 5A3C52DE
P 6850 4400
F 0 "#PWR045" H 6850 4150 50  0001 C CNN
F 1 "GND" H 6850 4250 50  0000 C CNN
F 2 "" H 6850 4400 50  0001 C CNN
F 3 "" H 6850 4400 50  0001 C CNN
	1    6850 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4350 6850 4400
Wire Wire Line
	6850 4000 7250 4000
Connection ~ 6850 4000
Text Label 6300 3550 0    60   ~ 0
SYNC_RAW
Text GLabel 7250 4000 2    60   Output ~ 0
SYNC
Text Notes 7100 4550 0    60   ~ 0
This voltage divider reduces\nthe 15V output voltage to\nabout 3.1V, suitable for the\nmicrocontroller's input pin.
$Comp
L TEST TP9
U 1 1 5A439B1B
P 4650 3400
F 0 "TP9" H 4650 3700 50  0000 C BNN
F 1 "TEST" H 4650 3650 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4650 3400 50  0001 C CNN
F 3 "" H 4650 3400 50  0001 C CNN
	1    4650 3400
	1    0    0    -1  
$EndComp
$Comp
L TEST TP10
U 1 1 5A439C40
P 5200 3400
F 0 "TP10" H 5200 3700 50  0000 C BNN
F 1 "TEST" H 5200 3650 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5200 3400 50  0001 C CNN
F 3 "" H 5200 3400 50  0001 C CNN
	1    5200 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3400 4650 3450
Connection ~ 4650 3450
Wire Wire Line
	5200 3400 5200 3450
Connection ~ 5200 3450
$Comp
L TEST TP11
U 1 1 5A43A093
P 5400 4650
F 0 "TP11" H 5400 4950 50  0000 C BNN
F 1 "TEST" H 5400 4900 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5400 4650 50  0001 C CNN
F 3 "" H 5400 4650 50  0001 C CNN
	1    5400 4650
	-1   0    0    1   
$EndComp
Connection ~ 5400 4600
$Comp
L TEST TP12
U 1 1 5A43A451
P 6850 3500
F 0 "TP12" H 6850 3800 50  0000 C BNN
F 1 "TEST" H 6850 3750 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6850 3500 50  0001 C CNN
F 3 "" H 6850 3500 50  0001 C CNN
	1    6850 3500
	1    0    0    -1  
$EndComp
$Comp
L TEST TP13
U 1 1 5A43A494
P 7150 3950
F 0 "TP13" H 7150 4250 50  0000 C BNN
F 1 "TEST" H 7150 4200 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7150 3950 50  0001 C CNN
F 3 "" H 7150 3950 50  0001 C CNN
	1    7150 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3950 7150 4000
Connection ~ 7150 4000
Connection ~ 6850 3550
$EndSCHEMATC
