{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  packages = with pkgs; [
    clang
    gnumake
    pkg-config
    SDL2
    SDL2_image
    SDL2_ttf
  ];
}
