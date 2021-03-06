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
Sheet 5 7
Title "Solenoid and relay driving circuitry"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3600 1100 2    60   Output ~ 0
CODE0_SOL
Wire Wire Line
	3450 1100 3600 1100
Wire Wire Line
	3500 1100 3500 1200
$Comp
L GND #PWR040
U 1 1 5A3B44A2
P 3500 1650
F 0 "#PWR040" H 3500 1400 50  0001 C CNN
F 1 "GND" H 3500 1500 50  0000 C CNN
F 2 "" H 3500 1650 50  0001 C CNN
F 3 "" H 3500 1650 50  0001 C CNN
	1    3500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1600 3500 1650
$Comp
L R R28
U 1 1 5A3B45A9
P 2400 1400
F 0 "R28" V 2480 1400 50  0000 C CNN
F 1 "180" V 2400 1400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2330 1400 50  0001 C CNN
F 3 "" H 2400 1400 50  0001 C CNN
	1    2400 1400
	0    1    1    0   
$EndComp
$Comp
L R R18
U 1 1 5A3B463A
P 2150 1650
F 0 "R18" V 2230 1650 50  0000 C CNN
F 1 "1M" V 2150 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2080 1650 50  0001 C CNN
F 3 "" H 2150 1650 50  0001 C CNN
	1    2150 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1400 3200 1400
Text Label 2600 1400 0    60   ~ 0
CODE0_GATE
Wire Wire Line
	1850 1400 2250 1400
Wire Wire Line
	2150 1400 2150 1500
$Comp
L GND #PWR041
U 1 1 5A3B4730
P 2150 1850
F 0 "#PWR041" H 2150 1600 50  0001 C CNN
F 1 "GND" H 2150 1700 50  0000 C CNN
F 2 "" H 2150 1850 50  0001 C CNN
F 3 "" H 2150 1850 50  0001 C CNN
	1    2150 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 1800 2150 1850
Text GLabel 1850 1400 0    60   Input ~ 0
CODE0_SIG
Connection ~ 2150 1400
Text GLabel 3600 2000 2    60   Output ~ 0
CODE1_SOL
Wire Wire Line
	3450 2000 3600 2000
Wire Wire Line
	3500 2000 3500 2100
$Comp
L GND #PWR042
U 1 1 5A3B508E
P 3500 2550
F 0 "#PWR042" H 3500 2300 50  0001 C CNN
F 1 "GND" H 3500 2400 50  0000 C CNN
F 2 "" H 3500 2550 50  0001 C CNN
F 3 "" H 3500 2550 50  0001 C CNN
	1    3500 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2500 3500 2550
$Comp
L R R21
U 1 1 5A3B5095
P 2400 2300
F 0 "R21" V 2480 2300 50  0000 C CNN
F 1 "180" V 2400 2300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2330 2300 50  0001 C CNN
F 3 "" H 2400 2300 50  0001 C CNN
	1    2400 2300
	0    1    1    0   
$EndComp
$Comp
L R R11
U 1 1 5A3B509B
P 2150 2550
F 0 "R11" V 2230 2550 50  0000 C CNN
F 1 "1M" V 2150 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2080 2550 50  0001 C CNN
F 3 "" H 2150 2550 50  0001 C CNN
	1    2150 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2300 3200 2300
Text Label 2600 2300 0    60   ~ 0
CODE1_GATE
Wire Wire Line
	1850 2300 2250 2300
Wire Wire Line
	2150 2300 2150 2400
$Comp
L GND #PWR043
U 1 1 5A3B50A5
P 2150 2750
F 0 "#PWR043" H 2150 2500 50  0001 C CNN
F 1 "GND" H 2150 2600 50  0000 C CNN
F 2 "" H 2150 2750 50  0001 C CNN
F 3 "" H 2150 2750 50  0001 C CNN
	1    2150 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2700 2150 2750
Text GLabel 1850 2300 0    60   Input ~ 0
CODE1_SIG
Connection ~ 2150 2300
Text GLabel 3600 2900 2    60   Output ~ 0
CODE2_SOL
Wire Wire Line
	3450 2900 3600 2900
Wire Wire Line
	3500 2900 3500 3000
$Comp
L GND #PWR044
U 1 1 5A3B6977
P 3500 3450
F 0 "#PWR044" H 3500 3200 50  0001 C CNN
F 1 "GND" H 3500 3300 50  0000 C CNN
F 2 "" H 3500 3450 50  0001 C CNN
F 3 "" H 3500 3450 50  0001 C CNN
	1    3500 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3400 3500 3450
