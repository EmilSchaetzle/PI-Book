EESchema Schematic File Version 4
EELAYER 26 0
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
L Device:Solar_Cell SC1
U 1 1 5C3A75C2
P 3200 3600
F 0 "SC1" H 3308 3696 50  0001 L CNN
F 1 "Solarzelle" H 3308 3650 50  0000 L CNN
F 2 "" V 3200 3660 50  0001 C CNN
F 3 "~" V 3200 3660 50  0001 C CNN
	1    3200 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5C3A7712
P 3200 1250
F 0 "BT1" H 3318 1346 50  0000 L CNN
F 1 "Akkumulator" H 3318 1255 50  0000 L CNN
F 2 "" V 3200 1310 50  0001 C CNN
F 3 "~" V 3200 1310 50  0001 C CNN
	1    3200 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT2
U 1 1 5C3A77DB
P 3200 1700
F 0 "BT2" H 3318 1796 50  0000 L CNN
F 1 "Akkumulator" H 3318 1705 50  0000 L CNN
F 2 "" V 3200 1760 50  0001 C CNN
F 3 "~" V 3200 1760 50  0001 C CNN
	1    3200 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT4
U 1 1 5C3A7831
P 3200 2600
F 0 "BT4" H 3318 2696 50  0000 L CNN
F 1 "Akkumulator" H 3318 2605 50  0000 L CNN
F 2 "" V 3200 2660 50  0001 C CNN
F 3 "~" V 3200 2660 50  0001 C CNN
	1    3200 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT5
U 1 1 5C3A7858
P 3200 3050
F 0 "BT5" H 3318 3146 50  0000 L CNN
F 1 "Akkumulator" H 3318 3055 50  0000 L CNN
F 2 "" V 3200 3110 50  0001 C CNN
F 3 "~" V 3200 3110 50  0001 C CNN
	1    3200 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT3
U 1 1 5C3A78BE
P 3200 2150
F 0 "BT3" H 3318 2246 50  0000 L CNN
F 1 "Akkumulator" H 3318 2155 50  0000 L CNN
F 2 "" V 3200 2210 50  0001 C CNN
F 3 "~" V 3200 2210 50  0001 C CNN
	1    3200 2150
	1    0    0    -1  
$EndComp
$Comp
L mylib:Lademodul LM1
U 1 1 5C3AFA8B
P 4200 1200
F 0 "LM1" H 4000 1400 50  0000 C CNN
F 1 "Lademodul" H 4300 1400 50  0000 C CNN
F 2 "" H 4250 1100 50  0001 C CNN
F 3 "" H 4250 1100 50  0001 C CNN
	1    4200 1200
	1    0    0    -1  
$EndComp
$Comp
L mylib:Lademodul LM2
U 1 1 5C3B6F19
P 4200 1650
F 0 "LM2" H 4000 1850 50  0000 C CNN
F 1 "Lademodul" H 4300 1850 50  0000 C CNN
F 2 "" H 4250 1550 50  0001 C CNN
F 3 "" H 4250 1550 50  0001 C CNN
	1    4200 1650
	1    0    0    -1  
$EndComp
$Comp
L mylib:Lademodul LM3
U 1 1 5C3B6FBD
P 4200 2100
F 0 "LM3" H 4000 2300 50  0000 C CNN
F 1 "Lademodul" H 4300 2300 50  0000 C CNN
F 2 "" H 4250 2000 50  0001 C CNN
F 3 "" H 4250 2000 50  0001 C CNN
	1    4200 2100
	1    0    0    -1  
$EndComp
$Comp
L mylib:Lademodul LM4
U 1 1 5C3B6FF5
P 4200 2550
F 0 "LM4" H 4000 2750 50  0000 C CNN
F 1 "Lademodul" H 4300 2750 50  0000 C CNN
F 2 "" H 4250 2450 50  0001 C CNN
F 3 "" H 4250 2450 50  0001 C CNN
	1    4200 2550
	1    0    0    -1  
