{ pkgs ? import <nixpkgs> {} }:

import ./shell.nix {
  inherit pkgs;
  device = "atxmega192c3";
  platform = "pcb";
}
