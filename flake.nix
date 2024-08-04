{
  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    nix-systems.url = "github:nix-systems/default";
  };
  outputs = inputs @ {
    self,
    nixpkgs,
    ...
  }: let
    eachSystem = nixpkgs.lib.genAttrs (import inputs.nix-systems);
    mkPkgs = system: nixpkgs.legacyPackages.${system};
  in {
    packages = eachSystem (system: let
      pkgs = mkPkgs system;
    in {
      default = pkgs.stdenv.mkDerivation {
        name = "Oware-Life";
        src = ./.;
        buildInputs = with pkgs; [
          gcc
          gnumake
          cmake
          sfml
          libGLU
        ];
        configurePhase = ''
          mkdir -p bin
          mkdir -p build
          cd build
          cmake -DCMAKE_BUILD_TYPE=Release ..
        '';
        buildPhase = ''
          cmake --build .
          mv Oware ../bin
        '';
        installPhase = ''
          mkdir -p $out/bin
          cp ../bin/Oware $out/bin/
        '';
      };
    });
    apps = eachSystem (system: {
      default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/Oware";
      };
    });
    devShells = eachSystem (system: let 
        pkgs = mkPkgs system; 
    in
    {
        default = pkgs.mkShell{
        buildInputs = with pkgs;[
          gcc
          gnumake
          cmake
          sfml
          libGLU
          ];
        };
    });
    };
}
