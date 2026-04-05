# SDL3-for-Pascal H2Paswizard Tool

This file describes how to use the
[H2Paswizard tool](https://wiki.freepascal.org/H2Paswizard)
to translate SDL3 header files into Pascal units for the
[SDL3 for Pascal Project](https://github.com/PascalGameDevelopment/SDL3-for-Pascal).
[H2Pas](https://wiki.freepascal.org/H2Pas) is a command line tool to translate
C header files into Pascal units. H2Paswizard is a GUI for easier use of H2Pas.

H2Paswizard is shipped as package alongside with the Lazarus IDE but is not
installed. The file `translate-sdl3-h2paswizard.h2p` is specifically created by
us to translate SDL3 header files into Pascal units as required for
SDL3-for-Pascal.

## How to start

- [Install the H2Paswizard package](https://wiki.lazarus.freepascal.org/Install_Packages)
to the Lazarus IDE
- Start H2Paswizard: Select menu item Tools -> H2Pas...
- Click on "Add .h files..."-button and add `sdl3code.h` (from SDL3-for-Pascal
tools/h2paswizard folder)
- Click on "Open Settings"-button and open `translate-sdl3-h2paswizard.h2p`
- Open "H2Pas Options"-tab; activate the following options: -e, -i, -D, -c, -p, -T, -C
- Further options: -l Library name: "SDL3"
- Output extension: ".inc"
- Output directory: e.g. SDL3-for-Pascal/tools/h2paswizard/
- Open `sdl3code.h` and `sdl3code.inc` in Lazarus
- Now you are ready to copy C code into `sdl3code.h` and get the resulting Pascal
code in `sdl3code.inc` by hitting "Run H2Pas"

*Hint:* You should open the settings always again, if you closed H2Paswizard.
Otherwise the settings file is not recognized.

*Important:* The results are not perfect, they must always be revised.






