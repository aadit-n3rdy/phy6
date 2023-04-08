# Phy6

An open-source simulator electric charges and electric fields constrained 
within a 2-dimensional plane

[![](https://img.shields.io/static/v1?label=C/Cpp&message=programming&color=black&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![](https://img.shields.io/static/v1?label=CMake&message=compilation&color=green&logo=cmake)](https://cmake.org/)

## Table of Contents
- [Synopsis](#synopsis)
- [Build Instructions](#build-instructions)
- [Usage](#usage)
- [License](#license)
- [Libraries Used](#libraries-used)
- [Credits and Contributors](#credits-and-contributors)

## Synopsis

This project is intended to get a more intuitive grasp of electrostatics, especially
the concepts that would be covered in a undergrad course on computer science. No
complicated algorithms have been used, the project works completely based on
calculating forces and displacements over very small timesteps.

## Build Instructions

- Install the SDL2 library
- Use CMake to build the project and run the executable
```cmake
cmake -B build
cmake --build build
```

## Usage

- The only argument is the path to the JSON file to parse for input.
- If no argument is given, the `examples/simple.json` is loaded.
- Use UP and DOWN arrow keys to zoom in and out, and W-A-S-D to move the camera around

## Libraries Used

- SDL2 for graphics and windows excluding UI [https://github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL)
- cJSON for loading configs from files [https://github.com/DaveGamble/cJSON](https://github.com/DaveGamble/cJSON)
- sdl2-cmake-modules, for easy loading of SDL2 libraries [https://gitlab.com/aminosbh/sdl2-cmake-modules](https://gitlab.com/aminosbh/sdl2-cmake-modules)
- SDL_FontCache for text rendering [https://github.com/grimfang4/SDL_FontCache](https://github.com/grimfang4/SDL_FontCache)
- VT323 Font by Peter Hull (obtained from Google Fonts) [https://fonts.google.com/specimen/VT323](https://fonts.google.com/specimen/VT323)

## Credits and Contributors

<!-- Displays the list of contributors to the project. -->
<a href = "https://github.com/aadit-n3rdy/phy6/contributors">
    <img src = "https://contrib.rocks/image?repo=aadit-n3rdy/phy6"/>
</a>

All forms of contributions are welcomed!
