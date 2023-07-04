# Game-of-Life

Hello, welcome to the game of life!

    This is a game that is played by itself and follows certain rules...
    Let me explain!
    
    The game works as follows:
    1. Any live cell with fewer than two live neighbors dies due to loneliness.
    2. Any live cell with more than three live neighbors dies due to overpopulation.
    3. Any dead cell with exactly three live neighbors becomes a live cell.
    4. Any cell with two live neighbors remains in the same state for the next generation.

   Before running the game, make sure you have the following files available:
   - estado0.vid
   - estado1.vid
   - estado2.vid

   These files contain initial configurations for the Game of Life. If you don't have them,
   you can create your own files following the format specified below.

   File Format:
   - The first line should contain the number of rows in the matrix.
   - The second line should contain the number of columns in the matrix.
   - The following lines should represent the matrix itself, where each character (0 or 1)
     represents a cell state. '0' represents a dead cell, and '1' represents a live cell.

   Example File (estado0.vid):
   5
   5
   00000
   00100
   01010
   00100
   00000

   Example File (estado1.vid):
   3
   3
   111
   010
   111

   Example File (estado2.vid):
   4
   4
   1001
   0110
   0110
   1001

   Once you have the desired file, specify its name when prompted to choose a file in the program.

   Enjoy the Game of Life! Created by: Rafael Olivare Piveta - Computer Engineer
