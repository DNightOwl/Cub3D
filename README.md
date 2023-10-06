# Cub3D

## Introduction
The cub3D is a 42 School graphic design project inspired by the famous game Wolfenstein 3D. The project is a simple raycasting game engine, that includes several features like the implementation of the sprites and the ability to take a screenshot without running the game.
The project is using the [miniLibX](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html) library.

[Project subject](https://github.com/DNightOwl/Cub3D/blob/main/subject.en.pdf)

## Getting Started
To compile and run cub3D, follow these steps:

### Prerequisites
-  A Unix-like operating system (macOS or Linux)
The makefile can detect the currently running operating system and will compile it with the needed libraries.
-  Make sure you have the `gcc` compiler installed.

    MacOS:
    -  since the project is using MiniLibX ,it requires Cocoa of MacOSX (AppKit) and OpenGL
    
    Linux:
    -  MiniLibX for Linux requires xorg, x11 and zlib , therefore you will need to install the following dependencies: xorg, libxext-dev and zlib1g-dev:
    ```
    sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
    ```

### Compilation
1. Clone this repository to your local machine.
   ```
   git clone https://github.com/DNightOwl/Cub3D.git
   ```
   ```
    cd cub3D
   ```


3. Build the project by running `make`.

   make

### Running cub3D
You can run cub3D with the following command:
```
./cub3D path-map-file.cub
```
