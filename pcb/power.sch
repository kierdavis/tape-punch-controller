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
Sheet 3 7
Title "28V input and 15V/3.3V supplies"
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +28V #PWR020
U 1 1 5A3BEEA9
P 4750 2500
F 0 "#PWR020" H 4750 2350 50  0001 C CNN
F 1 "+28V" H 4750 2650 50  0000 C CNN
F 2 "" H 5000 2550 50  0001 C CNN
F 3 "" H 5000 2550 50  0001 C CNN
	1    4750 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 5A3BEED9
P 4750 2700
F 0 "#PWR021" H 4750 2450 50  0001 C CNN
F 1 "GND" H 4750 2550 50  0000 C CNN
F 2 "" H 4750 2700 50  0001 C CNN
F 3 "" H 4750 2700 50  0001 C CNN
	1    4750 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2550 4750 2550
Wire Wire Line
	4750 2550 4750 2500
Wire Wire Line
	4100 2650 4750 2650
Wire Wire Line
	4750 2650 4750 2700
$Comp
L TSR_1-2433 U4
U 1 1 5A3ECA6C
P 7050 2500
F 0 "U4" H 6900 2625 50  0000 C CNN
F 1 "TSR_1-2433" H 7050 2625 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 7050 2700 50  0001 C CNN
F 3 "" H 7150 2250 50  0001 C CNN
	1    7050 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 5A3ECB59
P 7050 2850
F 0 "#PWR022" H 7050 2600 50  0001 C CNN
F 1 "GND" H 7050 2700 50  0000 C CNN
F 2 "" H 7050 2850 50  0001 C CNN
F 3 "" H 7050 2850 50  0001 C CNN
	1    7050 2850
	1    0    0    -1  
$EndComp
$Comp
L +28V #PWR023
U 1 1 5A3ECB8D
P 6650 2450
F 0 "#PWR023" H 6650 2300 50  0001 C CNN
F 1 "+28V" H 6650 2600 50  0000 C CNN
F 2 "" H 6900 2500 50  0001 C CNN
F 3 "" H 6900 2500 50  0001 C CNN
	1    6650 2450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR024
U 1 1 5A3ECBA7
P 8050 2450
F 0 "#PWR024" H 8050 2300 50  0001 C CNN
F 1 "+3.3V" H 8050 2590 50  0000 C CNN
F 2 "" H 8050 2450 50  0001 C CNN
F 3 "" H 8050 2450 50  0001 C CNN
	1    8050 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2450 6650 2500
Wire Wire Line
	6650 2500 6750 2500
Wire Wire Line
	7050 2800 7050 2850
Wire Wire Line
	7350 2500 8050 2500
Wire Wire Line
	7750 2450 7750 2550
$Comp
L TSR_1-24150 U5
U 1 1 5A3ECEEC
P 7050 4450
F 0 "U5" H 6900 4575 50  0000 C CNN
F 1 "TSR_1-24150" H 7050 4575 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 7050 4650 50  0001 C CNN
F 3 "" H 7150 4200 50  0001 C CNN
	1    7050 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4450 8050 4450
Wire Wire Line
	7750 4400 7750 4500
$Comp
L +28V #PWR025
U 1 1 5A3ECFDF
P 6650 4400
F 0 "#PWR025" H 6650 4250 50  0001 C CNN
F 1 "+28V" H 6650 4550 50  0000 C CNN
F 2 "" H 6900 4450 50  0001 C CNN
F 3 "" H 6900 4450 50  0001 C CNN
	1    6650 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4400 6650 4450
Wire Wire Line
	6650 4450 6750 4450
$Comp
L GND #PWR026
U 1 1 5A3ED012
P 7050 4800
F 0 "#PWR026" H 7050 4550 50  0001 C CNN
F 1 "GND" H 7050 4650 50  0000 C CNN
F 2 "" H 7050 4800 50  0001 C CNN
F 3 "" H 7050 4800 50  0001 C CNN
	1    7050 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4750 7050 4800
$Comp
L +15V #PWR027
U 1 1 5A3ED2D9
P 8050 4400
F 0 "#PWR027" H 8050 4250 50  0001 C CNN
F 1 "+15V" H 8050 4540 50  0000 C CNN
F 2 "" H 8050 4400 50  0001 C CNN
F 3 "" H 8050 4400 50  0001 C CNN
	1    8050 4400
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 5A3ED752
P 7750 4650
F 0 "C11" H 7775 4750 50  0000 L CNN
F 1 "10u" H 7775 4550 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 7788 4500 50  0001 C CNN
F 3 "" H 7750 4650 50  0001 C CNN
	1    7750 4650
	-1   0    0    1   
