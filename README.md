# roguelike
### A basic roguelike written in C++
Olle Lögdahl, 24 November 2018

<!--![release](https://img.shields.io/github/v/release/ollelogdahl/roguelike) -->
![cmake](https://img.shields.io/github/workflow/status/ollelogdahl/roguelike/CMake?label=Build)
![licence](https://img.shields.io/github/license/ollelogdahl/roguelike)
![issues](https://img.shields.io/github/issues-raw/ollelogdahl/roguelike)

---
**roguelike** is a C++ game, inspired by rogue and NetHack. Implements a custom engine, xml resource loading, texture atlasing, dungeon generation and more.

<p align="center">
<img src="https://github.com/ollelogdahl/roguelike/blob/master/media/dungeon.png">
</p>

**NOTE**: This project is in the middle of a major rework, and is therefore broken. Come back later :)

## Installation Guide
*Note: Only tested on linux. My codebase should be platform independent, but would need some tweaks to the cmake script.*
```bash
git clone https://github.com/ollelogdahl/roguelike.git
cd roguelike
mkdir build
cd build
cmake .. && make -j4
```

## Dependencies
 * [SDL2](https://www.libsdl.org/download-2.0.php)
 * [SDL2 - Image](https://www.libsdl.org/projects/SDL_image/)
 * [pugixml](https://pugixml.org/)
