This repository a series of examples demonstrating how to write server plugins for [SuperCollider](https://github.com/supercollider/supercollider) (not to be confused with quarks, which are libraries for the language).

Beyond this repository, the reader is encouraged to look at [sc3-plugins](https://github.com/supercollider/sc3-plugins) for more complex, real-world examples.

## Compiling

Make a directory for the `cmake` build files:

```shell
plugin-example/01-BoringMixer/$ mkdir build && cd build
plugin-example/01-BoringMixer/build/$ cmake -DSC_PATH=/path/to/sc3source/ ..
```

If no `SC_PATH` is provided the build system assumes the SuperCollider include files in `/usr/include/SuperCollider/`.

```shell
plugin-example/01-BoringMixer/build/$ make
plugin-example/01-BoringMixer/build/$ make install
```

WARNING: on OSX, if you want to install into `CMAKE_INSTALL_PREFIX`, you have to specify it by disabling the `IN_PLACE_BUILD` cmake option which defaults to ON (see below).

## Installing

Copy the folder you want to install to your Extensions folder. You can find out which one that is by evaluating

```
Platform.userExtensionDir
```

from within SuperCollider. Alternatively, you may install the extensions system-wide by copying to

```
Platform.systemExtensionDir
```

Tip: On OSX and Linux, it might be more convenient to use a symbolic link rather than copying or moving the directory.
