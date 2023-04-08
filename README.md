# Phy6

An open-source simulator electric charges and electric fields constrained 
within a 2-dimensional plane

[![](https://img.shields.io/static/v1?label=C-Programming&message=&color=blue&logo=github)](https://github.com/aadit-n3rdy/phy6)
[![](https://img.shields.io/static/v1?label=CMake&color=blue&logo=github)](https://github.com/aadit-n3rdy/phy6)
[![](https://img.shields.io/static/v1?label=AadityaE&message=phy6-electrostatic-simulator&color=blue&logo=github)](https://github.com/aadit-n3rdy/phy6)
[![](https://img.shields.io/static/v1?label=AadityaE&message=phy6-electrostatic-simulator&color=blue&logo=github)](https://github.com/aadit-n3rdy/phy6)


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

## Credits and Contributors

<!-- Displays the list of contributors to the project. -->
<a href = "https://github.com/aadit-n3rdy/phy6/contributors">
    <img src = "https://contrib.rocks/image?repo=aadit-n3rdy/phy6"/>
</a>

All forms of contributions are welcomed!
