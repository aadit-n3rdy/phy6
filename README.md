# Phy6

A small project to simulate electric charges and electric fields constrained on a 2D plane

## Introduction

This project is intended to get a more intuitive grasp of electrostatics, especially
the concepts that would be covered in a undergrad course on computer science. No
complicated algorithms have been used, the project works completely based on
calculating forces and displacements over very small timesteps.

## Build Instructions

- Install the SDL2 library
- Use CMake to build the project and run the executable

## Basic Usage

- The only argument is the path to the JSON file to parse for input.
- If no argument is given, the examples/simple.json is loaded

## Libraries Used

- SDL2 for graphics and windows excluding UI [https://github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL)
- cJSON for loading configs from files [https://github.com/DaveGamble/cJSON](https://github.com/DaveGamble/cJSON)

