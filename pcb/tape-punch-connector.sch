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
LIBS:tape-punch-controller-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
Title "Tape punch connector"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DB25_Male_MountingHoles J1
U 1 1 5A3B26B2
P 6600 3600
F 0 "J1" H 6600 5050 50  0000 C CNN
F 1 "DB25_Male_MountingHoles" H 6600 4975 50  0000 C CNN
F 2 "local:NORCOMP_182-025-113R171" H 6600 3600 50  0001 C CNN
F 3 "" H 6600 3600 50  0001 C CNN
	1    6600 3600
	1    0    0    -1  
$EndComp
$Comp
L +28V #PWR064
U 1 1 5A3B26B9
P 5900 2300
F 0 "#PWR064" H 5900 2150 50  0001 C CNN
F 1 "+28V" H 5900 2450 50  0000 C CNN
F 2 "" H 6150 2350 50  0001 C CNN
F 3 "" H 6150 2350 50  0001 C CNN
	1    5900 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2800 6100 2800
Wire Wire Line
	6100 2800 6100 5200
Wire Wire Line
	6100 5100 6600 5100
Wire Wire Line
	6600 5100 6600 5000
Wire Wire Line
	6300 2900 5900 2900
Wire Wire Line
	5900 2300 5900 3900
Wire Wire Line
	5900 3000 6300 3000
Wire Wire Line
	5900 3700 6300 3700
Connection ~ 5900 3000
Wire Wire Line
	5900 3900 6300 3900
Connection ~ 5900 3700
Connection ~ 5900 2900
Connection ~ 6100 5100
Wire Wire Line
	6300 3200 5400 3200
Wire Wire Line
	6300 3400 5400 3400
Wire Wire Line
	6300 3600 5400 3600
Wire Wire Line
	6300 3800 5400 3800
Wire Wire Line
	6300 4000 5400 4000
Wire Wire Line
	6300 4200 5400 4200
Wire Wire Line
	6300 4400 5400 4400
Wire Wire Line
	6300 4600 5400 4600
Wire Wire Line
	6300 4800 5400 4800
Wire Wire Line
	6300 2600 5500 2600
Wire Wire Line
	6300 2700 5500 2700
Wire Wire Line
	6300 2500 5400 2500
$Comp
L R R3
U 1 1 5A3B26DD
P 3900 2850
F 0 "R3" V 3980 2850 50  0000 C CNN
F 1 "10k" V 3900 2850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3830 2850 50  0001 C CNN
F 3 "" H 3900 2850 50  0001 C CNN
	1    3900 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2400 5700 2400
Wire Wire Line
	5700 3300 6300 3300
Wire Wire Line
	3600 3100 6300 3100
Wire Wire Line
	3900 3000 3900 3150
NoConn ~ 6300 3500
$Comp
L +3.3V #PWR065
U 1 1 5A3B26F7
P 3900 2650
F 0 "#PWR065" H 3900 2500 50  0001 C CNN
F 1 "+3.3V" H 3900 2790 50  0000 C CNN
F 2 "" H 3900 2650 50  0001 C CNN
F 3 "" H 3900 2650 50  0001 C CNN
	1    3900 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2650 3900 2700
$Comp
L R R4
U 1 1 5A3B26FE
P 3900 4500
F 0 "R4" V 3980 4500 50  0000 C CNN
F 1 "10k" V 3900 4500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3830 4500 50  0001 C CNN
F 3 "" H 3900 4500 50  0001 C CNN
	1    3900 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4700 6300 4700
Wire Wire Line
	3900 4650 3900 4750
NoConn ~ 6300 4500
$Comp
L +3.3V #PWR066
U 1 1 5A3B2708
P 3900 4250
F 0 "#PWR066" H 3900 4100 50  0001 C CNN
F 1 "+3.3V" H 3900 4390 50  0000 C CNN
F 2 "" H 3900 4250 50  0001 C CNN
F 3 "" H 3900 4250 50  0001 C CNN
	1    3900 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4250 3900 4350
$Comp
L R R1
U 1 1 5A3B270F
P 3450 3100
F 0 "R1" V 3530 3100 50  0000 C CNN
F 1 "68k" V 3450 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3380 3100 50  0001 C CNN
F 3 "" H 3450 3100 50  0001 C CNN
	1    3450 3100
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5A3B2719
P 3450 4700
F 0 "R2" V 3530 4700 50  0000 C CNN
F 1 "68k" V 3450 4700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3380 4700 50  0001 C CNN
F 3 "" H 3450 4700 50  0001 C CNN
	1    3450 4700
	0    1    1    0   
$EndComp
Connection ~ 3900 4700
$Comp
L C C1
U 1 1 5A3B2723
P 3200 3350
F 0 "C1" H 3225 3450 50  0000 L CNN
F 1 "100n" H 3225 3250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3238 3200 50  0001 C CNN
F 3 "" H 3200 3350 50  0001 C CNN
	1    3200 3350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5A3B272A
P 3200 4950
F 0 "C2" H 3225 5050 50  0000 L CNN
F 1 "100n" H 3225 4850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3238 4800 50  0001 C CNN
F 3 "" H 3200 4950 50  0001 C CNN
	1    3200 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3100 3300 3100
Wire Wire Line
	3200 3100 3200 3200
Wire Wire Line
	2900 4700 3300 4700
Wire Wire Line
	3200 4700 3200 4800
$Comp
L GND #PWR067
U 1 1 5A3B2735
P 3200 3550
F 0 "#PWR067" H 3200 3300 50  0001 C CNN
F 1 "GND" H 3200 3400 50  0000 C CNN
F 2 "" H 3200 3550 50  0001 C CNN
F 3 "" H 3200 3550 50  0001 C CNN
	1    3200 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR068
