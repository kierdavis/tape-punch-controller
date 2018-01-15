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
Sheet 1 7
Title "Tape punch controller"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 4350 1900 1250 1650
U 5A3BC77B
F0 "Microcontroller" 60
F1 "microcontroller.sch" 60
$EndSheet
$Sheet
S 4350 4400 1250 800 
U 5A3BEBFE
F0 "PowerSupplies" 60
F1 "power.sch" 60
$EndSheet
$Sheet
S 6100 2650 1250 500 
U 5A3C02B4
F0 "FeedbackSignalProcessing" 60
F1 "feedback-signal.sch" 60
$EndSheet
$Comp
L Screw_Terminal_01x01 MH1
U 1 1 5A3E86DB
P 9800 4850
F 0 "MH1" H 9800 4950 50  0000 C CNN
F 1 "Screw_Terminal_01x01" H 9800 4750 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4_Pad" H 9800 4850 50  0001 C CNN
F 3 "" H 9800 4850 50  0001 C CNN
	1    9800 4850
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x01 MH2
U 1 1 5A3E8774
P 9800 5150
F 0 "MH2" H 9800 5250 50  0000 C CNN
F 1 "Screw_Terminal_01x01" H 9800 5050 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4_Pad" H 9800 5150 50  0001 C CNN
F 3 "" H 9800 5150 50  0001 C CNN
	1    9800 5150
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x01 MH3
U 1 1 5A3E8794
P 9800 5450
F 0 "MH3" H 9800 5550 50  0000 C CNN
F 1 "Screw_Terminal_01x01" H 9800 5350 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_4.3mm_M4_Pad" H 9800 5450 50  0001 C CNN
F 3 "" H 9800 5450 50  0001 C CNN
	1    9800 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5A3E882F
P 9200 5550
F 0 "#PWR01" H 9200 5300 50  0001 C CNN
F 1 "GND" H 9200 5400 50  0000 C CNN
F 2 "" H 9200 5550 50  0001 C CNN
F 3 "" H 9200 5550 50  0001 C CNN
	1    9200 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 4850 9200 4850
Wire Wire Line
	9200 4850 9200 5550
Wire Wire Line
	9600 5150 9200 5150
Connection ~ 9200 5150
Wire Wire Line
	9600 5450 9200 5450
Connection ~ 9200 5450
Text Notes 9200 4650 0    60   ~ 0
Mounting holes\n(plated and grounded).
$Sheet
S 6100 1900 1250 500 
U 5A3B4329
F0 "SolenoidDrivers" 60
F1 "solenoid-drivers.sch" 60
$EndSheet
$Sheet
S 7850 1900 1250 1650
U 5A3B0CA1
F0 "TapePunchConnector" 60
F1 "tape-punch-connector.sch" 60
$EndSheet
Wire Notes Line
	7850 2150 7350 2150
Wire Notes Line
	6100 2150 5600 2150
Wire Notes Line
	7850 2900 7350 2900
Wire Notes Line
	6100 2900 5600 2900
Wire Notes Line
	7850 3400 5600 3400
$Sheet
S 2650 2850 1250 700 
U 5A3D185F
F0 "Controls" 60
F1 "controls.sch" 60
$EndSheet
Wire Notes Line
	3900 3200 4350 3200
Wire Notes Line
	9100 2700 9600 2700
Wire Notes Line
	4350 2050 3900 2050
Wire Notes Line
	2650 3000 2150 3000
Wire Notes Line
	2650 3400 2150 3400
Text Notes 2150 3000 2    60   ~ 0
LCD module
Text Notes 2150 3500 2    60   ~ 0
Chassis LEDs\n& buttons
Text Notes 3900 2150 2    60   ~ 0
Host computer\n(via USB)
Text Notes 9600 2700 0    60   ~ 0
Tape punch
$EndSCHEMATC
