# SuperCollider Example Plugins

This repository demonstrates how to write UGens for [SuperCollider](https://github.com/supercollider/supercollider) using a series of examples. Custom UGens are packaged in server plugins. Plugins are not to be confused with quarks, which are libraries for the language.

This supplements the [Writing Unit Generators](http://doc.sccode.org/Guides/WritingUGens.html) helpfile. Chapter 25 of [the SuperCollider Book](http://www.supercolliderbook.net/) is also a useful resource, although the build instructions are outdated.

There is a lot of conflicting material out there for UGen building. This is the official repository and should be the most up to date.

Beyond this repository, the reader is encouraged to look at [sc3-plugins](https://github.com/supercollider/sc3-plugins) for more complex, real-world examples.

## Directory

- 01a-BoringMixer -- minimal example of a plugin
- 01b-BoringMixer -- using a newer C++ wrapper
- 02-MySaw -- introduces multiple calculation functions and state variables
- 03-AnalogEcho -- introduces memory allocation and cubic interpolation

## Compiling

This is how you build one of the examples in this directory. The examples are kept separate with duplicated code so that you can simply copy out a directory to start your own ugen. **Currently, this build system is missing two things: Windows and supernova. Sorry, we're working on it...**

Before you can compile any plugin, you will need a copy of the SuperCollider *source code* (NOT the app itself). The source code version should match your SuperCollider app version. Slight differences will probably be tolerated, but if they're too far apart you will get an "API version mismatch" error when you boot the server.

You will **not** need to recompile SuperCollider itself in order to get a plugin working. You only need the source code to get the C++ headers.

CMake dumps a lot of files into your working directory, so you should always start by creating the `build/` directory:

```shell
example-plugins/01a-BoringMixer/$ mkdir build
example-plugins/01a-BoringMixer/$ cd build
```
Next, we run CMake and tell it where the SuperCollider headers are to be found (don't forget the `..`!):

```shell
example-plugins/01a-BoringMixer/build/$ cmake -DSC_PATH=/path/to/sc3source/ ..
```

Here, `/path/to/sc3source/` is the path to the source code. Once again, this is the *source code*, not the app itself.

The path should contain a file at `include/plugin_interface/SC_PlugIn.h`. If you get a warning that `SC_PlugIn.h` could not be found, then `SC_PATH` is not set correctly. If no `SC_PATH` is provided, the build system assumes the SuperCollider include files in `/usr/include/SuperCollider/`.

CMake will remember your `SC_PATH`, so you only need to run that once. After that, simply build using `make`:

```shell
example-plugins/01a-BoringMixer/build/$ make
```

This will produce a "shared library" file ending in `.scx`. On Linux, the extension is `.so`.

## Installing

You can install each folder -- or the entire repository -- as you would a quark: `Quarks.gui` => `Install a folder`.

Alternatively, you can copy, move, or symbolic link the folder into your Extensions folder. You can find out which one that is by evaluating `Platform.userExtensionDir` in sclang. You can install the plugin(s) system-wide by copying to `Platform.systemExtensionDir`.

If you're not using sclang, the installation method varies. Ask the developer(s) of the client if you're not sure how.

## Development workflow

If you change your source file(s) or `CMakeLists.txt`, simply use `make` to recompile the shared library. You will need to restart scsynth/supernova for your changes to take effect.

If you change your `.sc` class file, you will need to restart sclang.