$Comp
L R R22
U 1 1 5A3B697E
P 2400 3200
F 0 "R22" V 2480 3200 50  0000 C CNN
F 1 "180" V 2400 3200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2330 3200 50  0001 C CNN
F 3 "" H 2400 3200 50  0001 C CNN
	1    2400 3200
	0    1    1    0   
$EndComp
$Comp
L R R12
U 1 1 5A3B6984
P 2150 3450
F 0 "R12" V 2230 3450 50  0000 C CNN
F 1 "1M" V 2150 3450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2080 3450 50  0001 C CNN
F 3 "" H 2150 3450 50  0001 C CNN
	1    2150 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3200 3200 3200
Text Label 2600 3200 0    60   ~ 0
CODE2_GATE
Wire Wire Line
	1850 3200 2250 3200
Wire Wire Line
	2150 3200 2150 3300
$Comp
L GND #PWR045
U 1 1 5A3B698E
P 2150 3650
F 0 "#PWR045" H 2150 3400 50  0001 C CNN
F 1 "GND" H 2150 3500 50  0000 C CNN
F 2 "" H 2150 3650 50  0001 C CNN
F 3 "" H 2150 3650 50  0001 C CNN
	1    2150 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 3600 2150 3650
Text GLabel 1850 3200 0    60   Input ~ 0
CODE2_SIG
Connection ~ 2150 3200
Text GLabel 3600 3800 2    60   Output ~ 0
CODE3_SOL
Wire Wire Line
	3450 3800 3600 3800
Wire Wire Line
	3500 3800 3500 3900
$Comp
L GND #PWR046
U 1 1 5A3B69A0
P 3500 4350
F 0 "#PWR046" H 3500 4100 50  0001 C CNN
F 1 "GND" H 3500 4200 50  0000 C CNN
F 2 "" H 3500 4350 50  0001 C CNN
F 3 "" H 3500 4350 50  0001 C CNN
	1    3500 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4300 3500 4350
$Comp
L R R23
U 1 1 5A3B69A7
P 2400 4100
F 0 "R23" V 2480 4100 50  0000 C CNN
F 1 "180" V 2400 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2330 4100 50  0001 C CNN
F 3 "" H 2400 4100 50  0001 C CNN
	1    2400 4100
	0    1    1    0   
$EndComp
$Comp
L R R13
U 1 1 5A3B69AD
P 2150 4350
F 0 "R13" V 2230 4350 50  0000 C CNN
F 1 "1M" V 2150 4350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2080 4350 50  0001 C CNN
F 3 "" H 2150 4350 50  0001 C CNN
	1    2150 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4100 3200 4100
Text Label 2600 4100 0    60   ~ 0
CODE3_GATE
Wire Wire Line
	1850 4100 2250 4100
Wire Wire Line
	2150 4100 2150 4200
$Comp
L GND #PWR047
U 1 1 5A3B69B7
P 2150 4550
F 0 "#PWR047" H 2150 4300 50  0001 C CNN
F 1 "GND" H 2150 4400 50  0000 C CNN
F 2 "" H 2150 4550 50  0001 C CNN
F 3 "" H 2150 4550 50  0001 C CNN
	1    2150 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4500 2150 4550
Text GLabel 1850 4100 0    60   Input ~ 0
CODE3_SIG
Connection ~ 2150 4100
Text GLabel 7200 1100 2    60   Output ~ 0
CODE4_SOL
Wire Wire Line
	7050 1100 7200 1100
Wire Wire Line
	7100 1100 7100 1200
$Comp
L GND #PWR048
U 1 1 5A3BA91A
P 7100 1650
F 0 "#PWR048" H 7100 1400 50  0001 C CNN
F 1 "GND" H 7100 1500 50  0000 C CNN
F 2 "" H 7100 1650 50  0001 C CNN
F 3 "" H 7100 1650 50  0001 C CNN
	1    7100 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1600 7100 1650
$Comp
L R R24
U 1 1 5A3BA921
P 6000 1400
F 0 "R24" V 6080 1400 50  0000 C CNN
F 1 "180" V 6000 1400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5930 1400 50  0001 C CNN
F 3 "" H 6000 1400 50  0001 C CNN
	1    6000 1400
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 5A3BA927
P 5750 1650
F 0 "R14" V 5830 1650 50  0000 C CNN
F 1 "1M" V 5750 1650 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 1650 50  0001 C CNN
F 3 "" H 5750 1650 50  0001 C CNN
	1    5750 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1400 6800 1400
Text Label 6200 1400 0    60   ~ 0
CODE4_GATE
Wire Wire Line
	5450 1400 5850 1400
Wire Wire Line
	5750 1400 5750 1500