$EndComp
$Comp
L mylib:Lademodul LM5
U 1 1 5C3B7025
P 4200 3000
F 0 "LM5" H 4000 3200 50  0000 C CNN
F 1 "Lademodul" H 4300 3200 50  0000 C CNN
F 2 "" H 4250 2900 50  0001 C CNN
F 3 "" H 4250 2900 50  0001 C CNN
	1    4200 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1050 3900 1050
Wire Wire Line
	3900 1050 3900 1100
Wire Wire Line
	3900 1300 3900 1350
Wire Wire Line
	3900 1350 3200 1350
Wire Wire Line
	3200 1800 3900 1800
Wire Wire Line
	3900 1800 3900 1750
Wire Wire Line
	3200 1500 3900 1500
Wire Wire Line
	3900 1500 3900 1550
Wire Wire Line
	3900 2000 3900 1950
Wire Wire Line
	3900 1950 3200 1950
Wire Wire Line
	3200 2250 3900 2250
Wire Wire Line
	3900 2250 3900 2200
Wire Wire Line
	3900 2450 3900 2400
Wire Wire Line
	3900 2400 3200 2400
Wire Wire Line
	3900 2650 3900 2700
Wire Wire Line
	3900 2700 3200 2700
Wire Wire Line
	3900 2900 3900 2850
Wire Wire Line
	3900 2850 3200 2850
Wire Wire Line
	3900 3100 3900 3150
Wire Wire Line
	3900 3150 3200 3150
Wire Wire Line
	4500 1100 4900 1100
Wire Wire Line
	4900 1100 4900 1300
Wire Wire Line
	4900 2900 4500 2900
Wire Wire Line
	4500 2450 4900 2450
Connection ~ 4900 2450
Wire Wire Line
	4900 2450 4900 2900
Wire Wire Line
	4500 2000 4900 2000
Connection ~ 4900 2000
Wire Wire Line
	4900 2000 4900 2200
Wire Wire Line
	4500 1550 4900 1550
Connection ~ 4900 1550
Wire Wire Line
	4900 1550 4900 2000
NoConn ~ 4700 1550
NoConn ~ 4700 2000
NoConn ~ 4700 2450
NoConn ~ 4700 2900
Text Label 4900 2000 0    50   ~ 0
+3.86V
Text Label 4700 2350 0    50   ~ 0
GND
Wire Wire Line
	4700 1150 4500 1150
Wire Wire Line
	4700 1150 4700 1500
Wire Wire Line
	4500 1600 4700 1600
Connection ~ 4700 1600
Wire Wire Line
	4700 1600 4700 2050
Wire Wire Line
	4500 2050 4700 2050
Connection ~ 4700 2050
Wire Wire Line
	4700 2050 4700 2400
Wire Wire Line
	4500 2500 4700 2500
Connection ~ 4700 2500
Wire Wire Line
	4500 2950 4700 2950
Wire Wire Line
	4500 1700 4800 1700
Wire Wire Line
	4800 1700 4800 2150
Wire Wire Line
	4500 2150 4800 2150
Connection ~ 4800 2150
Wire Wire Line
	4800 2150 4800 2600
Wire Wire Line
	4700 2500 4700 2950
Wire Wire Line
	4500 2600 4800 2600
Connection ~ 4800 2600
Wire Wire Line
	4800 2600 4800 3050
Wire Wire Line
	4800 1700 4800 1250
Wire Wire Line
	4800 1250 4500 1250
Connection ~ 4800 1700
Wire Wire Line
	4500 1750 4600 1750
Wire Wire Line
	4600 1750 4600 2200
Wire Wire Line
	4600 3100 4500 3100
Wire Wire Line
	4500 2650 4600 2650
Connection ~ 4600 2650
Wire Wire Line
	4600 2650 4600 3050
Wire Wire Line
	4500 2200 4600 2200
Connection ~ 4600 2200
Wire Wire Line
	4600 2200 4600 2650
Wire Wire Line
	4600 1750 4600 1300
Wire Wire Line
	4600 1300 4500 1300
