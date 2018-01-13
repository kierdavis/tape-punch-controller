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
Sheet 6 7
Title "Tape punch connectors"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R34
U 1 1 5A3B26DD
P 2200 4850
F 0 "R34" V 2280 4850 50  0000 C CNN
F 1 "10k" V 2200 4850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2130 4850 50  0001 C CNN
F 3 "" H 2200 4850 50  0001 C CNN
	1    2200 4850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR066
U 1 1 5A3B26F7
P 2200 4650
F 0 "#PWR066" H 2200 4500 50  0001 C CNN
F 1 "+3.3V" H 2200 4790 50  0000 C CNN
F 2 "" H 2200 4650 50  0001 C CNN
F 3 "" H 2200 4650 50  0001 C CNN
	1    2200 4650
	1    0    0    -1  
$EndComp
$Comp
L R R35
U 1 1 5A3B26FE
P 2200 6300
F 0 "R35" V 2280 6300 50  0000 C CNN
F 1 "10k" V 2200 6300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2130 6300 50  0001 C CNN
F 3 "" H 2200 6300 50  0001 C CNN
	1    2200 6300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR067
U 1 1 5A3B2708
P 2200 6100
F 0 "#PWR067" H 2200 5950 50  0001 C CNN
F 1 "+3.3V" H 2200 6240 50  0000 C CNN
F 2 "" H 2200 6100 50  0001 C CNN
F 3 "" H 2200 6100 50  0001 C CNN
	1    2200 6100
	1    0    0    -1  
$EndComp
$Comp
L R R36
U 1 1 5A3B270F
P 2450 5100
F 0 "R36" V 2530 5100 50  0000 C CNN
F 1 "68k" V 2450 5100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2380 5100 50  0001 C CNN
F 3 "" H 2450 5100 50  0001 C CNN
	1    2450 5100
	0    1    1    0   
$EndComp
$Comp
L R R37
U 1 1 5A3B2719
P 2450 6550
F 0 "R37" V 2530 6550 50  0000 C CNN
F 1 "68k" V 2450 6550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2380 6550 50  0001 C CNN
F 3 "" H 2450 6550 50  0001 C CNN
	1    2450 6550
	0    1    1    0   
$EndComp
$Comp
L C C12
U 1 1 5A3B2723
P 2700 5350
F 0 "C12" H 2725 5450 50  0000 L CNN
F 1 "100n" H 2725 5250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2738 5200 50  0001 C CNN
F 3 "" H 2700 5350 50  0001 C CNN
	1    2700 5350
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 5A3B272A
P 2700 6800
F 0 "C13" H 2725 6900 50  0000 L CNN
F 1 "100n" H 2725 6700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2738 6650 50  0001 C CNN
F 3 "" H 2700 6800 50  0001 C CNN
	1    2700 6800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR068
U 1 1 5A3B2735
P 2700 5550
F 0 "#PWR068" H 2700 5300 50  0001 C CNN
F 1 "GND" H 2700 5400 50  0000 C CNN
F 2 "" H 2700 5550 50  0001 C CNN
F 3 "" H 2700 5550 50  0001 C CNN
	1    2700 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR069
U 1 1 5A3B273B
P 2700 7000
F 0 "#PWR069" H 2700 6750 50  0001 C CNN
F 1 "GND" H 2700 6850 50  0000 C CNN
F 2 "" H 2700 7000 50  0001 C CNN
F 3 "" H 2700 7000 50  0001 C CNN
	1    2700 7000
	1    0    0    -1  
$EndComp
Text GLabel 5400 1950 0    60   Input ~ 0
CODE1_SOL
Text GLabel 5400 2100 0    60   Input ~ 0
CODE2_SOL
Text GLabel 5400 2250 0    60   Input ~ 0
CODE3_SOL
Text GLabel 5400 2400 0    60   Input ~ 0
CODE4_SOL
Text GLabel 5400 2550 0    60   Input ~ 0
CODE5_SOL
Text GLabel 5400 2700 0    60   Input ~ 0
CODE6_SOL
Text GLabel 5400 2850 0    60   Input ~ 0
CODE7_SOL
Text GLabel 5400 3000 0    60   Input ~ 0
CODE0_SOL
Text GLabel 5400 3150 0    60   Input ~ 0
FEED_SOL
Text GLabel 2350 2750 0    60   Input ~ 0
ENABLE_RELAY
Text GLabel 2350 2950 0    60   BiDi ~ 0
SYNC_COIL+
Text GLabel 2350 3150 0    60   BiDi ~ 0
SYNC_COIL-
Text GLabel 3200 5100 2    60   Output ~ 0
LOW_TAPE
Text GLabel 3200 6550 2    60   Output ~ 0
NO_TAPE
Text Notes 4200 6150 0    60   ~ 0
LOW_TAPE_RAW/NO_TAPE_RAW are normally connected\nto ground by their respective switches. If a low tape or\nno tape condition occurs, the switch disconnects, allowing\nthe corresponding _RAW signal to be pulled high by the\n10k resistor.\n\nEach switch is debounced with an RC filter.
$Comp
L GND #PWR070
U 1 1 5A3C33D9
P 2700 3450
F 0 "#PWR070" H 2700 3200 50  0001 C CNN
F 1 "GND" H 2700 3300 50  0000 C CNN
F 2 "" H 2700 3450 50  0001 C CNN
F 3 "" H 2700 3450 50  0001 C CNN
	1    2700 3450
	1    0    0    -1  
