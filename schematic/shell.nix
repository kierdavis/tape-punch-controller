with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "piii-project-schematic-env";
  buildInputs = [ geda ];
}