Connection ~ 4600 1750
NoConn ~ 4600 1550
NoConn ~ 4800 1550
NoConn ~ 4600 1600
NoConn ~ 4700 1700
NoConn ~ 4600 1700
NoConn ~ 4700 1250
NoConn ~ 4700 2150
NoConn ~ 4700 2600
NoConn ~ 4600 2600
NoConn ~ 4600 2500
NoConn ~ 4600 2450
NoConn ~ 4800 2450
NoConn ~ 4800 2000
NoConn ~ 4600 2000
NoConn ~ 4600 2150
NoConn ~ 4600 2050
NoConn ~ 4800 2900
NoConn ~ 4600 2900
NoConn ~ 4600 2950
NoConn ~ 4600 3050
Text Label 4600 1400 0    50   ~ 0
GND
Text Label 4800 3050 0    50   ~ 0
+5V
Wire Wire Line
	4600 3050 4600 3100
Wire Wire Line
	4500 3050 4800 3050
$Comp
L mylib:Spannungswandler SW2
U 1 1 5C3E6869
P 5500 1400
F 0 "SW2" H 5500 1725 50  0000 C CNN
F 1 "Spannungswandler" H 5500 1634 50  0000 C CNN
F 2 "" H 5500 1400 50  0001 C CNN
F 3 "" H 5500 1400 50  0001 C CNN
	1    5500 1400
	1    0    0    -1  
$EndComp
$Comp
L mylib:Spannungswandler SW3
U 1 1 5C3E68EC
P 5500 2300
F 0 "SW3" H 5500 2625 50  0000 C CNN
F 1 "Spannungswandler" H 5500 2534 50  0000 C CNN
F 2 "" H 5500 2300 50  0001 C CNN
F 3 "" H 5500 2300 50  0001 C CNN
	1    5500 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 1300 4900 1300
Connection ~ 4900 1300
Wire Wire Line
	4900 1300 4900 1550
Wire Wire Line
	5200 1500 4700 1500
Connection ~ 4700 1500
Wire Wire Line
	4700 1500 4700 1600
Wire Wire Line
	5200 2200 4900 2200
Connection ~ 4900 2200
Wire Wire Line
	4900 2200 4900 2450
Wire Wire Line
	5200 2400 4700 2400
Connection ~ 4700 2400
Wire Wire Line
	4700 2400 4700 2500
NoConn ~ 4800 1500
NoConn ~ 4900 1500
NoConn ~ 4900 2400
NoConn ~ 4800 2400
Text Label 6300 1300 0    50   ~ 0
RaspberryPi+
Text Label 6300 1500 0    50   ~ 0
RaspberryPi-
Wire Wire Line
	5800 1300 6300 1300
Wire Wire Line
	5800 1500 6300 1500
Text Label 6000 1500 0    50   ~ 0
GND
Text Label 6000 1300 0    50   ~ 0
+5.25V
Text Label 6300 2200 0    50   ~ 0
Bildschirm+
Text Label 6300 2400 0    50   ~ 0
Bildschirm-
Text Label 6000 2200 0    50   ~ 0
+12V
Text Label 6000 2400 0    50   ~ 0
GND
Wire Wire Line
	5800 2200 6300 2200
Wire Wire Line
	5800 2400 6300 2400
$Comp
L mylib:Spannungswandler SW1
U 1 1 5C3F3353
P 4200 3550
F 0 "SW1" H 4200 3875 50  0000 C CNN
F 1 "Spannungswandler" H 4200 3784 50  0000 C CNN
F 2 "" H 4200 3550 50  0001 C CNN
F 3 "" H 4200 3550 50  0001 C CNN
	1    4200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3650 3900 3700
Wire Wire Line
	3900 3700 3200 3700
Wire Wire Line
	3200 3400 3900 3400
Wire Wire Line
	3900 3400 3900 3450
Wire Wire Line
	4500 3450 4800 3450
Wire Wire Line
	4800 3450 4800 3050
Connection ~ 4800 3050
Wire Wire Line
	4500 3650 4700 3650
Wire Wire Line
	4700 3650 4700 2950
Connection ~ 4700 2950
NoConn ~ 4700 3050
$EndSCHEMATC