$Comp
L GND #PWR049
U 1 1 5A3BA931
P 5750 1850
F 0 "#PWR049" H 5750 1600 50  0001 C CNN
F 1 "GND" H 5750 1700 50  0000 C CNN
F 2 "" H 5750 1850 50  0001 C CNN
F 3 "" H 5750 1850 50  0001 C CNN
	1    5750 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1800 5750 1850
Text GLabel 5450 1400 0    60   Input ~ 0
CODE4_SIG
Connection ~ 5750 1400
Text GLabel 7200 2000 2    60   Output ~ 0
CODE5_SOL
Wire Wire Line
	7050 2000 7200 2000
Wire Wire Line
	7100 2000 7100 2100
$Comp
L GND #PWR050
U 1 1 5A3BA943
P 7100 2550
F 0 "#PWR050" H 7100 2300 50  0001 C CNN
F 1 "GND" H 7100 2400 50  0000 C CNN
F 2 "" H 7100 2550 50  0001 C CNN
F 3 "" H 7100 2550 50  0001 C CNN
	1    7100 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2500 7100 2550
$Comp
L R R25
U 1 1 5A3BA94A
P 6000 2300
F 0 "R25" V 6080 2300 50  0000 C CNN
F 1 "180" V 6000 2300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5930 2300 50  0001 C CNN
F 3 "" H 6000 2300 50  0001 C CNN
	1    6000 2300
	0    1    1    0   
$EndComp
$Comp
L R R15
U 1 1 5A3BA950
P 5750 2550
F 0 "R15" V 5830 2550 50  0000 C CNN
F 1 "1M" V 5750 2550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 2550 50  0001 C CNN
F 3 "" H 5750 2550 50  0001 C CNN
	1    5750 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2300 6800 2300
Text Label 6200 2300 0    60   ~ 0
CODE5_GATE
Wire Wire Line
	5450 2300 5850 2300
Wire Wire Line
	5750 2300 5750 2400
$Comp
L GND #PWR051
U 1 1 5A3BA95A
P 5750 2750
F 0 "#PWR051" H 5750 2500 50  0001 C CNN
F 1 "GND" H 5750 2600 50  0000 C CNN
F 2 "" H 5750 2750 50  0001 C CNN
F 3 "" H 5750 2750 50  0001 C CNN
	1    5750 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2700 5750 2750
Text GLabel 5450 2300 0    60   Input ~ 0
CODE5_SIG
Connection ~ 5750 2300
Text GLabel 7200 2900 2    60   Output ~ 0
CODE6_SOL
Wire Wire Line
	7050 2900 7200 2900
Wire Wire Line
	7100 2900 7100 3000
$Comp
L GND #PWR052
U 1 1 5A3BA96C
P 7100 3450
F 0 "#PWR052" H 7100 3200 50  0001 C CNN
F 1 "GND" H 7100 3300 50  0000 C CNN
F 2 "" H 7100 3450 50  0001 C CNN
F 3 "" H 7100 3450 50  0001 C CNN
	1    7100 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3400 7100 3450
$Comp
L R R26
U 1 1 5A3BA973
P 6000 3200
F 0 "R26" V 6080 3200 50  0000 C CNN
F 1 "180" V 6000 3200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5930 3200 50  0001 C CNN
F 3 "" H 6000 3200 50  0001 C CNN
	1    6000 3200
	0    1    1    0   
$EndComp
$Comp
L R R16
U 1 1 5A3BA979
P 5750 3450
F 0 "R16" V 5830 3450 50  0000 C CNN
F 1 "1M" V 5750 3450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 3450 50  0001 C CNN
F 3 "" H 5750 3450 50  0001 C CNN
	1    5750 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3200 6800 3200
Text Label 6200 3200 0    60   ~ 0
CODE6_GATE
Wire Wire Line
	5450 3200 5850 3200
Wire Wire Line
	5750 3200 5750 3300
$Comp
L GND #PWR053
U 1 1 5A3BA983
P 5750 3650
F 0 "#PWR053" H 5750 3400 50  0001 C CNN
F 1 "GND" H 5750 3500 50  0000 C CNN
F 2 "" H 5750 3650 50  0001 C CNN
F 3 "" H 5750 3650 50  0001 C CNN
	1    5750 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3600 5750 3650
Text GLabel 5450 3200 0    60   Input ~ 0
CODE6_SIG
Connection ~ 5750 3200
Text GLabel 7200 3800 2    60   Output ~ 0
CODE7_SOL
Wire Wire Line
	7050 3800 7200 3800
Wire Wire Line
	7100 3800 7100 3900
