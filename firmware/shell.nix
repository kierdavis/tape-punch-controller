{ pkgs ? import <nixpkgs> {}, device ? "atxmega192c3", buildInputs ? [] }:

with pkgs;

let
  pdiprog-src = fetchTarball https://github.com/kierdavis/pdi-programmer/archive/1db20221af78bfecaf71d872678ff31be1b0fd5e.tar.gz;
  pdiprog = pkgs.callPackage (import "${pdiprog-src}/client") {};

in stdenv.mkDerivation {
  name = "tpc-firmware-env";

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
