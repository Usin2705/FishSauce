EESchema Schematic File Version 4
LIBS:IoTProject-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "FishSauce IoT Project's Main Board"
Date "01-Dec-2018"
Rev "1"
Comp "Metropolia UAS"
Comment1 ""
Comment2 ""
Comment3 "LPCXpresso board, drivers, etc."
Comment4 "This central board contains mostly headers to connect motors,"
$EndDescr
$Comp
L Connector:Conn_01x06_Female J1
U 1 1 5BF2A4B1
P 1350 1950
F 0 "J1" H 1377 1926 50  0000 L TNN
F 1 "north motor" V 1377 1835 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1350 1950 50  0001 C CNN
F 3 "~" H 1350 1950 50  0001 C CNN
	1    1350 1950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Female J2
U 1 1 5BF2A505
P 2500 1950
F 0 "J2" H 2527 1926 50  0000 L TNN
F 1 "south motor" V 2527 1835 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2500 1950 50  0001 C CNN
F 3 "~" H 2500 1950 50  0001 C CNN
	1    2500 1950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Female J3
U 1 1 5BF2A589
P 3700 1950
F 0 "J3" H 3727 1926 50  0000 L TNN
F 1 "east motor" V 3727 1835 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3700 1950 50  0001 C CNN
F 3 "~" H 3700 1950 50  0001 C CNN
	1    3700 1950
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Female J4
U 1 1 5BF2A5FD
P 4900 1950
F 0 "J4" H 4928 1926 50  0000 L TNN
F 1 "west motor" V 4928 1835 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 4900 1950 50  0001 C CNN
F 3 "~" H 4900 1950 50  0001 C CNN
	1    4900 1950
	-1   0    0    1   
$EndComp
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 5BF2AF7E
P 2800 4350
F 0 "A1" H 2800 5528 50  0000 C CNN
F 1 "LPCXpresso1549" H 2650 5450 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 2950 3300 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 2600 5400 50  0001 C CNN
	1    2800 4350
	1    0    0    -1  
$EndComp
$Comp
L l298module:L298module U2
U 1 1 5BF2F35F
P 7800 3000
F 0 "U2" H 8200 3115 50  0000 C CNN
F 1 "L298module" H 8200 3024 50  0000 C CNN
F 2 "customm:l298module" H 8400 3050 50  0001 C CNN
F 3 "" H 8400 3050 50  0001 C CNN
	1    7800 3000
	1    0    0    -1  
$EndComp
Text GLabel 5350 3350 0    50   Input ~ 0
5VU1
Text GLabel 7600 3350 0    50   Input ~ 0
5VU2
$Comp
L power:Earth #PWR0101
U 1 1 5C0131CB
P 5450 3250
F 0 "#PWR0101" H 5450 3000 50  0001 C CNN
F 1 "Earth" H 5450 3100 50  0001 C CNN
F 2 "" H 5450 3250 50  0001 C CNN
F 3 "~" H 5450 3250 50  0001 C CNN
	1    5450 3250
	0    1    1    0   
$EndComp
$Comp
L power:Earth #PWR0102
U 1 1 5C0135B4
P 7700 3250
F 0 "#PWR0102" H 7700 3000 50  0001 C CNN
F 1 "Earth" H 7700 3100 50  0001 C CNN
F 2 "" H 7700 3250 50  0001 C CNN
F 3 "~" H 7700 3250 50  0001 C CNN
	1    7700 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 3250 7700 3250
Wire Wire Line
	7600 3350 7800 3350
Wire Wire Line
	5550 3250 5450 3250
Wire Wire Line
	5350 3350 5550 3350
