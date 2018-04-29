# Firmware

The firmware for the microcontroller is written in C++, using the GNU toolchain (`avr-gcc`, `avr-binutils` and `avr-libc`) for compilation and [`avrdude`][avrdude] for uploading programs to the microcontroller. The [LUFA][lufa] library (used primarily for its USB support code) provides a makefile-based build system which is used by this project.

## Obtaining source code

If you don't already have a copy of the source code, you will need to obtain a copy of this repository from Github:

```sh
git clone --recursive https://github.com/kierdavis/tape-punch-controller
```

If you do, you should make sure that the LUFA dependency (a Git submodule located in `firmware/lib/lufa`) has also been downloaded. If not (or if you are unsure), run:

```sh
git submodule update --init --recursive
```

to ensure it is downloaded.

## Compiling

Once done, you should be able to compile the firmware as follows:

```sh
cd firmware
make
```

If your processor has multiple cores, you can use `make -j $(nproc)` to speed up compilation by running more than one job in parallel. This should leave the compiled firmware image in the current directory in various forms:

* `firmware.elf`: the "master file" output directly from the linker, from which other files are generated
* `firmware.bin`: the machine code in unencoded binary
* `firmware.hex`: the machine code in Intel HEX format, used by e.g. avrdude
* `firmware.eep`: initial EEPROM contents in Intel HEX format (not used)
* `firmware.lss`: disassembly listing, can be useful for debugging
* `firmware.map`: memory layout information, can be useful for debugging
* `firmware.sym`: list of symbols and their addresses, can be useful for debugging

## Uploading to the microcontroller

Programs are uploaded to the microcontroller using the PDI protocol (exclusive to a small number of Atmel microcontrollers), so you will need a programmer device that supports this. The officially recommended tool for this is the [Atmel-ICE][atmel-ice], which should work. Lacking one of these, I ported the PDI functionality found in the LUFA project's AVRISP clone to my Il Matto development board.

TODO: explain how to set up and use pdi-programmer. Probably need to port it to Arduino first.

[avrdude]: https://www.nongnu.org/avrdude/
[lufa]: http://www.fourwalledcubicle.com/LUFA.php
[atmel-ice]: http://www.microchip.com/developmenttools/productdetails.aspx?partno=atatmel-ice
