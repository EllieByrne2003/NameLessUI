{ pkgs ? import <nixpkgs> {} }:

let
    namelessUtils = pkgs.stdenv.mkDerivation {
        pname = "nlut";
        version = "0.1.1";

        src = ../NameLessUtils;

        nativeBuildInputs = with pkgs; [
            gcc
            gnumake

            libGL
            glfw
            glew
            glm
            nlohmann_json
        ];

        buildPhase = ''
            runHook preBuild
            make -j $NIX_BUILD_CORES
            runHook postBuild
        '';

        installPhase = ''
            runHook preInstall

            mkdir -p $out/lib
            mkdir -p $out/include/NLUT

            cp bin/*.so* $out/lib/ 2>/dev/null || true

            cd src
            echo $out/include
            find -wholename "**/*.hpp"
            cp --parents **/*.hpp $out/include/NLUT/ 2>/dev/null || true

            echo "$out/include/"
            cd ..

            runHook postInstall
        '';
    };
in

pkgs.mkShell {
    buildInputs = with pkgs; [
        git
        gcc
        gdb
        gnumake
        bear
        # valgrind

        libGL
        glfw
        glew
        glm
        nlohmann_json

        renderdoc

        namelessUtils
    ];

    # shellHook = ''
    #     echo "NameLessUtils is at: ${namelessUtils}"

    # '';
}