with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "piii-project-schematic-util-env";
  buildInputs = [ geda python3 ];
}
