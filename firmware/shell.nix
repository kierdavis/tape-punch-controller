with import <nixpkgs> {};

stdenv.mkDerivation rec {
  name = "piii-project-firmware-env";

  buildInputs = [ avrbinutils avrdude avrgcc avrlibc ];

  DEVICE = "atmega644p";
  F_CPU = "12000000";

  CFLAGS = [ "-isystem ${avrlibc}/avr/include" ];

  shellHook = ''
    lib=$(find ${avrlibc}/avr/lib -name "lib${DEVICE}.a" -print)
    if [ -z "$lib" ]; then
      echo >&2 "Could not find target-specific library in ${avrlibc}/avr/lib (bad DEVICE?)."
      exit 1
    fi
    libdir=$(dirname $lib)
    export LDFLAGS="-B $libdir -L $libdir"
  '';
}