$Comp
L GND #PWR054
U 1 1 5A3BA995
P 7100 4350
F 0 "#PWR054" H 7100 4100 50  0001 C CNN
F 1 "GND" H 7100 4200 50  0000 C CNN
F 2 "" H 7100 4350 50  0001 C CNN
F 3 "" H 7100 4350 50  0001 C CNN
	1    7100 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4300 7100 4350
$Comp
L R R27
U 1 1 5A3BA99C
P 6000 4100
F 0 "R27" V 6080 4100 50  0000 C CNN
F 1 "180" V 6000 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5930 4100 50  0001 C CNN
F 3 "" H 6000 4100 50  0001 C CNN
	1    6000 4100
	0    1    1    0   
$EndComp
$Comp
L R R17
U 1 1 5A3BA9A2
P 5750 4350
F 0 "R17" V 5830 4350 50  0000 C CNN
F 1 "1M" V 5750 4350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 4350 50  0001 C CNN
F 3 "" H 5750 4350 50  0001 C CNN
	1    5750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4100 6800 4100
Text Label 6200 4100 0    60   ~ 0
CODE7_GATE
Wire Wire Line
	5450 4100 5850 4100
Wire Wire Line
	5750 4100 5750 4200
$Comp
L GND #PWR055
U 1 1 5A3BA9AC
P 5750 4550
F 0 "#PWR055" H 5750 4300 50  0001 C CNN
F 1 "GND" H 5750 4400 50  0000 C CNN
F 2 "" H 5750 4550 50  0001 C CNN
F 3 "" H 5750 4550 50  0001 C CNN
	1    5750 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4500 5750 4550
Text GLabel 5450 4100 0    60   Input ~ 0
CODE7_SIG
Connection ~ 5750 4100
Text GLabel 3600 5200 2    60   Output ~ 0
FEED_SOL
Wire Wire Line
	3450 5200 3600 5200
Wire Wire Line
	3500 5200 3500 5300
$Comp
L GND #PWR056
U 1 1 5A3BC4B5
P 3500 5750
F 0 "#PWR056" H 3500 5500 50  0001 C CNN
F 1 "GND" H 3500 5600 50  0000 C CNN
F 2 "" H 3500 5750 50  0001 C CNN
F 3 "" H 3500 5750 50  0001 C CNN
	1    3500 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 5700 3500 5750
$Comp
L R R29
U 1 1 5A3BC4BC
P 2400 5500
F 0 "R29" V 2480 5500 50  0000 C CNN
F 1 "180" V 2400 5500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2330 5500 50  0001 C CNN
F 3 "" H 2400 5500 50  0001 C CNN
	1    2400 5500
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 5A3BC4C2
P 2150 5750
F 0 "R19" V 2230 5750 50  0000 C CNN
F 1 "1M" V 2150 5750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2080 5750 50  0001 C CNN
F 3 "" H 2150 5750 50  0001 C CNN
	1    2150 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 5500 3200 5500
Text Label 2600 5500 0    60   ~ 0
FEED_GATE
Wire Wire Line
	1850 5500 2250 5500
Wire Wire Line
	2150 5500 2150 5600
$Comp
L GND #PWR057
U 1 1 5A3BC4CC
P 2150 5950
F 0 "#PWR057" H 2150 5700 50  0001 C CNN
F 1 "GND" H 2150 5800 50  0000 C CNN
F 2 "" H 2150 5950 50  0001 C CNN
F 3 "" H 2150 5950 50  0001 C CNN
	1    2150 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 5900 2150 5950
Text GLabel 1850 5500 0    60   Input ~ 0
FEED_SIG
Connection ~ 2150 5500
Text Notes 8350 2300 0    60   ~ 0
The resistors in series with the MOSFET gates\nexist to limit inrush current. At the instant *_SIG\ngoes high, the MOSFET gate is still appoximately\n0V as its slew rate is limited by gate capacitance.\nHence the voltage across the resistor peaks at 3.3V.\nThe MOSFET's rated maximum gate current is\n20mA; aiming for 18mA gives a resistance of\n3.3V/18mA = 183Ω.\n\nThe 1MΩ shunt resistors are pull-downs, ensuring\nthat the MOSFET gates are held low when the\nmicrocontroller's outputs are tri-stated\n(e.g. during reset).
Text GLabel 7200 4700 2    60   Output ~ 0
ENABLE_RELAY
$Comp
L GND #PWR058
U 1 1 5A3BF7BB
P 7100 5750
F 0 "#PWR058" H 7100 5500 50  0001 C CNN
F 1 "GND" H 7100 5600 50  0000 C CNN
F 2 "" H 7100 5750 50  0001 C CNN
F 3 "" H 7100 5750 50  0001 C CNN
	1    7100 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 5700 7100 5750