$Comp
L power:Earth #PWR0103
U 1 1 5C013BE8
P 1600 1850
F 0 "#PWR0103" H 1600 1600 50  0001 C CNN
F 1 "Earth" H 1600 1700 50  0001 C CNN
F 2 "" H 1600 1850 50  0001 C CNN
F 3 "~" H 1600 1850 50  0001 C CNN
	1    1600 1850
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR0104
U 1 1 5C013C01
P 2750 1850
F 0 "#PWR0104" H 2750 1600 50  0001 C CNN
F 1 "Earth" H 2750 1700 50  0001 C CNN
F 2 "" H 2750 1850 50  0001 C CNN
F 3 "~" H 2750 1850 50  0001 C CNN
	1    2750 1850
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR0105
U 1 1 5C013CBB
P 3950 1850
F 0 "#PWR0105" H 3950 1600 50  0001 C CNN
F 1 "Earth" H 3950 1700 50  0001 C CNN
F 2 "" H 3950 1850 50  0001 C CNN
F 3 "~" H 3950 1850 50  0001 C CNN
	1    3950 1850
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR0106
U 1 1 5C013DA6
P 5150 1850
F 0 "#PWR0106" H 5150 1600 50  0001 C CNN
F 1 "Earth" H 5150 1700 50  0001 C CNN
F 2 "" H 5150 1850 50  0001 C CNN
F 3 "~" H 5150 1850 50  0001 C CNN
	1    5150 1850
	0    -1   -1   0   
$EndComp
Text GLabel 1750 1950 2    50   Input ~ 0
5VU1
Wire Wire Line
	1750 1950 1550 1950
Wire Wire Line
	1600 1850 1550 1850
Text GLabel 2900 1950 2    50   Input ~ 0
5VU1
Wire Wire Line
	2750 1850 2700 1850
Text GLabel 4100 1950 2    50   Input ~ 0
5VU2
Wire Wire Line
	3950 1850 3900 1850
Text GLabel 5300 1950 2    50   Input ~ 0
5VU2
Wire Wire Line
	5150 1850 5100 1850
Wire Wire Line
	5100 1950 5300 1950
Wire Wire Line
	3900 1950 4100 1950
Wire Wire Line
	2700 1950 2900 1950
Wire Wire Line
	6550 3450 6350 3450
Wire Wire Line
	6350 3550 6550 3550
Wire Wire Line
	5550 3450 5350 3450
Wire Wire Line
	5350 3550 5550 3550
Wire Wire Line
	7600 3450 7800 3450
Wire Wire Line
	7800 3550 7600 3550
Wire Wire Line
	8600 3450 8800 3450
Wire Wire Line
	8800 3550 8600 3550
Wire Wire Line
	2100 3750 2300 3750
Wire Wire Line
	2300 3850 2100 3850
Wire Wire Line
	2100 3950 2300 3950
Wire Wire Line
	2300 4050 2100 4050
Wire Wire Line
	3300 4550 3500 4550
Wire Wire Line
	3500 4650 3300 4650
Wire Wire Line
	3300 4750 3500 4750
Wire Wire Line
	3500 4850 3300 4850
$Comp
L power:Earth #PWR0107
U 1 1 5C024625
P 2800 5550
F 0 "#PWR0107" H 2800 5300 50  0001 C CNN
F 1 "Earth" H 2800 5400 50  0001 C CNN
F 2 "" H 2800 5550 50  0001 C CNN
F 3 "~" H 2800 5550 50  0001 C CNN
	1    2800 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5450 2700 5500
Wire Wire Line
	2700 5500 2800 5500
Wire Wire Line
	2900 5500 2900 5450
Wire Wire Line
	2800 5450 2800 5500
Connection ~ 2800 5500
Wire Wire Line
	2800 5500 2900 5500
Wire Wire Line
	2800 5550 2800 5500
Wire Wire Line
	1550 1750 1650 1750
Wire Wire Line
	2700 1750 2800 1750
Wire Wire Line
	3900 1750 4000 1750
Wire Wire Line
	5100 1750 5200 1750
