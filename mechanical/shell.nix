with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "tpc-mechanical-env";
  buildInputs = [ librecad ];
}