$EndComp
$Comp
L TEST TP45
U 1 1 5A42C90A
P 1900 5000
F 0 "TP45" H 1900 5300 50  0000 C BNN
F 1 "TEST" H 1900 5250 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1900 5000 50  0001 C CNN
F 3 "" H 1900 5000 50  0001 C CNN
	1    1900 5000
	1    0    0    -1  
$EndComp
$Comp
L TEST TP47
U 1 1 5A42D2A2
P 3000 5050
F 0 "TP47" H 3000 5350 50  0000 C BNN
F 1 "TEST" H 3000 5300 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3000 5050 50  0001 C CNN
F 3 "" H 3000 5050 50  0001 C CNN
	1    3000 5050
	1    0    0    -1  
$EndComp
$Comp
L TEST TP46
U 1 1 5A42D3C3
P 1900 6450
F 0 "TP46" H 1900 6750 50  0000 C BNN
F 1 "TEST" H 1900 6700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1900 6450 50  0001 C CNN
F 3 "" H 1900 6450 50  0001 C CNN
	1    1900 6450
	1    0    0    -1  
$EndComp
$Comp
L TEST TP48
U 1 1 5A42D3F4
P 3000 6450
F 0 "TP48" H 3000 6750 50  0000 C BNN
F 1 "TEST" H 3000 6700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3000 6450 50  0001 C CNN
F 3 "" H 3000 6450 50  0001 C CNN
	1    3000 6450
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x09 J2
U 1 1 5A590012
P 5900 2550
F 0 "J2" H 5900 3050 50  0000 C CNN
F 1 "Conn_01x09" H 5900 2050 50  0000 C CNN
F 2 "Local:Weidmuller_1234610000" H 5900 2550 50  0001 C CNN
F 3 "" H 5900 2550 50  0001 C CNN
	1    5900 2550
	1    0    0    -1  
$EndComp
Text Label 2350 3550 2    60   ~ 0
NO_TAPE_RAW
Text Label 2350 3350 2    60   ~ 0
LOW_TAPE_RAW
Text Label 1050 5100 0    60   ~ 0
LOW_TAPE_RAW
Text Label 1050 6550 0    60   ~ 0
NO_TAPE_RAW
Text Notes 4550 1750 0    60   ~ 0
Each pin on J2 is wired to the pin of the\nsame number on the DB25 (tape punch)\nconnector mounted on the chassis.\nThese are the negative ends of the nine\nsolenoids. The positive ends are connected\nto the 28V rail inside the tape punch, which\nitself is directly connected to the PSU.
Text Notes 7500 5000 0    60   ~ 0
Tape punch cable pinout:\n\nTP pin 1  -- J2 pin 1 (code sol 1)\nTP pin 2  -- J2 pin 2 (code sol 2)\nTP pin 3  -- J2 pin 3 (code sol 3)\nTP pin 4  -- J2 pin 4 (code sol 4)\nTP pin 5  -- J2 pin 5 (code sol 5)\nTP pin 6  -- J2 pin 6 (code sol 6)\nTP pin 7  -- J2 pin 7 (code sol 7)\nTP pin 8  -- J2 pin 8 (code sol 0)\nTP pin 9  -- J2 pin 9 (feed sol)\nTP pin 10 -- PSU 28VDC output\nTP pin 11 -- earth (tape punch chassis)\nTP pin 12 -- J1 pin 3 (sync coil)\nTP pin 13 -- J1 pin 1 ("no tape" switch, common)\nTP pin 14 -- J1 pin 6 ("no tape" switch, closed when tape present)\nTP pin 15 -- N.C. ("no tape" switch, closed when no tape)\nTP pin 16 -- earth (N.C. in tape punch)\nTP pin 17 -- earth (N.C. in tape punch)\nTP pin 18 -- PSU 28VDC output\nTP pin 19 -- PSU 28VDC output\nTP pin 20 -- N.C. ("low tape" switch, closed when tape is low)\nTP pin 21 -- J1 pin 1 ("low tape" switch, common)\nTP pin 22 -- J1 pin 5 ("low tape" switch, closed when tape not low)\nTP pin 23 -- PSU 28VDC output\nTP pin 24 -- J1 pin 4 (sync coil)\nTP pin 25 -- J1 pin 2 (enable relay)\nTP cable sheath -- earth\n\nTP = tape punch\nPSU = power supply unit\nN.C. = no connection
Text Notes 1250 2450 0    60   ~ 0
Miscellaneous low-current signals for the tape punch.\n\nENABLE_RELAY is the negative end of the relay that\nconnects power to the motor and solenoids. The\npositive end of this relay is tied to the 28V supply\ninside the tape punch.\n\nThe feedback coil is connected between SYNC_COIL+\nand SYNC_COIL-.\n\nLOW_TAPE_RAW and NO_TAPE_RAW connect to the\ntwo switches inside the tape punch; see the comment\nnext to their filtering circuitry below for details on\nthe functionality of these pins.
$Comp
L Conn_01x06 J1
U 1 1 5A59E154
P 3050 3050
F 0 "J1" H 3050 3350 50  0000 C CNN
F 1 "Conn_01x06" H 3050 2650 50  0000 C CNN
F 2 "Local:Amphenol_T821106A1S100CEU" H 3050 3050 50  0001 C CNN
F 3 "" H 3050 3050 50  0001 C CNN
	1    3050 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2550 5700 2550
