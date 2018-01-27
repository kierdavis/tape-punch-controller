{ pkgs ? import <nixpkgs> {}, device ? "atmega644p", platform ? null }:

with pkgs;

stdenv.mkDerivation rec {
  name = "piii-project-firmware-env";

  buildInputs = [ avrbinutils avrdude avrgcc avrlibc ];

  PLATFORM = platform;

  CPPFLAGS = [ "-isystem ${avrlibc}/avr/include" ];

  shellHook = ''
    lib=$(find ${avrlibc}/avr/lib -name "lib${device}.a" -print)
    if [ -z "$lib" ]; then
      echo >&2 "Could not find target-specific library in ${avrlibc}/avr/lib (bad `device`?)."
      exit 1
    fi
    libdir=$(dirname $lib)
    export LDFLAGS="-B $libdir -L $libdir"
  '';
}
