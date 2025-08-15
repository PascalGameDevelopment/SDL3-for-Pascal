# SDL3-for-Pascal

Unit files for building
[Free Pascal](https://freepascal.org/) / [Delphi](https://www.embarcadero.com/products/delphi) applications
using the [SDL3 library](https://libsdl.org).

## Installation

Simply add the units to your include path. You can achieve this by:
 - (FPC) using the `{$UNITPATH XXX}` directive in your source code;
 - (FPC) using the `-FuXXX` command-line argument to the compiler;
 - just copying & pasting the units into the same directory as your main source code.

Use the `SDL3` unit for the main SDL3 library (should be always needed). Units for the other SDL3 libraries are (or will be) also provided:
 - [`SDL3_image`](https://github.com/libsdl-org/SDL_image)
 - [`SDL3_ttf`](https://github.com/libsdl-org/SDL_ttf)
 - [`SDL3_mixer`](https://github.com/libsdl-org/SDL_mixer)
 - [`SDL3_net`](https://github.com/libsdl-org/SDL_net) (not published yet)
 - [`SDL3_gfx`](https://github.com/sabdul-khabir/SDL3_gfx)

## Documentation

- [`Tutorial for SDL3`](https://www.freepascal-meets-sdl.net/sdl-tutorials/)

## Bugs / Contributions / ToDos

If you have any contributions or bugfixes, feel free to drop a pull request or send in a patch.
Please use the GitHub [issue tracker](https://github.com/PascalGameDevelopment/SDL3-for-Pascal/issues).

### ToDos

- implement GitHub Pages documentation via GitHub Actions
- add tests ([FPCUnit](https://wiki.freepascal.org/fpcunit)?)
- improve units (search for "#todo" to find specific tasks)
- adapt comments to [PasDoc format](https://pasdoc.github.io) (later)

### Code style guidelines

The main principle is to stay as tight as possible at the names in the C headers.
These guidelines aim to have better consistency in this community project and make
it easier to find certain code parts in the C headers/Pascal includes. Feel free
to discuss or extend these guidelines, use the issue tracker.

For details please refer to our [Translation Code Style Sheet](STYLESHEET.md).

## Versions

The version number/tag (see [tags](https://github.com/PascalGameDevelopment/SDL3-for-Pascal/tags)) refers to the version of this unit  package [SDL3 for Pascal](https://github.com/PascalGameDevelopment/SDL3-for-Pascal), not the `SDL3 Library`.

### v0.x (work in progress)

### v0.5 (15/08/2025)

- adds SDL3_ttf unit
- adds SDL3_mixer unit
- adds SDL3_gfx unit
- adds further include files for SDL3 unit
- updates some includes files
- adds basic CI feature (compilation tests)
- adds type size test
- bugfixes

### v0.4 (15/03/2025)

- adds working SDL3 unit (rather complete)
- adds working SDL3_image unit
- units seem stable

## License

The units are licensed under the [zlib license](https://opensource.org/license/zlib).