Text GLabel 3450 3000 1    50   Input ~ 0
5VU2
NoConn ~ 1550 1650
NoConn ~ 2700 1650
NoConn ~ 3900 1650
NoConn ~ 5100 1650
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 5C033DA0
P 5200 5250
F 0 "J5" H 5280 5242 50  0000 L CNN
F 1 "Input from battery" H 5200 5400 50  0000 C TNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 5200 5250 50  0001 C CNN
F 3 "~" H 5200 5250 50  0001 C CNN
	1    5200 5250
	-1   0    0    1   
$EndComp
$Comp
L power:Earth #PWR0108
U 1 1 5C033F32
P 6400 5600
F 0 "#PWR0108" H 6400 5350 50  0001 C CNN
F 1 "Earth" H 6400 5450 50  0001 C CNN
F 2 "" H 6400 5600 50  0001 C CNN
F 3 "~" H 6400 5600 50  0001 C CNN
	1    6400 5600
	1    0    0    -1  
$EndComp
Text GLabel 5600 4950 1    50   Input ~ 0
12V
NoConn ~ 2700 3350
NoConn ~ 2900 3350
Text GLabel 5350 3150 0    50   Input ~ 0
12V
Text GLabel 7600 3150 0    50   Input ~ 0
12V
Wire Wire Line
	7600 3150 7800 3150
Wire Wire Line
	5350 3150 5550 3150
$Comp
L l298module:L298module U1
U 1 1 5BF2F0C0
P 5550 3000
F 0 "U1" H 5950 3115 50  0000 C CNN
F 1 "L298module" H 5950 3024 50  0000 C CNN
F 2 "customm:l298module" H 6150 3050 50  0001 C CNN
F 3 "" H 6150 3050 50  0001 C CNN
	1    5550 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2050 5100 2050
Wire Wire Line
	5100 2150 5200 2150
Wire Wire Line
	3900 2050 4000 2050
Wire Wire Line
	4000 2150 3900 2150
Wire Wire Line
	2800 2050 2700 2050
Wire Wire Line
	2700 2150 2800 2150
Wire Wire Line
	1650 2050 1550 2050
Wire Wire Line
	1550 2150 1650 2150
Wire Wire Line
	6350 3250 6550 3250
Wire Wire Line
	6550 3350 6350 3350
Wire Wire Line
	6000 3800 6000 3950
Wire Wire Line
	5850 3800 5850 3950
Wire Wire Line
	8600 3250 8800 3250
Wire Wire Line
	8800 3350 8600 3350
Wire Wire Line
	8100 3800 8100 3950
Wire Wire Line
	8250 3800 8250 3950
$Comp
L Connector:Conn_01x05_Female J15
U 1 1 5C220F2E
P 9300 4850
F 0 "J15" H 9328 4876 50  0000 L CNN
F 1 "HC12 module" H 9328 4785 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 9300 4850 50  0001 C CNN
F 3 "~" H 9300 4850 50  0001 C CNN
	1    9300 4850
	1    0    0    -1  
$EndComp
Text GLabel 8900 4650 0    50   Input ~ 0
5VU1
$Comp
L power:Earth #PWR0109
U 1 1 5C22112E
P 8900 4750
F 0 "#PWR0109" H 8900 4500 50  0001 C CNN
F 1 "Earth" H 8900 4600 50  0001 C CNN
F 2 "" H 8900 4750 50  0001 C CNN
F 3 "~" H 8900 4750 50  0001 C CNN
	1    8900 4750
	0    1    1    0   
$EndComp
NoConn ~ 9100 5050
Wire Wire Line
	8900 4650 9100 4650
Wire Wire Line
	9100 4750 8900 4750
Wire Wire Line
	8900 4850 9100 4850
Wire Wire Line
	9100 4950 8900 4950
Wire Wire Line
	2300 4150 2100 4150
