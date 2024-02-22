<h1>3D Maze project</h1>

The 3D Maze Project aimed to create an immersive and interactive maze exploration experience using 3D graphics using SDL2, offering a combination of entertainment and algorithmic challenges.
The Maze was written in C using SDL2 library.
Deveploment was performed using window 10 gcc (MinGW.org GCC-6.3.0-1) 

<h3>SDL2</h3>
Simple DirectMedia Layer is a cross-platform software development library designed to provide a hardware abstraction layer for computer multimedia hardware components.

<h3>Instalation</h3>
git clone https://github.com/ChaymaeOuh/3D_Maze.git

<h3>Compilation</h3>
gcc main.c -o maze -IC:/SDL2/include -LC:/SDL2/lib -lSDL2main -lSDL2

<h3>Running</h3>
After the compilation, run the program using the command 
./maze MAP

<h3>The Project Controls</h3>
W: Move forward.

S: Move backward.

A: Rotate left.

D: Rotate right.

Mouse movement left/right: Adjust your view to the left or right.

M: Disable the map display. Clicking won't show the 2D map.

N: Enable the map display. The 2D map will become visible once more if it was hidden.


<h3>The Project Directories</h3>
headers: All the header files are in here.

images: This contains all image files.

maps: This will be used by the program to output the map layout using the data map files

src: All the source code files written in C are in this folder.

<h3>Author</h3>
 OUHROUCH Chaymae 

 <h3>The 3D Maze Game Project Demo</h3>
 https://youtu.be/Hv_acdqMg7E