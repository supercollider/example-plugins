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

This is how you build one of the examples in this directory. The examples are kept separate with duplicated code so that you can simply copy out a directory to start your own ugen (see [Development workflow](#development-workflow)). **Currently, this build system is missing Windows. Sorry, we're working on it...**

### Step 1: Obtain header files

Before you can compile any plugin, you will need a copy of the SuperCollider *source code* (NOT the app itself). 
Source code tarballs can be downloaded from the [SuperCollider release page](https://github.com/supercollider/supercollider/releases). If you are on Linux, it's okay (and preferable) to use the Linux source tarball.

You will **not** need to recompile SuperCollider itself in order to get a plugin working. You only need the source code to get the C++ headers.

The source code version should roughly match your SuperCollider app version. This is due to occasional breaking changes in the plugin "API" (technically the ABI), which will occur only in 3.x releases. These breaking changes will not require modification to your plugin's source code, but compiled plugin binaries will need to be recompiled. If the server tries to load an incompatible plugin, it will give the "API version mismatch" error message.

### Step 2: Create build directory and set `SC_PATH`

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

To make sure you have the right path, check to ensure that it contains a file at `include/plugin_interface/SC_PlugIn.h`. If you get a warning that `SC_PlugIn.h` could not be found, then `SC_PATH` is not set correctly.

CMake will remember your `SC_PATH`, so you only need to run that once per plugin.

### Step 3: Set flags (optional)

If you don't plan on using a debugger, it's advisable to build in release mode so that the compiler optimizes:

```shell
example-plugins/01a-BoringMixer/build/$ cmake -DCMAKE_BUILD_TYPE=RELEASE ..
```

Switch back to debug mode with `-DCMAKE_BUILD_TYPE=DEBUG`.

If you also want to build the UGen for Supernova, then you need to set the 'SUPERNOVA' flag:

```shell
example-plugins/01a-BoringMixer/build/$ cmake -DSUPERNOVA=ON ..
```

Again, all these flags are persistent, and you only need to run them once. If something is messed up, you can trash the `build/` directory and start again.

### Step 4: Build it!

After that, make sure you're in the build directory, and call `make`:

```shell
example-plugins/01a-BoringMixer/build/$ make
```

This will produce a "shared library" file ending in `.scx`. On Linux, the extension is `.so`.

You can freely alternate between steps 3 and 4. If you decide to go back and change some CMake flags, just hit `make` again.

## Installing

Copy, move, or symbolic link the folder into your Extensions folder. You can find out which one that is by evaluating `Platform.userExtensionDir` in sclang. You can install the plugin(s) system-wide by copying to `Platform.systemExtensionDir`.

Please note that on macOS Supernova is more picky about location of UGens (as of January 2018). They need to be placed in a subdirectory called `plugins` inside the above mentioned Extensions folder. This pertains only to the UGen file (`.scx`), not the `.sc` class file.

If you're not using sclang, the installation method varies. Ask the developer(s) of the client if you're not sure how.

## Development workflow

In order to start developing a new UGen, make a copy of one of the example's directory. Change the `.cpp` filename, as well as the name and contents of the corresponding `.sc` file, and update the beginning of `CMakeLists.txt` with your new `.cpp` filename. Then you're ready to work on the code. If you are using Git, you may also want to copy over the `.gitignore` in the root of this project.

If you change your source file(s) or `CMakeLists.txt`, simply use `make` to recompile the shared library. You will need to restart scsynth/supernova for your changes to take effect.

If you change your `.sc` class file, you will need to restart sclang.
