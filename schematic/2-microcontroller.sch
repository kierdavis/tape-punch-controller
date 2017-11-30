v 20130925 2
C 43600 40400 1 0 0 gnd-1.sym
N 43700 40700 43700 40900 4
N 43700 40800 45200 40800 4
N 44000 40800 44000 40900 4
N 44300 40900 44300 40800 4
N 44600 40900 44600 40800 4
N 44900 40900 44900 40800 4
N 45200 40900 45200 40800 4
N 43700 51000 43700 51100 4
N 44000 51000 44000 51100 4
N 44300 51000 44300 51100 4
N 44600 51000 44600 51100 4
N 44900 51000 44900 51100 4
N 45200 51000 45200 51100 4
C 48500 49500 1 90 0 capacitor-1.sym
{
T 48000 49700 5 10 1 1 90 0 1
refdes=C3
T 47600 49700 5 10 0 0 90 0 1
symversion=0.1
T 48000 50100 5 10 1 1 90 0 1
value=100n
T 48500 49500 5 10 0 0 0 0 1
footprint=0805
T 48500 49500 5 10 0 0 0 0 1
x-dielectric=X7R
T 48500 49500 5 10 0 0 0 0 1
x-min-voltage-rating=5
}
C 49300 49500 1 90 0 capacitor-1.sym
{
T 48800 49700 5 10 1 1 90 0 1
refdes=C4
T 48400 49700 5 10 0 0 90 0 1
symversion=0.1
T 48800 50100 5 10 1 1 90 0 1
value=100n
T 49300 49500 5 10 0 0 0 0 1
footprint=0805
T 49300 49500 5 10 0 0 0 0 1
x-dielectric=X7R
T 49300 49500 5 10 0 0 0 0 1
x-min-voltage-rating=5
}
C 50100 49500 1 90 0 capacitor-1.sym
{
T 49200 49700 5 10 0 0 90 0 1
symversion=0.1
T 49600 49700 5 10 1 1 90 0 1
refdes=C5
T 49600 50100 5 10 1 1 90 0 1
value=100n
T 50100 49500 5 10 0 0 0 0 1
footprint=0805
T 50100 49500 5 10 0 0 0 0 1
x-dielectric=X7R
T 50100 49500 5 10 0 0 0 0 1
x-min-voltage-rating=5
}
C 50900 49500 1 90 0 capacitor-1.sym
{
T 50000 49700 5 10 0 0 90 0 1
symversion=0.1
T 50400 49700 5 10 1 1 90 0 1
refdes=C6
T 50400 50100 5 10 1 1 90 0 1
value=100n
T 50900 49500 5 10 0 0 0 0 1
footprint=0805
T 50900 49500 5 10 0 0 0 0 1
x-dielectric=X7R
T 50900 49500 5 10 0 0 0 0 1
x-min-voltage-rating=5
}
C 51700 49500 1 90 0 capacitor-1.sym
{
T 50800 49700 5 10 0 0 90 0 1
symversion=0.1
T 51200 49700 5 10 1 1 90 0 1
refdes=C7
T 51200 50100 5 10 1 1 90 0 1
value=100n
T 51700 49500 5 10 0 0 0 0 1
footprint=0805
T 51700 49500 5 10 0 0 0 0 1
x-dielectric=X7R
T 51700 49500 5 10 0 0 0 0 1
x-min-voltage-rating=5
}
C 52500 49500 1 90 0 capacitor-1.sym
{
T 51600 49700 5 10 0 0 90 0 1
symversion=0.1
T 52000 49700 5 10 1 1 90 0 1
refdes=C8
T 52000 50100 5 10 1 1 90 0 1
value=100n
T 52500 49500 5 10 0 0 0 0 1
footprint=0805
T 52500 49500 5 10 0 0 0 0 1
x-dielectric=X7R
T 52500 49500 5 10 0 0 0 0 1
x-min-voltage-rating=5
}
N 48300 50400 48300 51100 4
N 49100 50400 49100 50700 4
N 49900 50400 49900 50700 4
N 50700 50400 50700 50700 4
N 51500 50400 51500 50700 4
N 52300 50400 52300 50800 4
N 48300 49500 48300 49200 4
N 48300 49200 52300 49200 4
N 49100 49200 49100 49500 4
N 49900 49200 49900 49500 4
N 50700 49200 50700 49500 4
N 51500 49200 51500 49500 4
N 52300 49200 52300 49500 4
C 50200 48800 1 0 0 gnd-1.sym
N 50300 49100 50300 49200 4
C 52100 50800 1 0 0 3.3V-plus-1.sym
N 43700 51100 48300 51100 4
N 48300 50700 52300 50700 4
T 49200 50900 9 10 1 0 0 0 2
Decoupling caps - place near
microcontroller VCC pins.
N 42600 42200 40800 42200 4
{
T 41000 42200 5 10 1 1 0 0 1
netname=PDI_DATA
}
N 40800 41900 42600 41900 4
{
T 41000 41900 5 10 1 1 0 0 1
netname=\_RESET\_/PDI_CLK
}
C 53100 47100 1 0 0 conn-pdi-1.sym
{
T 54900 48900 5 10 0 0 0 0 1
device=CONNECTOR_6
T 53200 49100 5 10 1 1 0 0 1
refdes=CONN5
}
C 54900 47800 1 0 0 nc-right-1.sym
{
T 55000 48300 5 10 0 0 0 0 1
value=NoConnection
T 55000 48500 5 10 0 0 0 0 1
device=DRC_Directive
}
C 54900 48100 1 0 0 nc-right-1.sym
{
T 55000 48600 5 10 0 0 0 0 1
value=NoConnection
T 55000 48800 5 10 0 0 0 0 1
device=DRC_Directive
}
C 56100 48600 1 0 0 3.3V-plus-1.sym
C 54800 46900 1 0 0 gnd-1.sym
N 54800 47600 56400 47600 4
{
T 54900 47600 5 10 1 1 0 0 1
netname=\_RESET\_/PDI_CLK
}
N 54800 48200 54900 48200 4
N 54800 47900 54900 47900 4
N 55900 48800 54800 48800 4
{
T 54900 48800 5 10 1 1 0 0 1
netname=PDI_DATA
}
N 54800 48500 56300 48500 4
N 56300 48500 56300 48600 4
N 54800 47300 54900 47300 4
N 54900 47300 54900 47200 4
T 53100 49500 9 16 1 0 0 0 2
Programming/debugging
interface connector
N 50700 47000 51800 47000 4
{
T 50800 47000 5 10 1 1 0 0 1
netname=UART_RX
}
N 50700 46700 51800 46700 4
{
T 50800 46700 5 10 1 1 0 0 1
netname=UART_TX
}
C 49000 46200 1 0 0 conn-uart-1.sym
{
T 50800 47100 5 10 0 0 0 0 1
device=CONNECTOR_4
T 49000 47600 5 10 1 1 0 0 1
refdes=CONN3
}
C 50700 46000 1 0 0 gnd-1.sym
C 50600 47400 1 0 0 3.3V-plus-1.sym
N 50700 47300 50800 47300 4
N 50800 47300 50800 47400 4
N 50700 46400 50800 46400 4
N 50800 46400 50800 46300 4
T 48900 48000 9 16 1 0 0 0 1
UART (serial) connector
N 46300 49400 47500 49400 4
{
T 46500 49400 5 10 1 1 0 0 1
netname=UART_RX
}
N 46300 49100 47500 49100 4
{
T 46500 49100 5 10 1 1 0 0 1
netname=UART_TX
}
N 46300 44800 47300 44800 4
{
T 46500 44800 5 10 1 1 0 0 1
netname=CODE0
}
N 46300 44500 47300 44500 4
{
T 46500 44500 5 10 1 1 0 0 1
netname=CODE1
}
N 46300 44200 47300 44200 4
{
T 46500 44200 5 10 1 1 0 0 1
netname=CODE2
}
N 46300 43300 47300 43300 4
{
T 46500 43300 5 10 1 1 0 0 1
netname=CODE5
}
N 46300 43600 47300 43600 4
{
T 46500 43600 5 10 1 1 0 0 1
netname=CODE4
}
N 46300 43900 47300 43900 4
{
T 46500 43900 5 10 1 1 0 0 1
netname=CODE3
}
N 46300 43000 47300 43000 4
{
T 46500 43000 5 10 1 1 0 0 1
netname=CODE6
}
N 46300 42700 47300 42700 4
{
T 46500 42700 5 10 1 1 0 0 1
netname=CODE7
}
N 46300 45300 47300 45300 4
{
T 46500 45300 5 10 1 1 0 0 1
netname=FEED
}
N 46300 45600 47300 45600 4
{
T 46500 45600 5 10 1 1 0 0 1
netname=RELAY
}
N 46300 46200 48000 46200 4
{
T 46500 46200 5 10 1 1 0 0 1
netname=\_REEL_EMPTY\_
}
N 48000 45900 46300 45900 4
{
T 46500 45900 5 10 1 1 0 0 1
netname=\_PUNCH_EMPTY\_
}
N 41300 44800 42600 44800 4
{
T 41500 44800 5 10 1 1 0 0 1
netname=STAT_GRN
}
N 41300 44500 42600 44500 4
{
T 41500 44500 5 10 1 1 0 0 1
netname=STAT_RED
}
N 46300 47400 47600 47400 4
{
T 46500 47400 5 10 1 1 0 0 1
netname=\_OK\_
}
N 46300 47100 47600 47100 4
{
T 46500 47100 5 10 1 1 0 0 1
netname=\_CANCEL\_
}
N 41300 44200 42600 44200 4
{
T 41500 44200 5 10 1 1 0 0 1
netname=LCD_E
}
N 41300 43900 42600 43900 4
{
T 41500 43900 5 10 1 1 0 0 1
netname=LCD_RS
}
N 41300 43600 42600 43600 4
{
T 41500 43600 5 10 1 1 0 0 1
netname=LCD_DB4
}
N 41300 43300 42600 43300 4
{
T 41500 43300 5 10 1 1 0 0 1
netname=LCD_DB5
}
N 41300 43000 42600 43000 4
{
T 41500 43000 5 10 1 1 0 0 1
netname=LCD_DB6
}
N 41300 42700 42600 42700 4
{
T 41500 42700 5 10 1 1 0 0 1
netname=LCD_DB7
}
N 46300 48200 47300 48200 4
{
T 46500 48200 5 10 1 1 0 0 1
netname=USB_D-
}
N 46300 47900 47300 47900 4
{
T 46500 47900 5 10 1 1 0 0 1
netname=USB_D+
}
C 46600 49700 1 0 0 gnd-1.sym
N 46300 49700 46400 49700 4
N 46400 49700 46400 50000 4
N 46300 50000 46700 50000 4
C 46600 48500 1 0 0 gnd-1.sym
N 46300 48500 46400 48500 4
N 46400 48500 46400 48800 4
N 46300 48800 46700 48800 4
N 46300 46500 48000 46500 4
{
T 46500 46500 5 10 1 1 0 0 1
netname=USB_SENSE
}
C 46300 41500 1 0 0 gnd-1.sym
N 46300 41900 46400 41900 4
N 46400 41800 46400 42200 4
N 46300 42200 46400 42200 4
N 49800 43700 50000 43700 4
N 50000 43700 50000 43800 4
N 50000 43800 50200 43800 4
N 49800 43300 50000 43300 4
N 50000 43300 50000 43200 4
N 50000 43200 50200 43200 4
N 49800 44100 50000 44100 4
N 50000 44100 50000 44900 4
N 50000 44900 53800 44900 4
{
T 52500 44700 5 10 1 1 0 0 1
netname=USB_VBUS
}
N 51200 44900 51200 44800 4
N 49800 42900 50000 42900 4
N 50000 42100 50000 42900 4
N 50000 42100 51200 42100 4
N 51200 42000 51200 42200 4
N 52200 43800 53100 43800 4
{
T 52300 43800 5 10 1 1 0 0 1
netname=USB_D-
}
N 52200 43200 53100 43200 4
{
T 52300 43200 5 10 1 1 0 0 1
netname=USB_D+
}
C 53700 44700 1 270 0 resistor-1.sym
{
T 54050 44300 5 10 0 0 270 0 1
device=RESISTOR
T 54000 44500 5 10 1 1 270 0 1
refdes=R14
T 54000 44100 5 10 1 1 270 0 1
value=10k
T 53700 44700 5 10 0 0 0 0 1
footprint=0805
T 53700 44700 5 10 0 0 0 0 1
x-power-rating=125m
}
C 53700 43200 1 270 0 resistor-1.sym
{
T 54050 42800 5 10 0 0 270 0 1
device=RESISTOR
T 54000 43000 5 10 1 1 270 0 1
refdes=R15
T 54000 42600 5 10 1 1 270 0 1
value=10k
T 53700 43200 5 10 0 0 0 0 1
footprint=0805
T 53700 43200 5 10 0 0 0 0 1
x-power-rating=125m
}
C 51100 41700 1 0 0 gnd-1.sym
C 53700 41900 1 0 0 gnd-1.sym
N 53800 42200 53800 42300 4
N 53800 43200 53800 43800 4
N 53800 44700 53800 44900 4
N 53800 43500 56100 43500 4
{
T 54900 43500 5 10 1 1 0 0 1
netname=USB_SENSE
}
C 48300 42200 1 0 0 conn-usb-b-1.sym
{
T 48300 44600 5 10 1 1 0 0 1
refdes=CONN4
T 48300 44500 5 10 0 0 0 0 1
device=USB_CON
T 48300 44700 5 10 0 0 0 0 1
footprint=USB_B
}
T 49300 45200 9 16 1 0 0 0 1
USB connector & ESD protection
C 54500 43200 1 270 0 capacitor-1.sym
{
T 55000 43000 5 10 1 1 270 0 1
refdes=C9
T 55400 43000 5 10 0 0 270 0 1
symversion=0.1
T 55000 42600 5 10 1 1 270 0 1
value=1u
T 54500 43200 5 10 0 0 0 0 1
footprint=0805
T 54500 43200 5 10 0 0 0 0 1
x-dielectric=X7R
T 54500 43200 5 10 0 0 0 0 1
x-min-voltage-rating=10
}
C 54600 41900 1 0 0 gnd-1.sym
N 54700 42200 54700 42300 4
N 54700 43200 54700 43500 4
T 54500 44000 9 10 1 0 0 0 5
Voltage divider reduces
5V to 2.5V (greater than
minimum 2.31V required
for a logic HIGH). The
capacitor is for debouncing.
T 50000 40700 9 10 1 0 0 0 1
Microcontroller & USB/UART/PDI connectors
T 53900 40100 9 10 1 0 0 0 1
Kier Davis
C 42600 40900 1 0 0 atxmega192c3-au-1.sym
{
T 46910 50007 5 10 0 0 0 0 1
device=ATXMEGA192C3
T 46917 49607 5 10 0 0 0 0 1
footprint=TQFP64_14
T 45817 40907 5 10 1 1 0 0 1
refdes=U1
}
C 50200 42200 1 0 0 usblc6-2sc6-1.sym
{
T 51700 45200 5 10 0 0 0 0 1
device=USBLC6-2
T 51700 44600 5 10 1 1 0 0 1
refdes=U2
}
N 42600 45300 42500 45300 4
N 42500 45300 42500 50000 4
N 42200 50000 42600 50000 4
N 42600 49700 42500 49700 4
N 42600 49400 42500 49400 4
N 42600 49100 42500 49100 4
N 42600 48800 42500 48800 4
N 42600 48500 42500 48500 4
N 42600 48200 42500 48200 4
N 42600 47900 42500 47900 4
N 42600 47400 42500 47400 4
N 42600 47100 42500 47100 4
N 42600 46800 42500 46800 4
N 42600 46500 42500 46500 4
N 42600 46200 42500 46200 4
N 42600 45900 42500 45900 4
N 42600 45600 42500 45600 4
C 42100 49700 1 0 0 gnd-1.sym
N 46300 46800 47200 46800 4
{
T 46500 46800 5 10 1 1 0 0 1
netname=SYNC
}
T 53900 40400 9 10 1 0 0 0 1
r2 (2017-11-23)
T 50000 40400 9 10 1 0 0 0 1
2-microcontroller.sch
T 50000 40100 9 10 1 0 0 0 1
2
T 51500 40100 9 10 1 0 0 0 1
5
C 40500 40000 0 0 0 title-A3.sym
C 47800 41600 1 270 0 resistor-1.sym
{
T 48150 41200 5 10 0 0 270 0 1
device=RESISTOR
T 47400 41200 5 10 1 1 0 0 1
refdes=R48
T 47400 41000 5 10 1 1 0 0 1
value=1M
T 47800 41600 5 10 0 0 0 0 1
footprint=0805
T 47800 41600 5 10 0 0 0 0 1
x-power-rating=125m
}
C 48300 41600 1 270 0 capacitor-1.sym
{
T 48800 41200 5 10 1 1 0 0 1
refdes=C15
T 49200 41400 5 10 0 0 270 0 1
symversion=0.1
T 48800 41000 5 10 1 1 0 0 1
value=4.7n
T 48300 41600 5 10 0 0 0 0 1
footprint=0805
T 48300 41600 5 10 0 0 0 0 1
x-dielectric=X7R
T 48300 41600 5 10 0 0 0 0 1
x-min-voltage-rating=50
}
N 47900 41600 47900 41700 4
N 47900 41700 48500 41700 4
N 48500 41700 48500 41600 4
N 47900 40700 47900 40600 4
N 47900 40600 48500 40600 4
N 48500 40600 48500 40700 4
C 48100 40200 1 0 0 gnd-1.sym
N 48200 40500 48200 40600 4
N 48200 41700 48200 42000 4
N 48200 42000 48900 42000 4
N 48900 42000 48900 42200 4
T 45600 40200 9 10 1 0 0 0 2
RC filter as recommended
by document AVR1017.
