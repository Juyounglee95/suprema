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
LIBS:stm32f4
LIBS:tact_switch
LIBS:DHT11
LIBS:stm32f4-cache
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
L SFM6020 U?
U 1 1 59882BB3
P 11025 6475
F 0 "U?" H 11325 8725 60  0000 C CNN
F 1 "SFM6020" H 11825 8725 60  0000 C CNN
F 2 "" H 11075 6525 60  0001 C CNN
F 3 "" H 11075 6525 60  0001 C CNN
	1    11025 6475
	-1   0    0    -1  
$EndComp
$Comp
L LCD16X2 DS?
U 1 1 59884B91
P 2300 2525
F 0 "DS?" H 1500 2925 50  0000 C CNN
F 1 "LCD16X2" H 3000 2925 50  0000 C CNN
F 2 "WC1602A" H 2300 2475 50  0001 C CIN
F 3 "" H 2300 2525 50  0001 C CNN
	1    2300 2525
	0    -1   1    0   
$EndComp
$Comp
L Buzzer BZ?
U 1 1 59884800
P 1300 875
F 0 "BZ?" H 1450 925 50  0000 L CNN
F 1 "Buzzer" H 1450 825 50  0000 L CNN
F 2 "" V 1275 975 50  0001 C CNN
F 3 "" V 1275 975 50  0001 C CNN
	1    1300 875 
	-1   0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59886366
P 1000 1350
F 0 "R?" V 1080 1350 50  0000 C CNN
F 1 "R" V 1000 1350 50  0000 C CNN
F 2 "" V 930 1350 50  0001 C CNN
F 3 "" H 1000 1350 50  0001 C CNN
	1    1000 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59892911
P 1100 5725
F 0 "#PWR?" H 1100 5475 50  0001 C CNN
F 1 "GND" H 1100 5575 50  0000 C CNN
F 2 "" H 1100 5725 50  0001 C CNN
F 3 "" H 1100 5725 50  0001 C CNN
	1    1100 5725
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 59892951
P 1125 4850
F 0 "#PWR?" H 1125 4600 50  0001 C CNN
F 1 "GND" H 1125 4700 50  0000 C CNN
F 2 "" H 1125 4850 50  0001 C CNN
F 3 "" H 1125 4850 50  0001 C CNN
	1    1125 4850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 59892974
P 1100 4125
F 0 "#PWR?" H 1100 3875 50  0001 C CNN
F 1 "GND" H 1100 3975 50  0000 C CNN
F 2 "" H 1100 4125 50  0001 C CNN
F 3 "" H 1100 4125 50  0001 C CNN
	1    1100 4125
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 59893702
P 10375 1450
F 0 "#PWR?" H 10375 1200 50  0001 C CNN
F 1 "GND" H 10375 1300 50  0000 C CNN
F 2 "" H 10375 1450 50  0001 C CNN
F 3 "" H 10375 1450 50  0001 C CNN
	1    10375 1450
	0    -1   1    0   
$EndComp
Text Notes 9825 1625 0    40   ~ 0
Start Button
Text Notes 1325 4300 0    40   ~ 0
Enroll Button
Text Notes 1300 5050 0    40   ~ 0
Identify Button
Text Notes 1325 5925 0    40   ~ 0
Delete Button
$Comp
L +3.3V #PWR?
U 1 1 5989455C
P 1104 3902
F 0 "#PWR?" H 1104 3752 50  0001 C CNN
F 1 "+3.3V" H 1104 4042 50  0000 C CNN
F 2 "" H 1104 3902 50  0001 C CNN
F 3 "" H 1104 3902 50  0001 C CNN
	1    1104 3902
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 59894703
P 1104 4624
F 0 "#PWR?" H 1104 4474 50  0001 C CNN
F 1 "+3.3V" H 1104 4764 50  0000 C CNN
F 2 "" H 1104 4624 50  0001 C CNN
F 3 "" H 1104 4624 50  0001 C CNN
	1    1104 4624
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 59894729
P 1101 5499
F 0 "#PWR?" H 1101 5349 50  0001 C CNN
F 1 "+3.3V" H 1101 5639 50  0000 C CNN
F 2 "" H 1101 5499 50  0001 C CNN
F 3 "" H 1101 5499 50  0001 C CNN
	1    1101 5499
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 59894761
P 10379 1227
F 0 "#PWR?" H 10379 1077 50  0001 C CNN
F 1 "+3.3V" H 10379 1367 50  0000 C CNN
F 2 "" H 10379 1227 50  0001 C CNN
F 3 "" H 10379 1227 50  0001 C CNN
	1    10379 1227
	0    1    -1   0   
