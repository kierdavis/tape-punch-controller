# Tape Punch Controller Schematics

This is the schematic diagram for the tape punch controller. It is viewable with `gschem` (part of the [gEDA suite][geda]).

The schematic is split into five pages:

* `1-tape-punch.sch`, containing the breakout of the tape punch's control cable and the signal conditioning circuit for the
feedback signal.
* `2-microcontroller.sch`, containing the ATxmega192C3 microcontroller and its USB, PDI and UART connectors.
* `3-power.sch`, containing the power input connector, step-down converters and circuitry for driving the electromagnets 
inside the tape punch.
* `4-controls.sch`, containing on-board LEDs and buttons, and connectors to the offboard LEDs, buttons and LCD screen.
* `5-test-points.sch`, containing a number of [test points][test-point] useful for debugging.

All symbols used by the schematic, including those originally from the gEDA standard library, are mirrored in the `symbols` 
subdirectory to prevent breakage in the event of any potential standard library changes and to enable local modifications to 
the symbols if necessary.

[geda]: http://www.geda-project.org/
[test-point]: https://en.wikipedia.org/wiki/Test_point