$Comp
L R R30
U 1 1 5A3BF7C2
P 6000 5500
F 0 "R30" V 6080 5500 50  0000 C CNN
F 1 "180" V 6000 5500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5930 5500 50  0001 C CNN
F 3 "" H 6000 5500 50  0001 C CNN
	1    6000 5500
	0    -1   -1   0   
$EndComp
$Comp
L R R20
U 1 1 5A3BF7C8
P 5750 5750
F 0 "R20" V 5830 5750 50  0000 C CNN
F 1 "1M" V 5750 5750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 5680 5750 50  0001 C CNN
F 3 "" H 5750 5750 50  0001 C CNN
	1    5750 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5500 6800 5500
Text Label 6200 5500 0    60   ~ 0
ENABLE_GATE
Wire Wire Line
	5450 5500 5850 5500
Wire Wire Line
	5750 5500 5750 5600
$Comp
L GND #PWR059
U 1 1 5A3BF7D2
P 5750 5950
F 0 "#PWR059" H 5750 5700 50  0001 C CNN
F 1 "GND" H 5750 5800 50  0000 C CNN
F 2 "" H 5750 5950 50  0001 C CNN
F 3 "" H 5750 5950 50  0001 C CNN
	1    5750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 5900 5750 5950
Text GLabel 5450 5500 0    60   Input ~ 0
ENABLE_SIG
Connection ~ 5750 5500
$Comp
L R R33
U 1 1 5A3C201A
P 7100 4950
F 0 "R33" V 7180 4950 50  0000 C CNN
F 1 "120" V 7100 4950 50  0000 C CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" V 7030 4950 50  0001 C CNN
F 3 "" H 7100 4950 50  0001 C CNN
	1    7100 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	7050 4700 7200 4700
Wire Wire Line
	7100 4700 7100 4800
Wire Wire Line
	7100 5100 7100 5300
Text Label 7100 5200 0    60   ~ 0
ENABLE_DRAIN
Text Notes 8350 5900 0    60   ~ 0
The relay coil requires between 16V and 24V for\nactivation. We aim for 22V.\n\nOne end of the relay is tied to 28V inside the\ntape punch, so we need to bring the other end\n(ENABLE_RELAY) to about 6V. Under these\nconditions the relay coil is observed to pass\nabout 50 mA. Therefore a 6V/50mA = 120Ω\nresistor is needed here.\n\nThis 120Ω resistor dissipates 300mW when\nthe relay is active, so a 500mW-rated resistor\nin a 1210 package is used.
$Comp
L TEST TP19
U 1 1 5A42E017
P 2650 1450
F 0 "TP19" H 2650 1750 50  0000 C BNN
F 1 "TEST" H 2650 1700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 2650 1450 50  0001 C CNN
F 3 "" H 2650 1450 50  0001 C CNN
	1    2650 1450
	-1   0    0    1   
$EndComp
$Comp
L TEST TP20
U 1 1 5A42E246
P 2650 2350
F 0 "TP20" H 2650 2650 50  0000 C BNN
F 1 "TEST" H 2650 2600 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 2650 2350 50  0001 C CNN
F 3 "" H 2650 2350 50  0001 C CNN
	1    2650 2350
	-1   0    0    1   
$EndComp
$Comp
L TEST TP21
U 1 1 5A42E494
P 2650 3250
F 0 "TP21" H 2650 3550 50  0000 C BNN
F 1 "TEST" H 2650 3500 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 2650 3250 50  0001 C CNN
F 3 "" H 2650 3250 50  0001 C CNN
	1    2650 3250
	-1   0    0    1   
$EndComp
$Comp
L TEST TP22
U 1 1 5A42E741
P 2650 4150
F 0 "TP22" H 2650 4450 50  0000 C BNN
F 1 "TEST" H 2650 4400 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 2650 4150 50  0001 C CNN
F 3 "" H 2650 4150 50  0001 C CNN
	1    2650 4150
	-1   0    0    1   
$EndComp
$Comp
L TEST TP23
U 1 1 5A42EA4B
P 2650 5550
F 0 "TP23" H 2650 5850 50  0000 C BNN
F 1 "TEST" H 2650 5800 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 2650 5550 50  0001 C CNN
F 3 "" H 2650 5550 50  0001 C CNN
	1    2650 5550
	-1   0    0    1   