$EndComp
$Comp
L C C10
U 1 1 5A3ED84B
P 7750 2700
F 0 "C10" H 7775 2800 50  0000 L CNN
F 1 "10u" H 7775 2600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 7788 2550 50  0001 C CNN
F 3 "" H 7750 2700 50  0001 C CNN
	1    7750 2700
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR028
U 1 1 5A3ED923
P 7750 2900
F 0 "#PWR028" H 7750 2650 50  0001 C CNN
F 1 "GND" H 7750 2750 50  0000 C CNN
F 2 "" H 7750 2900 50  0001 C CNN
F 3 "" H 7750 2900 50  0001 C CNN
	1    7750 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 5A3ED96E
P 7750 4850
F 0 "#PWR029" H 7750 4600 50  0001 C CNN
F 1 "GND" H 7750 4700 50  0000 C CNN
F 2 "" H 7750 4850 50  0001 C CNN
F 3 "" H 7750 4850 50  0001 C CNN
	1    7750 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 4850 7750 4800
Connection ~ 7750 4450
Connection ~ 7750 2500
Wire Wire Line
	7750 2900 7750 2850
$Comp
L R R5
U 1 1 5A3EF81E
P 3900 4250
F 0 "R5" V 3980 4250 50  0000 C CNN
F 1 "1.8k" V 3900 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" V 3830 4250 50  0001 C CNN
F 3 "" H 3900 4250 50  0001 C CNN
	1    3900 4250
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5A3EF881
P 4400 4250
F 0 "R6" V 4480 4250 50  0000 C CNN
F 1 "820" V 4400 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4330 4250 50  0001 C CNN
F 3 "" H 4400 4250 50  0001 C CNN
	1    4400 4250
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5A3EF8C2
P 4900 4250
F 0 "R7" V 4980 4250 50  0000 C CNN
F 1 "82" V 4900 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4830 4250 50  0001 C CNN
F 3 "" H 4900 4250 50  0001 C CNN
	1    4900 4250
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5A3EFAC9
P 3900 4650
F 0 "D1" H 3900 4750 50  0000 C CNN
F 1 "green" H 3900 4550 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 3900 4650 50  0001 C CNN
F 3 "" H 3900 4650 50  0001 C CNN
	1    3900 4650
	0    -1   -1   0   
$EndComp
$Comp
L LED D2
U 1 1 5A3EFB40
P 4400 4650
F 0 "D2" H 4400 4750 50  0000 C CNN
F 1 "green" H 4400 4550 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 4400 4650 50  0001 C CNN
F 3 "" H 4400 4650 50  0001 C CNN
	1    4400 4650
	0    -1   -1   0   
$EndComp
$Comp
L LED D3
U 1 1 5A3EFB83
P 4900 4650
F 0 "D3" H 4900 4750 50  0000 C CNN
F 1 "green" H 4900 4550 50  0000 C CNN
F 2 "LEDs:LED_0805_HandSoldering" H 4900 4650 50  0001 C CNN
F 3 "" H 4900 4650 50  0001 C CNN
	1    4900 4650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3900 4400 3900 4500
Wire Wire Line
	4400 4400 4400 4500
Wire Wire Line
	4900 4400 4900 4500
$Comp
L GND #PWR030
U 1 1 5A3F00B4
P 3900 4850
F 0 "#PWR030" H 3900 4600 50  0001 C CNN
F 1 "GND" H 3900 4700 50  0000 C CNN
F 2 "" H 3900 4850 50  0001 C CNN
F 3 "" H 3900 4850 50  0001 C CNN
	1    3900 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 5A3F033B
P 4400 4850
F 0 "#PWR031" H 4400 4600 50  0001 C CNN
F 1 "GND" H 4400 4700 50  0000 C CNN
F 2 "" H 4400 4850 50  0001 C CNN
F 3 "" H 4400 4850 50  0001 C CNN
	1    4400 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 5A3F0365
P 4900 4850
F 0 "#PWR032" H 4900 4600 50  0001 C CNN
F 1 "GND" H 4900 4700 50  0000 C CNN
F 2 "" H 4900 4850 50  0001 C CNN
F 3 "" H 4900 4850 50  0001 C CNN
	1    4900 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4800 3900 4850
Wire Wire Line
	4400 4800 4400 4850
Wire Wire Line
	4900 4800 4900 4850
