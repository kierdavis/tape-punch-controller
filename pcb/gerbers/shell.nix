{ pkgs ? import <nixpkgs> {} }:

with pkgs;

stdenv.mkDerivation {
  name = "tpc-pcb-gerbers-env";
  buildInputs = [
    gerbv
  ];
}
