#!/bin/sh

set -o errexit -o pipefail -o nounset

avrdude -c usbasp -p m644p -U flash:w:build/firmware.hex
