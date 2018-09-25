# Nibbler
42 project made with Jimmy Chen Ma

# Objective
Create a Snake-like game in C++ with at least 3 different GUIs. These GUIs being shared libraries.

# Project's Constraints
The project must follow the following constraints:
- Since the GUIs are shared libraries the user must be able to switch between GUI seamlessy while in game.
- The game logic must be unaware of which one of the GUI is loaded. Therefore an interface must be created so that each GUI can be called with the same function name and arguments.
- None of the game logic must be in any of the GUI interfaces. Thus the game main loop must be in an indipendent section of the code, from which calls to input treatment and GUI display will take place.

# Game Requirements
The 3 GUI are GLFW, SDL and SFML. The first time the project is cloned we reccomend to run "make install", this command will make sure that all dependencies are installed (make sure that brew is installed beforehand) and will copy header files in the project include folder.
Then a simple "make" command will compile all 3 dynamic libraries + the main program.

# How to launch
$> ./nibbler [-option1] [-option2] map_width map_height

Available options:
- -w  ->  disable wall collision
- -p  ->  two player game
- -o  ->  enable obstacles

# How to play
Use following keys to change GUI:
- '1' for GLFW
- '2' for SDL
- '3' for SFML

Move snake with WASD keys.

Move second snake with Arrow keys.

Close game at any moment with '0'.

# Disclaimer
We do not own any of the assets used for this game, all ownership and credit goes to the respective creators. 
