{ pkgs ? import <nixpkgs> {}, device ? "atmega644p", platform ? null, buildInputs ? [] }:

with pkgs;

stdenv.mkDerivation {
  name = "piii-project-firmware-env";

  buildInputs = buildInputs ++ [ avrbinutils avrdude avrgcc avrlibc ];

  PLATFORM = platform;

  CC_FLAGS = [ "-isystem ${avrlibc}/avr/include" ];

  shellHook = ''
    lib=$(find ${avrlibc}/avr/lib -name "lib${device}.a" -print)
    if [ -z "$lib" ]; then
      echo >&2 "Could not find target-specific library in ${avrlibc}/avr/lib (bad `device`?)."
      exit 1
    fi
    libdir=$(dirname $lib)
    export LD_FLAGS="-B $libdir -L $libdir"
  '';
}
