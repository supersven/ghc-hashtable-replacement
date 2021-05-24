{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [
      pkgs.buildPackages.gnumake
      pkgs.buildPackages.gcc
      pkgs.buildPackages.gdb
      pkgs.buildPackages.valgrind
    ];
}