Text Notes 1250 5600 0    50   ~ 0
note: D6 is LPC's RX -> RPi's TX\nnote: D4 is LPC's TX -> RPi's RX
$Comp
L Connector:Conn_01x04_Male J8
U 1 1 5C22E253
P 8150 1650
F 0 "J8" H 8256 1928 50  0000 C CNN
F 1 "ultrasonic front" H 8256 1837 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8150 1650 50  0001 C CNN
F 3 "~" H 8150 1650 50  0001 C CNN
	1    8150 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J11
U 1 1 5C22E2E8
P 9450 1650
F 0 "J11" H 9556 1928 50  0000 C CNN
F 1 "ultrasonic rear" H 9556 1837 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9450 1650 50  0001 C CNN
F 3 "~" H 9450 1650 50  0001 C CNN
	1    9450 1650
	1    0    0    -1  
$EndComp
Text GLabel 8550 1550 2    50   Input ~ 0
5VU2
Text GLabel 9900 1550 2    50   Input ~ 0
5VU2
$Comp
L power:Earth #PWR0110
U 1 1 5C22E475
P 8550 1850
F 0 "#PWR0110" H 8550 1600 50  0001 C CNN
F 1 "Earth" H 8550 1700 50  0001 C CNN
F 2 "" H 8550 1850 50  0001 C CNN
F 3 "~" H 8550 1850 50  0001 C CNN
	1    8550 1850
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR0111
U 1 1 5C22E4D7
P 9900 1850
F 0 "#PWR0111" H 9900 1600 50  0001 C CNN
F 1 "Earth" H 9900 1700 50  0001 C CNN
F 2 "" H 9900 1850 50  0001 C CNN
F 3 "~" H 9900 1850 50  0001 C CNN
	1    9900 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8550 1550 8350 1550
Wire Wire Line
	8350 1650 8550 1650
Wire Wire Line
	9650 1550 9900 1550
Wire Wire Line
	9900 1650 9650 1650
Wire Wire Line
	8550 1850 8350 1850
Wire Wire Line
	9900 1850 9650 1850
Wire Wire Line
	9900 1750 9650 1750
Wire Wire Line
	8550 1750 8350 1750
$Comp
L Connector:Conn_01x03_Male J6
U 1 1 5C246A4D
P 6200 1550
F 0 "J6" H 6306 1828 50  0000 C CNN
F 1 "servo_updown" H 6306 1737 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6200 1550 50  0001 C CNN
F 3 "~" H 6200 1550 50  0001 C CNN
	1    6200 1550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 5C246B17
P 6200 2050
F 0 "J7" H 6306 2328 50  0000 C CNN
F 1 "servo_leftright" H 6306 2237 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6200 2050 50  0001 C CNN
F 3 "~" H 6200 2050 50  0001 C CNN
	1    6200 2050
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0112
U 1 1 5C246BE3
P 6650 1450
F 0 "#PWR0112" H 6650 1200 50  0001 C CNN
F 1 "Earth" H 6650 1300 50  0001 C CNN
F 2 "" H 6650 1450 50  0001 C CNN
F 3 "~" H 6650 1450 50  0001 C CNN
	1    6650 1450
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR0113
U 1 1 5C246C08
P 6650 1950
F 0 "#PWR0113" H 6650 1700 50  0001 C CNN
F 1 "Earth" H 6650 1800 50  0001 C CNN
F 2 "" H 6650 1950 50  0001 C CNN
F 3 "~" H 6650 1950 50  0001 C CNN
	1    6650 1950
	0    -1   -1   0   
$EndComp
$Comp
L Regulator_Linear:L7805 U3
U 1 1 5C247845
P 6400 5150
F 0 "U3" H 6400 5392 50  0000 C CNN
F 1 "L7805" H 6400 5301 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6425 5000 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 6400 5100 50  0001 C CNN
	1    6400 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 5250 5600 5250
Wire Wire Line
	5600 5250 5600 5500
Wire Wire Line
	6400 5500 6400 5450
Wire Wire Line
	5600 4950 5600 5150
