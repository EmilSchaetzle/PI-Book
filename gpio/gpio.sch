EESchema Schematic File Version 4
LIBS:gpio-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "PI-Book GPIO"
Date "2019-01-22"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J?
U 1 1 5C36C585
P 3450 2950
F 0 "J?" V 3454 3430 50  0001 L CNN
F 1 "PI-Book GPIO" V 3500 2362 50  0000 R CNN
F 2 "" H 3450 2950 50  0001 C CNN
F 3 "~" H 3450 2950 50  0001 C CNN
	1    3450 2950
	0    -1   -1   0   
$EndComp
Text Label 3050 3150 3    50   ~ 0
5V
Text Label 3150 3150 3    50   ~ 0
3.3V
Text Label 3050 2650 1    50   ~ 0
GND
Text Label 3150 2650 1    50   ~ 0
GND
$Comp
L Logic_LevelTranslator:TXB0104D U?
U 1 1 5C36C79F
P 2250 2750
F 0 "U?" H 2250 1964 50  0001 C CNN
F 1 "Voltage level shifter" H 2250 1873 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2250 2000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/txb0104.pdf" H 2360 2845 50  0001 C CNN
	1    2250 2750
	1    0    0    -1  
$EndComp
Text Label 2350 2050 1    50   ~ 0
3.3V
Text Label 2150 2050 1    50   ~ 0
5V
Text Label 1850 2250 1    50   ~ 0
GND
Text Label 1850 2450 2    50   ~ 0
TX_5
Text Label 1850 2650 2    50   ~ 0
RX_5
Text Label 3250 2650 1    50   ~ 0
TX_5
Text Label 3350 2650 1    50   ~ 0
RX_5
Text Label 3450 2650 1    50   ~ 0
SDA_5
Text Label 3550 2650 1    50   ~ 0
SCL_5
Text Label 3650 2650 1    50   ~ 0
MOSI
Text Label 3650 3150 3    50   ~ 0
MISO
Text Label 3750 3150 3    50   ~ 0
SCLK
Text Label 3250 3150 3    50   ~ 0
TX
Text Label 3350 3150 3    50   ~ 0
RX
Text Label 3450 3150 3    50   ~ 0
SDA
Text Label 3550 3150 3    50   ~ 0
SCL
Text Label 2650 2450 0    50   ~ 0
TX
Text Label 2650 2650 0    50   ~ 0
RX
Text Label 3750 2650 1    50   ~ 0
CE0
Text Label 3850 2650 1    50   ~ 0
CE1
Text Label 3850 3150 3    50   ~ 0
BCM12
Text Label 3950 3150 3    50   ~ 0
BCM13
Text Label 3950 2650 1    50   ~ 0
BCM18
Text Label 2650 2850 0    50   ~ 0
SDA
Text Label 2650 3050 0    50   ~ 0
SCL
Text Label 1850 2850 2    50   ~ 0
SDA_5
Text Label 1850 3050 2    50   ~ 0
SCL_5
$EndSCHEMATC
