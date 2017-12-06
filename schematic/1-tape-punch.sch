v 20130925 2
N 48600 47400 49800 47400 4
{
T 48700 47400 5 10 1 1 0 0 1
netname=TP_CODE1
}
N 48600 47000 49800 47000 4
{
T 48700 47000 5 10 1 1 0 0 1
netname=TP_CODE2
}
N 48600 46600 49800 46600 4
{
T 48700 46600 5 10 1 1 0 0 1
netname=TP_CODE3
}
N 48600 46200 49800 46200 4
{
T 48700 46200 5 10 1 1 0 0 1
netname=TP_CODE4
}
N 48600 45800 49800 45800 4
{
T 48700 45800 5 10 1 1 0 0 1
netname=TP_CODE5
}
N 48600 45400 49800 45400 4
{
T 48700 45400 5 10 1 1 0 0 1
netname=TP_CODE6
}
N 48600 45000 49800 45000 4
{
T 48700 45000 5 10 1 1 0 0 1
netname=TP_CODE7
}
N 48600 44600 49800 44600 4
{
T 48700 44600 5 10 1 1 0 0 1
netname=TP_CODE0
}
N 48600 44200 49800 44200 4
{
T 48700 44200 5 10 1 1 0 0 1
netname=TP_FEED
}
C 47100 42200 1 0 0 conn-tape-punch-1.sym
{
T 48500 47550 5 10 0 0 0 0 1
device=DB25
T 47500 47900 5 10 1 1 0 0 1
refdes=CONN8
}
N 45900 42800 47100 42800 4
{
T 46000 42800 5 10 1 1 0 0 1
netname=TP_RELAY
}
C 45800 45700 1 0 0 27V-plus-1.sym
C 50000 43900 1 0 0 27V-plus-1.sym
N 48600 43800 50200 43800 4
N 50200 43800 50200 43900 4
C 46500 46300 1 0 0 nc-left-1.sym
{
T 46500 46700 5 10 0 0 0 0 1
value=NoConnection
T 46500 47100 5 10 0 0 0 0 1
device=DRC_Directive
}
C 46500 45900 1 0 0 nc-left-1.sym
{
T 46500 46300 5 10 0 0 0 0 1
value=NoConnection
T 46500 46700 5 10 0 0 0 0 1
device=DRC_Directive
}
N 47000 46400 47100 46400 4
N 47000 46000 47100 46000 4
N 47100 45600 46000 45600 4
N 46000 45200 46000 45700 4
N 47100 45200 46000 45200 4
N 47100 43600 46000 43600 4
C 48600 42200 1 0 0 gnd-1.sym
C 45400 44000 1 0 0 gnd-1.sym
N 48600 42600 48700 42600 4
N 48700 42600 48700 42500 4
N 44200 44800 47100 44800 4
N 41000 46800 47100 46800 4
{
T 41100 46800 5 10 1 1 0 0 1
netname=\_PUNCH_EMPTY\__RAW
}
C 45500 46900 1 90 0 resistor-1.sym
{
T 45150 47300 5 10 0 0 90 0 1
device=RESISTOR
T 44900 47400 5 10 1 1 0 0 1
refdes=R38
T 44900 47200 5 10 1 1 0 0 1
value=10k
T 45500 46900 5 10 0 0 0 0 1
footprint=0805
T 45500 46900 5 10 0 0 0 0 1
x-power-rating=125m
}
C 45500 44900 1 90 0 resistor-1.sym
{
T 45150 45300 5 10 0 0 90 0 1
device=RESISTOR
T 44900 45400 5 10 1 1 0 0 1
refdes=R39
T 44900 45200 5 10 1 1 0 0 1
value=10k
T 45500 44900 5 10 0 0 0 0 1
footprint=0805
T 45500 44900 5 10 0 0 0 0 1
x-power-rating=125m
}
N 45400 44800 45400 44900 4
N 45400 46800 45400 46900 4
C 45200 47900 1 0 0 3.3V-plus-1.sym
C 45200 45900 1 0 0 3.3V-plus-1.sym
N 45400 47800 45400 47900 4
N 45400 45800 45400 45900 4
C 46500 47100 1 0 0 nc-left-1.sym
{
T 46500 47500 5 10 0 0 0 0 1
value=NoConnection
T 46500 47900 5 10 0 0 0 0 1
device=DRC_Directive
}
C 46500 43900 1 0 0 nc-left-1.sym
{
T 46500 44300 5 10 0 0 0 0 1
value=NoConnection
T 46500 44700 5 10 0 0 0 0 1
device=DRC_Directive
}
C 45800 43700 1 0 0 27V-plus-1.sym
N 46000 43600 46000 43700 4
N 47000 44000 47100 44000 4
N 47000 47200 47100 47200 4
N 47100 44400 45500 44400 4
N 45500 44400 45500 44300 4
T 50000 40700 9 10 1 0 0 0 1
Tape punch connector & feedback pulse preprocessing
T 53900 40100 9 10 1 0 0 0 1
Kier Davis
C 43900 46200 1 180 0 resistor-1.sym
{
T 43500 45850 5 10 0 0 180 0 1
device=RESISTOR
T 43100 46250 5 10 1 1 0 0 1
refdes=R37
T 43500 46250 5 10 1 1 0 0 1
value=68k
T 43900 46200 5 10 0 0 180 0 1
footprint=0805
T 43900 46200 5 10 0 0 180 0 1
x-power-rating=125m
}
C 42900 44900 1 90 0 capacitor-1.sym
{
T 43000 45400 5 10 1 1 0 0 1
refdes=C12
T 42000 45100 5 10 0 0 90 0 1
symversion=0.1
T 43000 45200 5 10 1 1 0 0 1
value=100n
T 42900 44900 5 10 0 0 0 0 1
footprint=0805
T 42900 44900 5 10 0 0 0 0 1
x-dielectric=X7R
T 42900 44900 5 10 0 0 0 0 1
x-min-voltage-rating=5
T 42900 44900 5 10 0 0 0 0 1
x-voltage-rating=25
}
N 42700 45800 42700 46100 4
N 41000 46100 43000 46100 4
{
T 41100 46100 5 10 1 1 0 0 1
netname=\_PUNCH_EMPTY\_
}
C 42600 44500 1 0 0 gnd-1.sym
N 42700 44800 42700 44900 4
C 43900 43200 1 180 0 resistor-1.sym
{
T 43500 42850 5 10 0 0 180 0 1
device=RESISTOR
T 43900 43200 5 10 0 0 180 0 1
footprint=0805
T 43900 43200 5 10 0 0 180 0 1
x-power-rating=125m
T 43100 43250 5 10 1 1 0 0 1
refdes=R40
T 43500 43250 5 10 1 1 0 0 1
value=68k
}
C 42900 41900 1 90 0 capacitor-1.sym
{
T 42000 42100 5 10 0 0 90 0 1
symversion=0.1
T 42900 41900 5 10 0 0 0 0 1
footprint=0805
T 42900 41900 5 10 0 0 0 0 1
x-dielectric=X7R
T 42900 41900 5 10 0 0 0 0 1
x-min-voltage-rating=5
T 43000 42400 5 10 1 1 0 0 1
refdes=C13
T 43000 42200 5 10 1 1 0 0 1
value=100n
T 42900 41900 5 10 0 0 0 0 1
x-voltage-rating=25
}
N 42700 42800 42700 43100 4
N 41200 43100 43000 43100 4
{
T 41300 43100 5 10 1 1 0 0 1
netname=\_REEL_EMPTY\_
}
C 42600 41500 1 0 0 gnd-1.sym
N 42700 41800 42700 41900 4
N 44200 46100 44200 46800 4
N 44200 43800 41200 43800 4
{
T 41300 43800 5 10 1 1 0 0 1
netname=\_REEL_EMPTY\__RAW
}
N 44200 43100 44200 44800 4
N 43900 43100 44200 43100 4
N 43900 46100 44200 46100 4
T 41600 47300 9 12 1 0 0 0 1
RC filters for debouncing
C 52100 45800 1 90 0 resistor-1.sym
{
T 51750 46200 5 10 0 0 90 0 1
device=RESISTOR
T 51800 46400 5 10 1 1 180 0 1
refdes=R43
T 51800 46200 5 10 1 1 180 0 1
value=4.7k
T 52100 45800 5 10 0 0 0 0 1
x-power-rating=125m
T 52100 45800 5 10 0 0 0 0 1
footprint=0805
}
C 51800 46800 1 0 0 15V-plus-1.sym
C 52500 45600 1 180 0 resistor-variable-1.sym
{
T 51850 45300 5 10 1 1 180 0 1
refdes=R45
T 51850 44900 5 10 0 1 180 0 1
device=VARIABLE_RESISTOR
T 51850 45100 5 10 1 1 180 0 1
value=1k
}
C 52100 43600 1 90 0 resistor-1.sym
{
T 51750 44000 5 10 0 0 90 0 1
device=RESISTOR
T 51800 44200 5 10 1 1 180 0 1
refdes=R46
T 51800 44000 5 10 1 1 180 0 1
value=6.8k
T 52100 43600 5 10 0 0 0 0 1
x-power-rating=125m
T 52100 43600 5 10 0 0 0 0 1
footprint=0805
}
N 52000 45800 52000 45600 4
N 52000 44500 52000 44700 4
N 52000 46800 52000 46700 4
C 51900 43200 1 0 0 gnd-1.sym
N 52000 43500 52000 43600 4
T 52200 44600 9 10 1 0 0 0 2
Threshold
adjustment
C 51100 47900 1 90 0 resistor-1.sym
{
T 50750 48300 5 10 0 0 90 0 1
device=RESISTOR
T 50800 48500 5 10 1 1 180 0 1
refdes=R41
T 50800 48300 5 10 1 1 180 0 1
value=1k
T 51100 47900 5 10 0 0 0 0 1
x-power-rating=125m
T 51100 47900 5 10 0 0 0 0 1
footprint=0805
}
C 51100 46600 1 90 0 resistor-1.sym
{
T 50750 47000 5 10 0 0 90 0 1
device=RESISTOR
T 50800 47200 5 10 1 1 180 0 1
refdes=R42
T 50800 47000 5 10 1 1 180 0 1
value=1k
T 51100 46600 5 10 0 0 0 0 1
x-power-rating=125m
T 51100 46600 5 10 0 0 0 0 1
footprint=0805
}
C 50800 48900 1 0 0 15V-plus-1.sym
C 50900 46200 1 0 0 gnd-1.sym
N 51000 47900 51000 47500 4
N 51000 48800 51000 48900 4
N 51000 46600 51000 46500 4
N 51000 47700 51800 47700 4
N 47100 43200 45900 43200 4
{
T 46000 43200 5 10 1 1 0 0 1
netname=TP_SYNC-
}
N 49800 43000 48600 43000 4
{
T 48700 43000 5 10 1 1 0 0 1
netname=TP_SYNC+
}
N 52100 47700 52100 48900 4
{
T 52100 48800 5 10 1 1 270 0 1
netname=TP_SYNC+
}
N 51800 47700 51800 48900 4
{
T 51800 48800 5 10 1 1 270 0 1
netname=TP_SYNC-
}
N 52100 47700 52900 47700 4
N 52500 45100 54400 45100 4
N 52700 45100 52700 47300 4
{
T 52900 45100 5 10 1 1 0 0 1
netname=SYNC_THRESH
}
N 52700 47300 52900 47300 4
C 53200 48000 1 0 0 15V-plus-1.sym
C 53300 46700 1 0 0 gnd-1.sym
N 53400 47000 53400 47100 4
N 53400 47900 53400 48000 4
T 52700 43000 9 10 1 0 0 0 6
TP_SYNC- is held at approx 7.5V.
TP_SYNC+ ranges between -5V
and +7V relative to TP_SYNC-.
Threshold is at 1.1V relative to
TP_SYNC-. This produces ~0.5ms
pulses on SYNC.
C 55200 46400 1 90 0 resistor-1.sym
{
T 54850 46800 5 10 0 0 90 0 1
device=RESISTOR
T 54900 47000 5 10 1 1 180 0 1
refdes=R44
T 54900 46800 5 10 1 1 180 0 1
value=68k
T 55200 46400 5 10 0 0 0 0 1
x-power-rating=125m
T 55200 46400 5 10 0 0 0 0 1
footprint=0805
}
C 55200 45100 1 90 0 resistor-1.sym
{
T 54850 45500 5 10 0 0 90 0 1
device=RESISTOR
T 54900 45700 5 10 1 1 180 0 1
refdes=R47
T 54900 45500 5 10 1 1 180 0 1
value=18k
T 55200 45100 5 10 0 0 0 0 1
x-power-rating=125m
T 55200 45100 5 10 0 0 0 0 1
footprint=0805
}
N 53900 47500 56500 47500 4
{
T 55300 47500 5 10 1 1 0 0 1
netname=SYNC_RAW
}
N 55100 47500 55100 47300 4
N 55100 46400 55100 46000 4
C 55000 44700 1 0 0 gnd-1.sym
N 55100 45000 55100 45100 4
N 55100 46200 56000 46200 4
{
T 55300 46200 5 10 1 1 0 0 1
netname=SYNC
}
T 44100 48600 9 16 1 0 0 0 1
Tape punch connector
T 51300 50700 9 16 1 0 0 0 1
Feedback pulse preprocessing
T 49900 49800 9 10 1 0 0 0 4
The tape punch has a pickup coil connected between TP_SYNC- and TP_SYNC+,
emitting a voltage pulse once per revolution of the main shaft. This circuit shapes
the waveform of this signal into a clean square wave, which is connected to an
interrupt pin on the microcontroller.
C 52900 47100 1 0 0 lm321-1.sym
{
T 53600 47900 5 10 0 0 0 0 1
device=OPAMP
T 53600 47700 5 10 1 1 0 0 1
refdes=U5
T 53600 48500 5 10 0 0 0 0 1
symversion=0.1
T 53600 48700 5 10 0 0 0 0 1
value=LM321
}
C 55800 48800 1 180 0 capacitor-1.sym
{
T 55600 47900 5 10 0 0 180 0 1
symversion=0.1
T 54900 48800 5 10 1 1 0 0 1
refdes=C14
T 55500 48800 5 10 1 1 0 0 1
value=100n
T 55800 48800 5 10 0 0 90 0 1
footprint=0805
T 55800 48800 5 10 0 0 90 0 1
x-dielectric=X7R
T 55800 48800 5 10 0 0 90 0 1
x-min-voltage-rating=20
T 55800 48800 5 10 0 0 0 0 1
x-voltage-rating=25
}
C 54400 48700 1 0 0 15V-plus-1.sym
C 56000 48200 1 0 0 gnd-1.sym
N 56100 48500 56100 48600 4
N 54600 48700 54600 48600 4
T 54500 49200 9 10 1 0 0 0 2
Decoupling capacitor,
place next to opamp.
N 54600 48600 54900 48600 4
N 55800 48600 56100 48600 4
N 45900 42400 47100 42400 4
{
T 46000 42400 5 10 1 1 0 0 1
netname=TP_EARTH
}
N 48600 43400 49800 43400 4
{
T 48700 43400 5 10 1 1 0 0 1
netname=TP_EARTH
}
T 53900 40400 9 10 1 0 0 0 1
r3 (2017-12-04)
T 50000 40400 9 10 1 0 0 0 1
1-tape-punch.sch
T 50000 40100 9 10 1 0 0 0 1
1
T 51500 40100 9 10 1 0 0 0 1
5
C 40500 40000 0 0 0 title-A3.sym
