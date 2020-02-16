# TalChorus

TalChorus is the chorus part of [TAL-NoiseMaker](https://tal-software.com/products/tal-noisemaker) extracted as a standalone VST plugin. This makes it similar to [TAL-Chorus-LX](https://tal-software.com/products/tal-chorus-lx) but this is not available for Linux, to I extracted the chorus from the open source NoiseMaker instead.

## Download releases

The plugin is only built for linux at the moment and only the VST version has been tested. The release can be downloaded from [here](https://github.com/soerenbnoergaard/talchorus/releases).

## Compiling the plugin

Initialize the git submodules:

    git submodule init
    git submodule update

Go to the `src/TalChorus` directory and compile the plugin:

    make

