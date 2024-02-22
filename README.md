# 3D Maze project
---------------

![maze3](https://github.com/ChaymaeOuh/3D_Maze/assets/101417413/40575f64-9a3d-4514-9ec5-2f91503e8c47)


The 3D Maze Project aimed to create an immersive and interactive maze exploration experience using 3D graphics using SDL2, offering a combination of entertainment and algorithmic challenges.
The Maze was written in C using SDL2 library.
Deveploment was performed using window 10 gcc (MinGW.org GCC-6.3.0-1) 

## SDL2
Simple DirectMedia Layer is a cross-platform software development library designed to provide a hardware abstraction layer for computer multimedia hardware components.

## Instalation
```sh
$ git clone https://github.com/ChaymaeOuh/3D_Maze.git

```
## Compilation
```sh
$ gcc main.c -o maze -IC:/SDL2/include -LC:/SDL2/lib -lSDL2main -lSDL2

```

## Running
After the compilation, run the program using the command 
```sh
$ ./maze MAP

```
where ```MAP``` is the name of the file found in the maps folder.

## The Project Controls

```W```: Move forward.

```S```: Move backward.

```A```: Rotate left.

```D```: Rotate right.

```Mouse movement left/right```: Adjust your view to the left or right.

```M```: Disable the map display. Clicking won't show the 2D map.

```N```: Enable the map display. The 2D map will become visible once more if it was hidden.


## The Project Directories
[`headers`](https://github.com/ChaymaeOuh/3D_Maze/tree/main/headers)

All the header files are in here.

[`images`](https://github.com/ChaymaeOuh/3D_Maze/tree/main/images)

This contains all image files.

[`maps`](https://github.com/ChaymaeOuh/3D_Maze/tree/main/maps)

This will be used by the program to output the map layout using the data map files

[`src`](https://github.com/ChaymaeOuh/3D_Maze/tree/main/src)

All the source code files written in C are in this folder.

## Author
 OUHROUCH Chaymae 

## The 3D Maze Game Project Demo(click :point_down:)
 The Maze Demo
![maze3](https://github.com/ChaymaeOuh/3D_Maze/assets/101417413/40575f64-9a3d-4514-9ec5-2f91503e8c47)(https://youtu.be/Hv_acdqMg7E)
