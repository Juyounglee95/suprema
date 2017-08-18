EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:Try001-cache
EELAYER 25 0
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
L R R1
U 1 1 5983C287
P 3150 1950
F 0 "R1" V 3230 1950 50  0000 C CNN
F 1 "220" V 3150 1950 50  0000 C CNN
F 2 "Resistors_THT:R_Radial_Power_L9.0mm_W10.0mm_Px2.70mm_Py2.30mm" V 3080 1950 50  0001 C CNN
F 3 "" H 3150 1950 50  0001 C CNN
	1    3150 1950
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5983C336
P 3700 1650
F 0 "D1" H 3700 1750 50  0000 C CNN
F 1 "LED" H 3700 1550 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3700 1650 50  0001 C CNN
F 3 "" H 3700 1650 50  0001 C CNN
	1    3700 1650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR01
U 1 1 5983C683
P 4250 1500
F 0 "#PWR01" H 4250 1350 50  0001 C CNN
F 1 "+5V" H 4250 1640 50  0000 C CNN
F 2 "" H 4250 1500 50  0001 C CNN
F 3 "" H 4250 1500 50  0001 C CNN
	1    4250 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5983C69B
P 3150 2350
F 0 "#PWR02" H 3150 2100 50  0001 C CNN
F 1 "GND" H 3150 2200 50  0000 C CNN
F 2 "" H 3150 2350 50  0001 C CNN
F 3 "" H 3150 2350 50  0001 C CNN
	1    3150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1500 4250 1650
Wire Wire Line
	4250 1650 3850 1650
Wire Wire Line
	3550 1650 3150 1650
Wire Wire Line
	3150 1650 3150 1800
Wire Wire Line
	3150 2100 3150 2350
$Comp
L CONN_01X02 J1
U 1 1 5983C6E9
P 2050 1500
F 0 "J1" H 2050 1650 50  0000 C CNN
F 1 "CONN_01X02" V 2150 1500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 2050 1500 50  0001 C CNN
F 3 "" H 2050 1500 50  0001 C CNN
	1    2050 1500
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 5983C8CD
P 2450 1250
F 0 "#PWR03" H 2450 1100 50  0001 C CNN
F 1 "+5V" H 2450 1390 50  0000 C CNN
F 2 "" H 2450 1250 50  0001 C CNN
F 3 "" H 2450 1250 50  0001 C CNN
	1    2450 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5983C8E7
P 2450 1750
F 0 "#PWR04" H 2450 1500 50  0001 C CNN
F 1 "GND" H 2450 1600 50  0000 C CNN
F 2 "" H 2450 1750 50  0001 C CNN
F 3 "" H 2450 1750 50  0001 C CNN
	1    2450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1450 2450 1450
Wire Wire Line
	2450 1450 2450 1250
Wire Wire Line
	2250 1550 2450 1550
Wire Wire Line
	2450 1550 2450 1750
$Comp
L R R?
U 1 1 5983CBF9
P 3150 1950
F 0 "R?" V 3230 1950 50  0000 C CNN
F 1 "220" V 3150 1950 50  0000 C CNN
F 2 "Resistors_THT:R_Radial_Power_L9.0mm_W10.0mm_Px2.70mm_Py2.30mm" V 3080 1950 50  0001 C CNN
F 3 "" H 3150 1950 50  0001 C CNN
	1    3150 1950
	1    0    0    -1  
$EndComp
$Comp
L LED D?
U 1 1 5983CBFA
P 3700 1650
F 0 "D?" H 3700 1750 50  0000 C CNN
F 1 "LED" H 3700 1550 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3700 1650 50  0001 C CNN
F 3 "" H 3700 1650 50  0001 C CNN
	1    3700 1650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5983CBFB
P 4250 1500
F 0 "#PWR?" H 4250 1350 50  0001 C CNN
F 1 "+5V" H 4250 1640 50  0000 C CNN
F 2 "" H 4250 1500 50  0001 C CNN
F 3 "" H 4250 1500 50  0001 C CNN
	1    4250 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5983CBFC
P 3150 2350
F 0 "#PWR?" H 3150 2100 50  0001 C CNN
F 1 "GND" H 3150 2200 50  0000 C CNN
F 2 "" H 3150 2350 50  0001 C CNN
F 3 "" H 3150 2350 50  0001 C CNN
	1    3150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1500 4250 1650
Wire Wire Line
	4250 1650 3850 1650
Wire Wire Line
	3550 1650 3150 1650
Wire Wire Line
	3150 1650 3150 1800
Wire Wire Line
	3150 2100 3150 2350
$Comp
L CONN_01X02 J?
U 1 1 5983CBFD
P 2050 1500
F 0 "J?" H 2050 1650 50  0000 C CNN
F 1 "CONN_01X02" V 2150 1500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch1.27mm" H 2050 1500 50  0001 C CNN
F 3 "" H 2050 1500 50  0001 C CNN
	1    2050 1500
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5983CBFE
P 2450 1250
F 0 "#PWR?" H 2450 1100 50  0001 C CNN
F 1 "+5V" H 2450 1390 50  0000 C CNN
F 2 "" H 2450 1250 50  0001 C CNN
F 3 "" H 2450 1250 50  0001 C CNN
	1    2450 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5983CBFF
P 2450 1750
F 0 "#PWR?" H 2450 1500 50  0001 C CNN
F 1 "GND" H 2450 1600 50  0000 C CNN
F 2 "" H 2450 1750 50  0001 C CNN
F 3 "" H 2450 1750 50  0001 C CNN
	1    2450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1450 2450 1450
Wire Wire Line
	2450 1450 2450 1250
Wire Wire Line
	2250 1550 2450 1550
Wire Wire Line
	2450 1550 2450 1750
$EndSCHEMATC