Connection ~ 5600 5150
Wire Wire Line
	5600 5150 5400 5150
$Comp
L Device:C_Small C1
U 1 1 5C266D79
P 5900 5300
F 0 "C1" H 5992 5346 50  0000 L CNN
F 1 "0.33uF" H 5992 5255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 5900 5300 50  0001 C CNN
F 3 "~" H 5900 5300 50  0001 C CNN
	1    5900 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 5150 5900 5150
Wire Wire Line
	5600 5500 5900 5500
Wire Wire Line
	5900 5400 5900 5500
Connection ~ 5900 5500
Wire Wire Line
	5900 5500 6400 5500
Wire Wire Line
	5900 5200 5900 5150
Connection ~ 5900 5150
Wire Wire Line
	5900 5150 6100 5150
$Comp
L Device:C_Small C2
U 1 1 5C278556
P 7000 5300
F 0 "C2" H 7092 5346 50  0000 L CNN
F 1 "104 ceramic cap" H 7092 5255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P1.50mm" H 7000 5300 50  0001 C CNN
F 3 "~" H 7000 5300 50  0001 C CNN
	1    7000 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 5150 7000 5150
Wire Wire Line
	7000 5150 7000 5200
Wire Wire Line
	7000 5400 7000 5500
Text GLabel 7000 4950 1    50   Input ~ 0
5VU3
Wire Wire Line
	7000 4950 7000 5150
Connection ~ 7000 5150
$Comp
L Device:LED D1
U 1 1 5C283D02
P 7450 5150
F 0 "D1" H 7442 4895 50  0000 C CNN
F 1 "5VU3 LED" H 7442 4986 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 7450 5150 50  0001 C CNN
F 3 "~" H 7450 5150 50  0001 C CNN
	1    7450 5150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5C283DDE
P 7900 5350
F 0 "R1" H 7970 5396 50  0000 L CNN
F 1 "1k" H 7970 5305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7830 5350 50  0001 C CNN
F 3 "~" H 7900 5350 50  0001 C CNN
	1    7900 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 5150 7300 5150
Wire Wire Line
	7900 5150 7900 5200
Wire Wire Line
	7900 5500 7000 5500
Wire Wire Line
	7000 5500 6400 5500
Connection ~ 7000 5500
Connection ~ 6400 5500
Wire Wire Line
	6400 5600 6400 5500
Text GLabel 6650 1550 2    50   Input ~ 0
5VU3
Text GLabel 6650 2050 2    50   Input ~ 0
5VU3
Wire Wire Line
	6650 2150 6400 2150
Wire Wire Line
	6400 2050 6650 2050
Wire Wire Line
	6650 1950 6400 1950
Wire Wire Line
	6400 1650 6650 1650
Wire Wire Line
	6650 1550 6400 1550
Wire Wire Line
	6400 1450 6650 1450
Wire Wire Line
	7600 5150 7900 5150
Wire Wire Line
	3500 4350 3300 4350
Wire Wire Line
	2100 4350 2300 4350
$Comp
L Connector:Conn_01x02_Male J12
U 1 1 5C2DDAEF
P 8850 5600
F 0 "J12" H 8956 5778 50  0000 C CNN
F 1 "Pi's UART" H 8956 5687 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8850 5600 50  0001 C CNN
F 3 "~" H 8850 5600 50  0001 C CNN
	1    8850 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 5600 9200 5600
Wire Wire Line
	9200 5700 9050 5700
Wire Wire Line
	2100 5050 2300 5050
Wire Wire Line
	2300 4850 2100 4850
$Comp
L Connector:Conn_01x01_Female J16
U 1 1 5C30958D
P 9300 5200
F 0 "J16" H 9327 5226 50  0000 L CNN
F 1 "P1_1 LPC's TX" H 9327 5135 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 9300 5200 50  0001 C CNN
F 3 "~" H 9300 5200 50  0001 C CNN
	1    9300 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 5200 9100 5200