U 1 1 5A3B273B
P 3200 5150
F 0 "#PWR068" H 3200 4900 50  0001 C CNN
F 1 "GND" H 3200 5000 50  0000 C CNN
F 2 "" H 3200 5150 50  0001 C CNN
F 3 "" H 3200 5150 50  0001 C CNN
	1    3200 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 5100 3200 5150
Wire Wire Line
	3200 3500 3200 3550
Connection ~ 3200 3100
Connection ~ 3200 4700
Text Notes 7600 2250 0    118  ~ 0
Pinout description:
Text Notes 7600 5100 0    60   ~ 0
Pins 1-9 are the negative sides of the\nsolenoids. The positive sides are\nconnected to the 28V supply rail via\npins 10, 18, 19 and 23.\n\nPin 25 is the negative side of the coil\nof the power relay. The positive side is\nlikewise connected to the 28V rail.\n\nPins 12 and 24 are connected to the\nfeedback coil.\n\nPins 13, 14 and 15 are connected to\nthe tape detection switch, located just\nnext to the punch apparatus. This\nswitch connects 14 to 13 when tape\nis present, and 15 to 13 when it is not.\n\nSimilarly, pin 20 is connected to pin 21\nwhen the reel is low on tape, and pin 22\nto pin 21 when it is not.\n\nPin 11 is connected to mains earth inside\nthe tape punch, as is the cable sheath\n(labelled here as pin 0).\n\nPins 16 and 17 have no connection inside\nthe tape punch.
Text GLabel 5400 4800 0    60   Input ~ 0
CODE1_SOL
Text GLabel 5400 4600 0    60   Input ~ 0
CODE2_SOL
Text GLabel 5400 4400 0    60   Input ~ 0
CODE3_SOL
Text GLabel 5400 4200 0    60   Input ~ 0
CODE4_SOL
Text GLabel 5400 4000 0    60   Input ~ 0
CODE5_SOL
Text GLabel 5400 3800 0    60   Input ~ 0
CODE6_SOL
Text GLabel 5400 3600 0    60   Input ~ 0
CODE7_SOL
Text GLabel 5400 3400 0    60   Input ~ 0
CODE0_SOL
Text GLabel 5400 3200 0    60   Input ~ 0
FEED_SOL
Text GLabel 5400 2500 0    60   Input ~ 0
ENABLE_RELAY
Text GLabel 5400 2650 0    60   BiDi ~ 0
SYNC_COIL+
Text GLabel 5400 2800 0    60   BiDi ~ 0
SYNC_COIL-
Wire Wire Line
	5400 2800 5500 2800
Wire Wire Line
	5500 2800 5500 2700
Wire Wire Line
	5400 2650 5500 2650
Wire Wire Line
	5500 2650 5500 2600
Text GLabel 2900 3100 0    60   Output ~ 0
LOW_TAPE
Text GLabel 2900 4700 0    60   Output ~ 0
NO_TAPE
Text GLabel 6100 5200 3    60   UnSpc ~ 0
TP_EARTH
Text Notes 1800 2450 0    60   ~ 0
LOW_TAPE_RAW/NO_TAPE_RAW are\nnormally held high, and are driven\nlow when the corresponding switches\ndetect that reel is not low on tape or\nthat there is tape present. Each switch\nis debounced using an RC filter.
NoConn ~ 6300 4300
NoConn ~ 6300 4100
Text Label 4750 3100 2    60   ~ 0
LOW_TAPE_RAW
Text Label 4750 4700 2    60   ~ 0
NO_TAPE_RAW
Connection ~ 3900 3100
Wire Wire Line
	5700 2400 5700 5200
Connection ~ 5700 3300
$Comp
L GND #PWR069
U 1 1 5A3C33D9
P 5700 5200
F 0 "#PWR069" H 5700 4950 50  0001 C CNN
F 1 "GND" H 5700 5050 50  0000 C CNN
F 2 "" H 5700 5200 50  0001 C CNN
F 3 "" H 5700 5200 50  0001 C CNN
	1    5700 5200
	1    0    0    -1  
$EndComp
$Comp
L TEST TP3
U 1 1 5A42C90A
P 3900 3150
F 0 "TP3" H 3900 3450 50  0000 C BNN
F 1 "TEST" H 3900 3400 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3900 3150 50  0001 C CNN
F 3 "" H 3900 3150 50  0001 C CNN
	1    3900 3150
	-1   0    0    1   
$EndComp
$Comp
L TEST TP1
U 1 1 5A42D2A2
P 3000 3050
F 0 "TP1" H 3000 3350 50  0000 C BNN
F 1 "TEST" H 3000 3300 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3000 3050 50  0001 C CNN
F 3 "" H 3000 3050 50  0001 C CNN
	1    3000 3050
	1    0    0    -1  
$EndComp
$Comp
L TEST TP4
U 1 1 5A42D3C3
P 3900 4750
F 0 "TP4" H 3900 5050 50  0000 C BNN
F 1 "TEST" H 3900 5000 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3900 4750 50  0001 C CNN
F 3 "" H 3900 4750 50  0001 C CNN
	1    3900 4750
	-1   0    0    1   
$EndComp
$Comp
L TEST TP2
U 1 1 5A42D3F4
P 3000 4650
F 0 "TP2" H 3000 4950 50  0000 C BNN
F 1 "TEST" H 3000 4900 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3000 4650 50  0001 C CNN
F 3 "" H 3000 4650 50  0001 C CNN
	1    3000 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3050 3000 3100
Connection ~ 3000 3100
Wire Wire Line
	3000 4650 3000 4700
Connection ~ 3000 4700
$EndSCHEMATC
