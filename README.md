This is a minimal example of a SuperCollider server plugin. It compiles a "MySaw" ugen, which is a simple saw oscillator with controllable frequency and initial phase.

## Compiling

Make a directory for the `cmake` build files:

```shell
plugin-example/$ mkdir build && cd build
plugin-example/build/$ cmake -DSC_PATH=/path/to/sc3source/ ..
```

If no `SC_PATH` is provided the build system assumes the SuperCollider include files in `/usr/include/SuperCollider/`.

```shell
plugin-example/build/$ make
plugin-example/build/$ make install
```

On OSX, the plugins will end up in `sc3-plugins/build/SC3plugins`.

WARNING: on OSX, if you want to install into `CMAKE_INSTALL_PREFIX`, you have to specify it by disabling the `IN_PLACE_BUILD` cmake option which defaults to ON (see below).

## Installing

Copy the `SC3plugins` folder to your Extensions folder. You can find out which one that is by evaluating

```
Platform.userExtensionDir
```

from within SuperCollider. Alternatively, you may install the extensions system-wide by copying to

```
Platform.systemExtensionDir
```

Tip: On OSX and Linux, it might be more convenient to use a symbolic link rather than copying or moving the directory.