$Comp
L Connector:Conn_01x01_Female J9
U 1 1 5C311D92
P 8550 2100
F 0 "J9" H 8578 2126 50  0000 L CNN
F 1 "P1_4 trig front" H 8650 2100 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8550 2100 50  0001 C CNN
F 3 "~" H 8550 2100 50  0001 C CNN
	1    8550 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J10
U 1 1 5C311DE2
P 8550 2250
F 0 "J10" H 8577 2276 50  0000 L CNN
F 1 "P1_6 echo front" H 8650 2250 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 8550 2250 50  0001 C CNN
F 3 "~" H 8550 2250 50  0001 C CNN
	1    8550 2250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J13
U 1 1 5C311E20
P 9950 2100
F 0 "J13" H 9977 2126 50  0000 L CNN
F 1 "P1_5 trig rear" H 10050 2100 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 9950 2100 50  0001 C CNN
F 3 "~" H 9950 2100 50  0001 C CNN
	1    9950 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J14
U 1 1 5C311E7C
P 9950 2250
F 0 "J14" H 9977 2276 50  0000 L CNN
F 1 "P1_7 echo rear" H 10050 2250 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 9950 2250 50  0001 C CNN
F 3 "~" H 9950 2250 50  0001 C CNN
	1    9950 2250
	1    0    0    -1  
$EndComp
Wire Notes Line
	8250 5800 4700 5800
Wire Notes Line
	4700 5800 4700 4500
Wire Notes Line
	4700 4500 8250 4500
Wire Notes Line
	8250 4500 8250 5800
Text Notes 6000 4650 0    59   Italic 12
SERVO POWER SUPPLY
Wire Notes Line
	9400 4150 4700 4150
Wire Notes Line
	4700 4150 4700 2600
Wire Notes Line
	4700 2600 9400 2600
Wire Notes Line
	9400 2600 9400 4150
Text Notes 6700 2800 0    59   Italic 12
L298 MODULES
Wire Notes Line
	7500 1150 1100 1150
Text Notes 3350 1400 0    59   Italic 12
DC AND RC SERVO MOTORS
Wire Notes Line
	7500 1150 7500 2350
Wire Notes Line
	1100 1150 1100 2350
Wire Notes Line
	1100 2350 7500 2350
Wire Notes Line
	10750 2400 7800 2400
Wire Notes Line
	7800 1150 10750 1150
Wire Notes Line
	10750 1150 10750 2400
Wire Notes Line
	7800 1150 7800 2400
Text Notes 8750 1300 0    59   Italic 12
ULTRASONIC SENSORS
Text Notes 9150 4550 0    59   Italic 12
UARTS
Wire Notes Line
	1100 2600 1100 5800
Text Notes 1800 2900 0    59   Italic 12
LPC XPRESSO1549
Wire Notes Line
	10000 5800 8550 5800
Wire Notes Line
	8550 4350 10000 4350
Wire Notes Line
	10000 4350 10000 5800
Wire Notes Line
	8550 4350 8550 5800
NoConn ~ 3300 4150
NoConn ~ 3300 3950
Wire Wire Line
	1400 4250 2300 4250
Wire Wire Line
	3500 4450 3300 4450
Wire Wire Line
	1600 4350 1400 4350
$Comp
L power:Earth #PWR01
U 1 1 5C29F29A
P 4100 4350
F 0 "#PWR01" H 4100 4100 50  0001 C CNN
F 1 "Earth" H 4100 4200 50  0001 C CNN
F 2 "" H 4100 4350 50  0001 C CNN
F 3 "~" H 4100 4350 50  0001 C CNN
	1    4100 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5C2B0144
P 3450 3250
F 0 "D2" V 3450 3100 50  0000 C CNN
F 1 "reset LED" V 3550 3000 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 3450 3250 50  0001 C CNN
F 3 "~" H 3450 3250 50  0001 C CNN
	1    3450 3250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5C2B043E
