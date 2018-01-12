with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "piii-project-lasercut-env";
  buildInputs = [ librecad ];
}
