This repository a series of examples demonstrating how to write UGens for [SuperCollider](https://github.com/supercollider/supercollider) (not to be confused with quarks, which are libraries for the language). The [Writing Unit Generators](http://doc.sccode.org/Guides/WritingUGens.html) helpfile is a comprehensive tutorial. Chapter 25 of [the SuperCollider Book](http://www.supercolliderbook.net/) is also a useful resource, although the build instructions are outdated.

Beyond this repository, the reader is encouraged to look at [sc3-plugins](https://github.com/supercollider/sc3-plugins) for more complex, real-world examples.

## Directory

- 01a-BoringMixer -- minimal example of a plugin
- 01b-BoringMixer -- using a newer C++ wrapper
- 02-MySaw -- introduces multiple calculation functions and state variables
- 03-AnalogEcho -- introduces memory allocation and cubic interpolation

## Compiling

Make a directory for the `cmake` build files:

```shell
plugin-example/01-BoringMixer/$ mkdir build && cd build
plugin-example/01-BoringMixer/build/$ cmake -DSC_PATH=/path/to/sc3source/ ..
```

Here, `/path/to/sc3source/` is the path to a directory of the SuperCollider *source code*. The source code version should match your SuperCollider app version. Slight differences will probably be tolerated, but if they're too far apart you will get an "API version mismatch" error when you boot the server.

The path should contain a file at `include/plugin_interface/SC_PlugIn.h`. If you get a warning that `SC_PlugIn.h` could not be found, then `SC_PATH` is not set correctly.

If no `SC_PATH` is provided, the build system assumes the SuperCollider include files in `/usr/include/SuperCollider/`.

```shell
plugin-example/01-BoringMixer/build/$ make
plugin-example/01-BoringMixer/build/$ make install
```

WARNING: on OSX, if you want to install into `CMAKE_INSTALL_PREFIX`, you have to specify it by disabling the `IN_PLACE_BUILD` cmake option which defaults to ON (see below).

## Installing

You can install each folder -- or the entire repository -- as you would a quark: `Quarks.gui` => `Install a folder`.

Alternatively, you can copy, move, or symbolic link the folder into your Extensions folder. You can find out which one that is by evaluating

```
Platform.userExtensionDir
```

from within SuperCollider. Alternatively, you may install the plugin(s) system-wide by copying to

```
Platform.systemExtensionDir
```