$EndComp
$Comp
L DHT11 U?
U 1 1 59895093
P 1450 6725
F 0 "U?" H 1350 6925 40  0000 C CNN
F 1 "DHT11" H 1500 6925 40  0000 C CNN
F 2 "" H 1461 6750 40  0001 C CNN
F 3 "" H 1461 6750 40  0001 C CNN
	1    1450 6725
	0    -1   1    0   
$EndComp
$Comp
L tact_switch U?
U 1 1 5989664F
P 1500 4025
F 0 "U?" H 1375 4300 30  0000 C CNN
F 1 "tact_switch" H 1575 4300 30  0000 C CNN
F 2 "" H 1500 4025 60  0001 C CNN
F 3 "" H 1500 4025 60  0001 C CNN
	1    1500 4025
	1    0    0    -1  
$EndComp
$Comp
L tact_switch U?
U 1 1 59896F79
P 1500 4750
F 0 "U?" H 1375 5025 30  0000 C CNN
F 1 "tact_switch" H 1575 5025 30  0000 C CNN
F 2 "" H 1500 4750 60  0001 C CNN
F 3 "" H 1500 4750 60  0001 C CNN
	1    1500 4750
	1    0    0    -1  
$EndComp
$Comp
L tact_switch U?
U 1 1 59896FCD
P 1500 5625
F 0 "U?" H 1375 5900 30  0000 C CNN
F 1 "tact_switch" H 1575 5900 30  0000 C CNN
F 2 "" H 1500 5625 60  0001 C CNN
F 3 "" H 1500 5625 60  0001 C CNN
	1    1500 5625
	1    0    0    -1  
$EndComp
$Comp
L tact_switch U?
U 1 1 598977F4
P 10000 1350
F 0 "U?" H 9875 1625 30  0000 C CNN
F 1 "tact_switch" H 10075 1625 30  0000 C CNN
F 2 "" H 10000 1350 60  0001 C CNN
F 3 "" H 10000 1350 60  0001 C CNN
	1    10000 1350
	1    0    0    -1  
$EndComp
Text Notes 1425 750  0    40   ~ 0
PF11
Text Notes 9475 1200 0    40   ~ 0
PF2
Text Notes 9550 4750 0    40   ~ 0
PC7
Text Notes 9550 4950 0    40   ~ 0
PC6
Text Notes 1925 5475 0    40   ~ 0
PF13
Text Notes 1925 4600 0    40   ~ 0
PF10
Text Notes 1950 3875 0    40   ~ 0
PF3
Text Notes 1725 6625 0    40   ~ 0
PE1
Text Notes 2875 2075 0    40   ~ 0
PC4
Text Notes 2875 2350 0    40   ~ 0
PC5
Text Notes 2875 2775 0    40   ~ 0
PA4
Text Notes 2875 2875 0    40   ~ 0
PA5
Text Notes 2875 2975 0    40   ~ 0
PA6
Text Notes 2875 3075 0    40   ~ 0
PA7
$Comp
L stm32f4 U?
U 1 1 59848217
P 3925 2425
F 0 "U?" H 3925 6225 100 0000 C CNN
F 1 "stm32f4" H 4575 6225 100 0000 C CNN
F 2 "" H 2775 3925 60  0001 C CNN
F 3 "" H 2775 3925 60  0001 C CNN
	1    3925 2425
	0    1    1    0   
$EndComp
Wire Wire Line
	9475 4875 9725 4875
Wire Wire Line
	1400 775  6125 775 
Wire Wire Line
	1400 975  2100 975 
Wire Wire Line
	2100 975  3000 975 
Wire Wire Line
	3000 975  3300 975 
Wire Wire Line
	3300 975  4825 975 
Wire Wire Line
	4825 975  4825 2175
Wire Wire Line
	6125 775  6125 2175
Wire Wire Line
	3550 2075 2800 2075
Wire Wire Line
	2800 2775 3675 2775
Wire Wire Line
	2800 2875 4375 2875
Wire Wire Line
	4375 2875 4375 3375
Wire Wire Line
	2800 2975 3900 2975
Wire Wire Line
	2800 3075 3900 3075
