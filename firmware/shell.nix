{ pkgs ? import <nixpkgs> {}, device ? "atxmega192c3", buildInputs ? [] }:

with pkgs;

let
  pdiprog = pkgs.callPackage ./pdi-programmer/client {};

in stdenv.mkDerivation {
  name = "piii-project-firmware-env";

  buildInputs = [ avrbinutils avrdude avrgcc avrlibc pdiprog ];

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