P 3450 3600
F 0 "R2" H 3520 3646 50  0000 L CNN
F 1 "2.2k" H 3520 3555 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3380 3600 50  0001 C CNN
F 3 "~" H 3450 3600 50  0001 C CNN
	1    3450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3400 3450 3450
$Comp
L Device:R R3
U 1 1 5C2D9D4E
P 3750 3750
F 0 "R3" H 3820 3796 50  0000 L CNN
F 1 "100R" H 3820 3705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3680 3750 50  0001 C CNN
F 3 "~" H 3750 3750 50  0001 C CNN
	1    3750 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 3750 3450 3750
Wire Wire Line
	4100 4300 4100 4350
Wire Notes Line
	4450 2600 4450 5800
Wire Notes Line
	1100 5800 4450 5800
Wire Notes Line
	1100 2600 4450 2600
Text GLabel 8550 1650 2    50   Input ~ 0
trig_front
Text GLabel 8350 2100 0    50   Input ~ 0
trig_front
Text GLabel 8550 1750 2    50   Input ~ 0
echo_front
Text GLabel 8350 2250 0    50   Input ~ 0
echo_front
Text GLabel 9900 1650 2    50   Input ~ 0
trig_rear
Text GLabel 9900 1750 2    50   Input ~ 0
echo_rear
Text GLabel 9750 2100 0    50   Input ~ 0
trig_rear
Text GLabel 9750 2250 0    50   Input ~ 0
echo_rear
Text GLabel 6650 1650 2    50   Input ~ 0
servo_updown
Text GLabel 6650 2150 2    50   Input ~ 0
servo_leftright
Text GLabel 5200 1750 2    50   Input ~ 0
westP0_22
Text GLabel 5200 2050 2    50   Input ~ 0
west_out1
Text GLabel 5200 2150 2    50   Input ~ 0
west_out2
Text GLabel 4000 1750 2    50   Input ~ 0
eastP1_0
Text GLabel 4000 2050 2    50   Input ~ 0
east_out1
Text GLabel 4000 2150 2    50   Input ~ 0
east_out2
Text GLabel 2800 1750 2    50   Input ~ 0
southP0_23
Text GLabel 2800 2050 2    50   Input ~ 0
south_out1
Text GLabel 2800 2150 2    50   Input ~ 0
south_out2
Text GLabel 1650 1750 2    50   Input ~ 0
northP0_0
Text GLabel 1650 2050 2    50   Input ~ 0
north_out1
Text GLabel 1650 2150 2    50   Input ~ 0
north_out2
Text GLabel 2100 3750 0    50   Input ~ 0
northP1_10
Text GLabel 2100 3850 0    50   Input ~ 0
northP1_9
Text GLabel 2100 3950 0    50   Input ~ 0
southP0_29
Text GLabel 2100 4050 0    50   Input ~ 0
southP0_9
Text GLabel 2100 4150 0    50   Input ~ 0
RX_Pi
Text GLabel 2100 4350 0    50   Input ~ 0
TX_Pi
Text GLabel 1600 4350 2    50   Input ~ 0
A1
Text GLabel 2100 4850 0    50   Input ~ 0
servo_leftright
Text GLabel 2100 5050 0    50   Input ~ 0
servo_updown
Text GLabel 3500 4350 2    50   Input ~ 0
TX
Text GLabel 3500 4450 2    50   Input ~ 0
A1
Text GLabel 3500 4550 2    50   Input ~ 0
westP1_8
Text GLabel 3500 4650 2    50   Input ~ 0
westP0_5
Text GLabel 3500 4750 2    50   Input ~ 0
eastP0_6
Text GLabel 3500 4850 2    50   Input ~ 0
eastP0_7
Text GLabel 5350 3450 0    50   Input ~ 0
northP1_10
Text GLabel 5350 3550 0    50   Input ~ 0
northP1_9
Text GLabel 6550 3250 2    50   Input ~ 0
north_out2
Text GLabel 6550 3350 2    50   Input ~ 0
north_out1
Text GLabel 6550 3450 2    50   Input ~ 0
southP0_9
Text GLabel 6550 3550 2    50   Input ~ 0
southP0_29
Text GLabel 6000 3950 2    50   Input ~ 0
south_out2
Text GLabel 5850 3950 0    50   Input ~ 0
south_out1
Text GLabel 7600 3450 0    50   Input ~ 0
eastP0_7
Text GLabel 7600 3550 0    50   Input ~ 0
eastP0_6
Text GLabel 8100 3950 0    50   Input ~ 0
west_out1
Text GLabel 8250 3950 2    50   Input ~ 0
west_out2
Text GLabel 8800 3250 2    50   Input ~ 0
east_out2
Text GLabel 8800 3350 2    50   Input ~ 0
east_out1
Text GLabel 8800 3450 2    50   Input ~ 0
westP1_8
Text GLabel 8800 3550 2    50   Input ~ 0
westP0_5
Text GLabel 8900 4850 0    50   Input ~ 0
RX
Text GLabel 8900 4950 0    50   Input ~ 0
TX
Text GLabel 8900 5200 0    50   Input ~ 0
RX
Text GLabel 9200 5600 2    50   Input ~ 0
RX_Pi
Text GLabel 9200 5700 2    50   Input ~ 0
TX_Pi
Text GLabel 2100 4450 0    50   Input ~ 0
northP0_0
Wire Wire Line
	2100 4450 2300 4450