$EndComp
$Comp
L TEST TP24
U 1 1 5A42FFAE
P 3450 1100
F 0 "TP24" H 3450 1400 50  0000 C BNN
F 1 "TEST" H 3450 1350 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3450 1100 50  0001 C CNN
F 3 "" H 3450 1100 50  0001 C CNN
	1    3450 1100
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP25
U 1 1 5A430195
P 3450 2000
F 0 "TP25" H 3450 2300 50  0000 C BNN
F 1 "TEST" H 3450 2250 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3450 2000 50  0001 C CNN
F 3 "" H 3450 2000 50  0001 C CNN
	1    3450 2000
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP26
U 1 1 5A4303C4
P 3450 2900
F 0 "TP26" H 3450 3200 50  0000 C BNN
F 1 "TEST" H 3450 3150 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3450 2900 50  0001 C CNN
F 3 "" H 3450 2900 50  0001 C CNN
	1    3450 2900
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP27
U 1 1 5A4304B2
P 3450 3800
F 0 "TP27" H 3450 4100 50  0000 C BNN
F 1 "TEST" H 3450 4050 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3450 3800 50  0001 C CNN
F 3 "" H 3450 3800 50  0001 C CNN
	1    3450 3800
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP28
U 1 1 5A43077B
P 3450 5200
F 0 "TP28" H 3450 5500 50  0000 C BNN
F 1 "TEST" H 3450 5450 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 3450 5200 50  0001 C CNN
F 3 "" H 3450 5200 50  0001 C CNN
	1    3450 5200
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP34
U 1 1 5A431213
P 6250 1450
F 0 "TP34" H 6250 1750 50  0000 C BNN
F 1 "TEST" H 6250 1700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6250 1450 50  0001 C CNN
F 3 "" H 6250 1450 50  0001 C CNN
	1    6250 1450
	-1   0    0    1   
$EndComp
$Comp
L TEST TP35
U 1 1 5A43153A
P 6250 2350
F 0 "TP35" H 6250 2650 50  0000 C BNN
F 1 "TEST" H 6250 2600 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6250 2350 50  0001 C CNN
F 3 "" H 6250 2350 50  0001 C CNN
	1    6250 2350
	-1   0    0    1   
$EndComp
$Comp
L TEST TP36
U 1 1 5A4316FC
P 6250 3250
F 0 "TP36" H 6250 3550 50  0000 C BNN
F 1 "TEST" H 6250 3500 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6250 3250 50  0001 C CNN
F 3 "" H 6250 3250 50  0001 C CNN
	1    6250 3250
	-1   0    0    1   
$EndComp
$Comp
L TEST TP37
U 1 1 5A4318DD
P 6250 4150
F 0 "TP37" H 6250 4450 50  0000 C BNN
F 1 "TEST" H 6250 4400 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6250 4150 50  0001 C CNN
F 3 "" H 6250 4150 50  0001 C CNN
	1    6250 4150
	-1   0    0    1   
$EndComp
$Comp
L TEST TP38
U 1 1 5A431B1E
P 6250 5550
F 0 "TP38" H 6250 5850 50  0000 C BNN
F 1 "TEST" H 6250 5800 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 6250 5550 50  0001 C CNN
F 3 "" H 6250 5550 50  0001 C CNN
	1    6250 5550
	-1   0    0    1   
$EndComp
$Comp
L TEST TP39
U 1 1 5A431F1F
P 7050 1100
F 0 "TP39" H 7050 1400 50  0000 C BNN
F 1 "TEST" H 7050 1350 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7050 1100 50  0001 C CNN
F 3 "" H 7050 1100 50  0001 C CNN
	1    7050 1100
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP40
U 1 1 5A431FA4
P 7050 2000
F 0 "TP40" H 7050 2300 50  0000 C BNN
F 1 "TEST" H 7050 2250 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7050 2000 50  0001 C CNN
F 3 "" H 7050 2000 50  0001 C CNN
	1    7050 2000
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP41
U 1 1 5A4321A3
P 7050 2900
F 0 "TP41" H 7050 3200 50  0000 C BNN
F 1 "TEST" H 7050 3150 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7050 2900 50  0001 C CNN
F 3 "" H 7050 2900 50  0001 C CNN
	1    7050 2900
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP42
U 1 1 5A432222
P 7050 3800
F 0 "TP42" H 7050 4100 50  0000 C BNN
F 1 "TEST" H 7050 4050 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7050 3800 50  0001 C CNN
F 3 "" H 7050 3800 50  0001 C CNN
	1    7050 3800
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP43
U 1 1 5A432441
P 7050 4700
F 0 "TP43" H 7050 5000 50  0000 C BNN
F 1 "TEST" H 7050 4950 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7050 4700 50  0001 C CNN
F 3 "" H 7050 4700 50  0001 C CNN
	1    7050 4700
	0    -1   -1   0   