$Comp
L +28V #PWR033
U 1 1 5A3F05A8
P 3900 4050
F 0 "#PWR033" H 3900 3900 50  0001 C CNN
F 1 "+28V" H 3900 4200 50  0000 C CNN
F 2 "" H 4150 4100 50  0001 C CNN
F 3 "" H 4150 4100 50  0001 C CNN
	1    3900 4050
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR034
U 1 1 5A3F05D2
P 4400 4050
F 0 "#PWR034" H 4400 3900 50  0001 C CNN
F 1 "+15V" H 4400 4190 50  0000 C CNN
F 2 "" H 4400 4050 50  0001 C CNN
F 3 "" H 4400 4050 50  0001 C CNN
	1    4400 4050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR035
U 1 1 5A3F05FC
P 4900 4050
F 0 "#PWR035" H 4900 3900 50  0001 C CNN
F 1 "+3.3V" H 4900 4190 50  0000 C CNN
F 2 "" H 4900 4050 50  0001 C CNN
F 3 "" H 4900 4050 50  0001 C CNN
	1    4900 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4050 3900 4100
Wire Wire Line
	4400 4050 4400 4100
Wire Wire Line
	4900 4050 4900 4100
$Comp
L TEST TP5
U 1 1 5A43BC95
P 4250 2500
F 0 "TP5" H 4250 2800 50  0000 C BNN
F 1 "TEST" H 4250 2750 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4250 2500 50  0001 C CNN
F 3 "" H 4250 2500 50  0001 C CNN
	1    4250 2500
	1    0    0    -1  
$EndComp
$Comp
L TEST TP6
U 1 1 5A43BD1B
P 4500 2500
F 0 "TP6" H 4500 2800 50  0000 C BNN
F 1 "TEST" H 4500 2750 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 4500 2500 50  0001 C CNN
F 3 "" H 4500 2500 50  0001 C CNN
	1    4500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2500 4250 2550
Connection ~ 4250 2550
Wire Wire Line
	4500 2500 4500 2650
Connection ~ 4500 2650
$Comp
L TEST TP7
U 1 1 5A43CBD8
P 7750 2450
F 0 "TP7" H 7750 2750 50  0000 C BNN
F 1 "TEST" H 7750 2700 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7750 2450 50  0001 C CNN
F 3 "" H 7750 2450 50  0001 C CNN
	1    7750 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 2500 8050 2450
$Comp
L TEST TP8
U 1 1 5A43CE4F
P 7750 4400
F 0 "TP8" H 7750 4700 50  0000 C BNN
F 1 "TEST" H 7750 4650 50  0000 C CNN
F 2 "Measurement_Points:Measurement_Point_Round-SMD-Pad_Small" H 7750 4400 50  0001 C CNN
F 3 "" H 7750 4400 50  0001 C CNN
	1    7750 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4450 8050 4400
Text Notes 3750 2050 0    60   ~ 0
28V power input connector
Text Notes 7000 2000 0    60   ~ 0
3.3V regulator
Text Notes 7100 3950 0    60   ~ 0
15V regulator
Text Notes 4200 3750 0    60   ~ 0
Power LEDs
$Comp
L Conn_01x02 J6
U 1 1 5A5A2D2F
P 3900 2650
F 0 "J6" H 3900 2750 50  0000 C CNN
F 1 "Conn_01x02" H 3900 2450 50  0000 C CNN
F 2 "Local:Multicomp_MC000048" H 3900 2650 50  0001 C CNN
F 3 "" H 3900 2650 50  0001 C CNN
	1    3900 2650
	-1   0    0    1   
$EndComp
$Comp
L PWR_FLAG #FLG036
U 1 1 5A5C13DD
P 1750 6750
F 0 "#FLG036" H 1750 6825 50  0001 C CNN
F 1 "PWR_FLAG" H 1750 6900 50  0000 C CNN
F 2 "" H 1750 6750 50  0001 C CNN
F 3 "" H 1750 6750 50  0001 C CNN
	1    1750 6750
	-1   0    0    1   
$EndComp
$Comp
L +28V #PWR037
U 1 1 5A5C1E08
P 1750 6700
F 0 "#PWR037" H 1750 6550 50  0001 C CNN
F 1 "+28V" H 1750 6850 50  0000 C CNN
F 2 "" H 2000 6750 50  0001 C CNN
F 3 "" H 2000 6750 50  0001 C CNN
	1    1750 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 6700 1750 6750
Text Notes 2100 6950 0    60   ~ 0
This is needed to stop KiCad's ERC complaining about\nthe 28V net not being driven. This warning occurs\nsince the pin that drives this net (J6 pin 2) is marked\nas passive (J6 is a standard library part so we can't\nchange that).
$EndSCHEMATC