Wire Wire Line
	2300 4950 1400 4950
Text GLabel 3500 5050 2    50   Input ~ 0
southP0_23
Wire Wire Line
	3500 5050 3300 5050
Text GLabel 3500 5150 2    50   Input ~ 0
westP0_22
Wire Wire Line
	3500 5150 3300 5150
$Comp
L Connector:Conn_01x01_Male J18
U 1 1 5C36C322
P 3550 5450
F 0 "J18" H 3656 5628 50  0000 C CNN
F 1 "extenfer for P1_0" H 3656 5537 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3550 5450 50  0001 C CNN
F 3 "~" H 3550 5450 50  0001 C CNN
	1    3550 5450
	1    0    0    -1  
$EndComp
Text GLabel 3900 5450 2    50   Input ~ 0
eastP1_0
Wire Wire Line
	3900 5450 3750 5450
$Comp
L Connector:Conn_01x06_Male J17
U 1 1 5C37E072
P 1200 4450
F 0 "J17" H 1306 4828 50  0000 C CNN
F 1 "extender" H 1306 4737 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 1200 4450 50  0001 C CNN
F 3 "~" H 1200 4450 50  0001 C CNN
	1    1200 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4450 1600 4450
Wire Wire Line
	1600 4450 1600 4550
Wire Wire Line
	1600 4550 2300 4550
Wire Wire Line
	1400 4550 1550 4550
Wire Wire Line
	1550 4550 1550 4650
Wire Wire Line
	1550 4650 2300 4650
Wire Wire Line
	1400 4650 1500 4650
Wire Wire Line
	1500 4650 1500 4750
Wire Wire Line
	1500 4750 2300 4750
Wire Wire Line
	1400 4750 1400 4950
NoConn ~ 3000 3350
Wire Wire Line
	3450 3000 3450 3100
Wire Wire Line
	4100 3900 4100 3750
Wire Wire Line
	3300 3750 3450 3750
Connection ~ 3450 3750
$Comp
L Switch:SW_Push SW1
U 1 1 5C3E7515
P 4100 4100
F 0 "SW1" V 4054 4248 50  0000 L CNN
F 1 "SW_Push" V 4145 4248 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4100 4300 50  0001 C CNN
F 3 "" H 4100 4300 50  0001 C CNN
	1    4100 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	3900 3750 4100 3750
$EndSCHEMATC
