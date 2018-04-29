# Tape Punch Controller

This repository contains the source code and CAD designs used for my university third year individual project.

The project involves designing a system that can interface a restored [Teletype BPRE-type High Speed Tape Punch][tapepunch] to a modern computer over USB.

## Repository Layout

- [`/firmware`][repo-firmware]: source code of the firmware running on the microcontroller
- [`/pcb`][repo-pcb]: design files for the PCB used in the device
- [`/mechanical`][repo-mechanical]: design files for various laser-cut parts

[tapepunch]: http://www.computinghistory.org.uk/det/2312/teletype-brpe-20-high-speed-tape-punch/
[repo-firmware]: https://github.com/kierdavis/tape-punch-controller/tree/master/firmware
[repo-pcb]: https://github.com/kierdavis/tape-punch-controller/tree/master/pcb
[repo-mechanical]: https://github.com/kierdavis/tape-punch-controller/tree/master/mechanical

## Branches

Two main Git branches are used with this repository: `master` and `stable`. New development occurs on `master`; when it has been tested and is deemed ready to ship to the client, it is merged into `stable`. `stable` should be a reflection of the version currently in use by the client.

## License

The contents of this repository are licensed under the terms of the MIT license. See the [LICENSE](LICENSE) file for more details.