$EndComp
$Comp
L TEST TP44
U 1 1 5A4324C6
P 7050 5200
F 0 "TP44" H 7050 5500 50  0000 C BNN
F 1 "TEST" H 7050 5450 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7050 5200 50  0001 C CNN
F 3 "" H 7050 5200 50  0001 C CNN
	1    7050 5200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7050 5200 7100 5200
Connection ~ 7100 5200
Connection ~ 7100 4700
Connection ~ 7100 3800
Wire Wire Line
	6250 5550 6250 5500
Connection ~ 6250 5500
Wire Wire Line
	6250 4150 6250 4100
Connection ~ 6250 4100
Wire Wire Line
	6250 3250 6250 3200
Connection ~ 6250 3200
Connection ~ 7100 2900
Wire Wire Line
	6250 2350 6250 2300
Connection ~ 6250 2300
Connection ~ 7100 2000
Wire Wire Line
	6250 1450 6250 1400
Connection ~ 6250 1400
Connection ~ 7100 1100
Connection ~ 3500 1100
Wire Wire Line
	2650 1450 2650 1400
Connection ~ 2650 1400
Connection ~ 3500 2000
Wire Wire Line
	2650 2350 2650 2300
Connection ~ 2650 2300
Connection ~ 3500 2900
Wire Wire Line
	2650 3250 2650 3200
Connection ~ 2650 3200
Connection ~ 3500 3800
Wire Wire Line
	2650 4150 2650 4100
Connection ~ 2650 4100
Connection ~ 3500 5200
Wire Wire Line
	2650 5550 2650 5500
Connection ~ 2650 5500
$Comp
L TEST TP14
U 1 1 5A4421E8
P 1950 1350
F 0 "TP14" H 1950 1650 50  0000 C BNN
F 1 "TEST" H 1950 1600 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1950 1350 50  0001 C CNN
F 3 "" H 1950 1350 50  0001 C CNN
	1    1950 1350
	1    0    0    -1  
$EndComp
$Comp
L TEST TP15
U 1 1 5A4425C7
P 1950 2250
F 0 "TP15" H 1950 2550 50  0000 C BNN
F 1 "TEST" H 1950 2500 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1950 2250 50  0001 C CNN
F 3 "" H 1950 2250 50  0001 C CNN
	1    1950 2250
	1    0    0    -1  
$EndComp
$Comp
L TEST TP16
U 1 1 5A4429B6
P 1950 3150
F 0 "TP16" H 1950 3450 50  0000 C BNN
F 1 "TEST" H 1950 3400 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1950 3150 50  0001 C CNN
F 3 "" H 1950 3150 50  0001 C CNN
	1    1950 3150
	1    0    0    -1  
$EndComp
$Comp
L TEST TP17
U 1 1 5A442E2F
P 1950 4050
F 0 "TP17" H 1950 4350 50  0000 C BNN
F 1 "TEST" H 1950 4300 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1950 4050 50  0001 C CNN
F 3 "" H 1950 4050 50  0001 C CNN
	1    1950 4050
	1    0    0    -1  
$EndComp
$Comp
L TEST TP18
U 1 1 5A443381
P 1950 5450
F 0 "TP18" H 1950 5750 50  0000 C BNN
F 1 "TEST" H 1950 5700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 1950 5450 50  0001 C CNN
F 3 "" H 1950 5450 50  0001 C CNN
	1    1950 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 5450 1950 5500
Connection ~ 1950 5500
Wire Wire Line
	1950 4050 1950 4100
Connection ~ 1950 4100
Wire Wire Line
	1950 3150 1950 3200
Connection ~ 1950 3200
Wire Wire Line
	1950 2250 1950 2300
Connection ~ 1950 2300
Wire Wire Line
	1950 1350 1950 1400
Connection ~ 1950 1400
$Comp
L TEST TP29
U 1 1 5A4466AE
P 5550 1350
F 0 "TP29" H 5550 1650 50  0000 C BNN
F 1 "TEST" H 5550 1600 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5550 1350 50  0001 C CNN
F 3 "" H 5550 1350 50  0001 C CNN
	1    5550 1350
	1    0    0    -1  
$EndComp
$Comp
L TEST TP30
U 1 1 5A44699D
P 5550 2250
F 0 "TP30" H 5550 2550 50  0000 C BNN
F 1 "TEST" H 5550 2500 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5550 2250 50  0001 C CNN
F 3 "" H 5550 2250 50  0001 C CNN
	1    5550 2250
	1    0    0    -1  
