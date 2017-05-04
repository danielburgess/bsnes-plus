# bsnes-plus (SuperFamicade controls added)

bsnes-plus (or bsnes+) is a fork of bsnes (based on bsnes-classic) intended to
introduce some new features and improvements, mostly aimed at debugging.

All that this version has added is a few extra button inputs so that I can test my SuperFamicade controls while debugging.

My SuperFamicade project is here: https://hackaday.io/project/3121-super-famicade-hardcore-snes-arcade-hack


## Check out the original repository
https://github.com/devinacker/bsnes-plus

## Building on Windows

- Install mingw64/Qt package included in the repository. (qt-4.8.6-x64-mingw492r1-seh.exe)
- Make sure the Qt `bin` directory is in your system path
- Run `mingw32-make`

Building with the original MinGW used to be the preferred way to do it, but made building "out of the box" annoying for various reasons (including requiring outdated DirectX headers/libs and problems with some native Windows code) and is no longer supported.

## Building on OS X

- Install a C++ toolchain ([Xcode](https://developer.apple.com) is probably the easiest route)  
- Install Qt 4.8 (get [Brew](http://brew.sh) and run `brew install qt`)  
- Make sure the `qtpath` environment variable points to your Qt installation, ie. add `export qtpath=/usr/local/Cellar/qt/4.8.7_2` to .bash_profile.
- Run `make`from the bsnes directory.

If you're running macOS 10.12 Sierra you will (probably not) be able to install Qt4 using brew. If so, try installing this unofficial branch:

```
brew install cartr/qt4/qt
brew linkapps qt
```

## Building on Linux / other *nix

As there is no ``configure`` step, make sure necessary Qt4/X11 packages are installed. On a Debian/Ubuntu system, it would require a command like:

```
apt-get install libqt4-dev libqt4-dev-bin libxv-dev libsdl1.2-dev libao-dev
libopenal-dev g++
```

Afterwards, run ``make`` and if everything works out correctly you will find the output binary in the ``out/`` directory.

The snesfilter, snesreader, and supergameboy plugins can all be built by running make (or mingw32-make) after you've configured your environment to build bsnes itself.
After building, just copy the .dll, .so, or .dylib files into the same directory as bsnes itself.

This fork of bsnes doesn't include the alternate UI based on byuu's `phoenix` library. The purpose of this fork is primarily to add additional UI functionality and I have no intention of implementing every new feature twice using completely different libraries just to keep both versions of the UI at parity.

bsnes v073 and its derivatives are licensed under the GPL v2; see *Help > License ...* for more information.

## Contributors

See *Help > Documentation ...* for a list of authors.
