{ pkgs ? import <nixpkgs> {} }:

import ./shell.nix {
  inherit pkgs;
  device = "atmega644p";
  platform = "il-matto";
}