$EndComp
$Comp
L TEST TP31
U 1 1 5A446C06
P 5550 3150
F 0 "TP31" H 5550 3450 50  0000 C BNN
F 1 "TEST" H 5550 3400 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5550 3150 50  0001 C CNN
F 3 "" H 5550 3150 50  0001 C CNN
	1    5550 3150
	1    0    0    -1  
$EndComp
$Comp
L TEST TP32
U 1 1 5A446CA9
P 5550 4050
F 0 "TP32" H 5550 4350 50  0000 C BNN
F 1 "TEST" H 5550 4300 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5550 4050 50  0001 C CNN
F 3 "" H 5550 4050 50  0001 C CNN
	1    5550 4050
	1    0    0    -1  
$EndComp
$Comp
L TEST TP33
U 1 1 5A446F6B
P 5550 5450
F 0 "TP33" H 5550 5750 50  0000 C BNN
F 1 "TEST" H 5550 5700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 5550 5450 50  0001 C CNN
F 3 "" H 5550 5450 50  0001 C CNN
	1    5550 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 5450 5550 5500
Connection ~ 5550 5500
Wire Wire Line
	5550 4050 5550 4100
Connection ~ 5550 4100
Wire Wire Line
	5550 3150 5550 3200
Connection ~ 5550 3200
Wire Wire Line
	5550 2250 5550 2300
Connection ~ 5550 2300
Wire Wire Line
	5550 1350 5550 1400
Connection ~ 5550 1400
$Comp
L Q_NMOS_GSD Q10
U 1 1 5A4D5EE5
P 7000 5500
F 0 "Q10" H 7200 5550 50  0000 L CNN
F 1 "IRLML0060" H 7200 5450 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 7200 5600 50  0001 C CNN
F 3 "" H 7000 5500 50  0001 C CNN
	1    7000 5500
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q7
U 1 1 5A5BC6F7
P 7000 4100
F 0 "Q7" H 7200 4150 50  0000 L CNN
F 1 "IRLML0060" H 7200 4050 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 7200 4200 50  0001 C CNN
F 3 "" H 7000 4100 50  0001 C CNN
	1    7000 4100
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q6
U 1 1 5A5BC7E1
P 7000 3200
F 0 "Q6" H 7200 3250 50  0000 L CNN
F 1 "IRLML0060" H 7200 3150 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 7200 3300 50  0001 C CNN
F 3 "" H 7000 3200 50  0001 C CNN
	1    7000 3200
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q5
U 1 1 5A5BC8BE
P 7000 2300
F 0 "Q5" H 7200 2350 50  0000 L CNN
F 1 "IRLML0060" H 7200 2250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 7200 2400 50  0001 C CNN
F 3 "" H 7000 2300 50  0001 C CNN
	1    7000 2300
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q4
U 1 1 5A5BC99E
P 7000 1400
F 0 "Q4" H 7200 1450 50  0000 L CNN
F 1 "IRLML0060" H 7200 1350 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 7200 1500 50  0001 C CNN
F 3 "" H 7000 1400 50  0001 C CNN
	1    7000 1400
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q8
U 1 1 5A5BCA83
P 3400 1400
F 0 "Q8" H 3600 1450 50  0000 L CNN
F 1 "IRLML0060" H 3600 1350 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 3600 1500 50  0001 C CNN
F 3 "" H 3400 1400 50  0001 C CNN
	1    3400 1400
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q1
U 1 1 5A5BCBCD
P 3400 2300
F 0 "Q1" H 3600 2350 50  0000 L CNN
F 1 "IRLML0060" H 3600 2250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 3600 2400 50  0001 C CNN
F 3 "" H 3400 2300 50  0001 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q2
U 1 1 5A5BCCB2
P 3400 3200
F 0 "Q2" H 3600 3250 50  0000 L CNN
F 1 "IRLML0060" H 3600 3150 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 3600 3300 50  0001 C CNN
F 3 "" H 3400 3200 50  0001 C CNN
	1    3400 3200
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q3
U 1 1 5A5BCE5C
P 3400 4100
F 0 "Q3" H 3600 4150 50  0000 L CNN
F 1 "IRLML0060" H 3600 4050 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 3600 4200 50  0001 C CNN
F 3 "" H 3400 4100 50  0001 C CNN
	1    3400 4100
	1    0    0    -1  
$EndComp
$Comp
L Q_NMOS_GSD Q9
U 1 1 5A5BCF4D
P 3400 5500
F 0 "Q9" H 3600 5550 50  0000 L CNN
F 1 "IRLML0060" H 3600 5450 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 3600 5600 50  0001 C CNN
F 3 "" H 3400 5500 50  0001 C CNN
	1    3400 5500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