Wire Wire Line
	2800 1875 3425 1875
Wire Wire Line
	3550 1325 5725 1325
Wire Wire Line
	5725 1325 5725 2175
Wire Wire Line
	3675 1450 5525 1450
Wire Wire Line
	5525 1450 5525 2175
Wire Wire Line
	2800 1975 3150 1975
Wire Wire Line
	5625 2175 5625 1775
Wire Wire Line
	5625 1775 3900 1775
Wire Wire Line
	2100 1200 1000 1200
Wire Wire Line
	3150 1500 1000 1500
Wire Wire Line
	4425 5500 4425 3825
Wire Wire Line
	4425 3825 7975 3825
Wire Wire Line
	7975 3825 7975 1925
Wire Wire Line
	7975 1925 6225 1925
Wire Wire Line
	6225 1925 6225 2175
Wire Wire Line
	6025 3900 1900 3900
Wire Wire Line
	6025 3275 6025 3900
Wire Wire Line
	1900 5500 4425 5500
Wire Wire Line
	1900 4125 2125 4125
Wire Wire Line
	1700 6650 3850 6650
Wire Wire Line
	3850 6650 3850 4275
Wire Wire Line
	3850 4275 5625 4275
Wire Wire Line
	5625 4275 5625 4375
Wire Wire Line
	4925 6725 1700 6725
Wire Wire Line
	4925 5475 4925 6725
Wire Wire Line
	1700 6800 4675 6800
Wire Wire Line
	4675 6800 4675 5725
Connection ~ 4675 5725
Wire Wire Line
	7125 5975 9475 5975
Wire Wire Line
	7125 5975 7125 5475
Wire Wire Line
	7225 1450 7225 2175
Wire Wire Line
	5925 1225 5925 2175
Wire Wire Line
	1900 5725 2425 5725
Wire Wire Line
	2425 5725 4675 5725
Wire Wire Line
	4675 5725 4825 5725
Wire Wire Line
	1900 4850 2125 4850
Wire Wire Line
	2125 4850 2425 4850
Wire Wire Line
	2425 4850 2425 5725
Connection ~ 2425 5725
Wire Wire Line
	2125 4125 2125 4850
Connection ~ 2125 4850
Wire Wire Line
	1900 4625 3375 4625
Wire Wire Line
	3375 4625 3375 4100
Wire Wire Line
	3375 4100 6125 4100
Wire Wire Line
	6125 4100 6125 3275
Wire Wire Line
	2800 1775 3000 1775
Connection ~ 3000 975 
Wire Wire Line
	2800 2275 3550 2275
Wire Wire Line
	3425 3175 2800 3175
Wire Wire Line
	3425 3750 4925 3750
Wire Wire Line
	4925 3750 4925 4375
Connection ~ 3425 3175
Wire Wire Line
	2800 3275 4825 3275
Wire Wire Line
	2800 2175 3300 2175
Connection ~ 3300 975 
Connection ~ 2100 975 
Wire Wire Line
	7225 5475 9725 5475
Wire Wire Line
	9475 5975 9475 4875
Wire Wire Line
	9725 4775 9475 4775
Wire Wire Line
	9475 4150 7125 4150
Wire Wire Line
	7125 4150 7125 4375
Wire Wire Line
	3000 1775 3000 975 
Wire Wire Line
	3150 1975 3150 1500
Wire Wire Line
	3425 1875 3425 3175
Wire Wire Line
	3425 3175 3425 3750
Wire Wire Line
	3550 2075 3550 1325
Wire Wire Line
	3300 2175 3300 975 
Wire Wire Line
	3550 2275 3550 3475
Wire Wire Line
	3550 3475 5725 3475
Wire Wire Line
	5725 3475 5725 3275
Wire Wire Line
	3675 2775 3675 1450
Wire Wire Line
	4375 3375 5525 3375
Wire Wire Line
	5525 3375 5525 3275
Wire Wire Line
	3900 3075 3900 3625
Wire Wire Line
	3900 3625 5625 3625
Wire Wire Line
	5625 3625 5625 3275
Wire Wire Line
	3900 1775 3900 2975
Wire Wire Line
	2100 1200 2100 975 
Wire Wire Line
	9650 1225 5925 1225
Wire Wire Line
	9650 1450 7225 1450
Wire Wire Line
	9475 4775 9475 4150
Wire Wire Line
	4825 5725 4825 5475
$EndSCHEMATC