Wire Wire Line
	5400 2400 5450 2400
Wire Wire Line
	5450 2400 5450 2450
Wire Wire Line
	5450 2450 5700 2450
Wire Wire Line
	5400 2250 5500 2250
Wire Wire Line
	5500 2250 5500 2350
Wire Wire Line
	5500 2350 5700 2350
Wire Wire Line
	5400 2100 5550 2100
Wire Wire Line
	5550 2100 5550 2250
Wire Wire Line
	5550 2250 5700 2250
Wire Wire Line
	5400 1950 5600 1950
Wire Wire Line
	5600 1950 5600 2150
Wire Wire Line
	5600 2150 5700 2150
Wire Wire Line
	5400 2700 5450 2700
Wire Wire Line
	5450 2700 5450 2650
Wire Wire Line
	5450 2650 5700 2650
Wire Wire Line
	5400 2850 5500 2850
Wire Wire Line
	5500 2850 5500 2750
Wire Wire Line
	5500 2750 5700 2750
Wire Wire Line
	5400 3000 5550 3000
Wire Wire Line
	5550 3000 5550 2850
Wire Wire Line
	5550 2850 5700 2850
Wire Wire Line
	5400 3150 5600 3150
Wire Wire Line
	5600 3150 5600 2950
Wire Wire Line
	5600 2950 5700 2950
Wire Wire Line
	2200 4650 2200 4700
Wire Wire Line
	2200 5100 2200 5000
Wire Wire Line
	1000 5100 2300 5100
Wire Wire Line
	1900 5000 1900 5100
Connection ~ 1900 5100
Wire Wire Line
	2700 5500 2700 5550
Connection ~ 2200 5100
Wire Wire Line
	2600 5100 3200 5100
Wire Wire Line
	2700 5100 2700 5200
Wire Wire Line
	3000 5100 3000 5050
Connection ~ 2700 5100
Connection ~ 3000 5100
Wire Wire Line
	1000 6550 2300 6550
Wire Wire Line
	1900 6450 1900 6550
Connection ~ 1900 6550
Wire Wire Line
	2200 6450 2200 6550
Connection ~ 2200 6550
Wire Wire Line
	2600 6550 3200 6550
Wire Wire Line
	2700 6550 2700 6650
Wire Wire Line
	2700 6950 2700 7000
Wire Wire Line
	3000 6550 3000 6450
Connection ~ 2700 6550
Connection ~ 3000 6550
Wire Wire Line
	2200 6100 2200 6150
Wire Wire Line
	2700 3450 2700 2850
Wire Wire Line
	2700 2850 2850 2850
Wire Wire Line
	2850 3150 2350 3150
Wire Wire Line
	2850 3050 2450 3050
Wire Wire Line
	2450 3050 2450 2950
Wire Wire Line
	2450 2950 2350 2950
Wire Wire Line
	2850 2950 2500 2950
Wire Wire Line
	2500 2950 2500 2750
Wire Wire Line
	2500 2750 2350 2750
Wire Wire Line
	2850 3250 2450 3250
Wire Wire Line
	2450 3250 2450 3350
Wire Wire Line
	2450 3350 1650 3350
Wire Wire Line
	2850 3350 2500 3350
Wire Wire Line
	2500 3350 2500 3550
Wire Wire Line
	2500 3550 1650 3550
$EndSCHEMATC
