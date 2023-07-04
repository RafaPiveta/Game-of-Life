#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/*
   Game of Life - File-based Initialization

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
*/

// Function to allocate dynamic memory for a matrix
void allocateMatrix(int ***matrix, int row, int column) {
    *matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        (*matrix)[i] = (int *)malloc(column * sizeof(int));
    }
}

// Function to free the allocated memory for a matrix
void freeMatrix(int ***matrix, int row) {
    for (int i = 0; i < row; i++) {
        free((*matrix)[i]);
    }
    free(*matrix);
    *matrix = NULL;
}

// Function to update the matrix based on the rules of the game of life
void updateMatrix(int **initial_matrix, int **new_matrix, int row, int column, int *counter_alive) {
    int i, j, k, l;
    int counter;

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            counter = 0;

            // Check the neighbors of the cell
            for (k = i - 1; k <= i + 1; k++) {
                for (l = j - 1; l <= j + 1; l++) {
                    if (k >= 0 && k < row && l >= 0 && l < column && !(k == i && l == j) && (initial_matrix[k][l] == 1)) {
                        counter++;
                    }
                }
            }

            if (initial_matrix[i][j] == 1) {
                // Rules for live cells
                if (counter < 2 || counter > 3) {
                    new_matrix[i][j] = 0;
                } else {
                    new_matrix[i][j] = 1;
                }
            } else {
                // Rules for dead cells
                if (counter == 3) {
                    new_matrix[i][j] = 1;
                } else {
                    new_matrix[i][j] = 0;
                }
            }
        }
    }

    *counter_alive = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if (initial_matrix[i][j] == 1) {
                (*counter_alive)++;
            }
        }
    }

    // Update the initial matrix with the updated matrix
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            initial_matrix[i][j] = new_matrix[i][j];
        }
    }
}

// Function to print the matrix on the screen
void printMatrix(int **matrix, int row, int column) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if (matrix[i][j] == 1) {
                printf("\033[31m%c \033[0m", 254); // Paint the alive elements red
            } else {
                printf("%c ", 32); // Use the ASCII table to make the dead elements invisible
            }
        }
        printf("\n");
    }
}

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // Clear screen on Windows
#else
    system("clear"); // Clear screen on Linux
#endif
}

int main() {
    int row, column;
    int i, j, k, l;
    int generation, numGeneration;
    int counter, counter_alive;
    char response[100];

    int **initial_matrix;
    int **new_matrix;

    printf("Hello, welcome to the game of life!\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("This is a game that is played by itself and follows certain rules...\n");
    printf("Let me explain!\n\n");
    printf("The game works as follows: \n");
    printf("1. Any live cell with fewer than two live neighbors dies due to loneliness.\n");
    printf("2. Any live cell with more than three live neighbors dies due to overpopulation.\n");
    printf("3. Any dead cell with exactly three live neighbors becomes a live cell.\n");
    printf("4. Any cell with two live neighbors remains in the same state for the next generation.\n\n");
    printf("First of all, which file do you want to open? We have three options: \n\n");
    printf("estado0.vid \n");
    printf("estado1.vid \n");
    printf("estado2.vid \n\n");
    scanf("%s", response);
    clearScreen();

    // Read which file the user wants
    FILE *pFile;
    char fileRow[100];
    char fileName[100];

    if (strcmp(response, "estado0.vid") == 0) {
        strcpy(fileName, "estado0.vid");
    } else if (strcmp(response, "estado1.vid") == 0) {
        strcpy(fileName, "estado1.vid");
    } else if (strcmp(response, "estado2.vid") == 0) {
        strcpy(fileName, "estado2.vid");
    } else {
        printf("Nonexistent or corrupted file.");
        return 1;
    }

    pFile = fopen(fileName, "r");

    if (pFile == NULL) {
        printf("File doesn't exist or is corrupted");
        exit(1);
    } else {
        fgets(fileRow, 100, pFile); // Get the number of rows in the file
        row = atoi(fileRow);

        fgets(fileRow, 100, pFile); // Get the number of columns in the file
        column = atoi(fileRow);

        printf("Okay, you have chosen %s. The chosen file has %d rows and %d columns...\n\n", response, row, column);

        // Dynamically allocate memory for the matrices
        allocateMatrix(&initial_matrix, row, column);
        allocateMatrix(&new_matrix, row, column);

        // Read the matrix from the file
        for (int i = 0; i < row; i++) {
            fgets(fileRow, 100, pFile);
            for (int j = 0; j < column; j++) {
                initial_matrix[i][j] = fileRow[j] - '0'; // Convert character to integer
            }
        }

        printf("Now, I have to ask... How many generations do you want? ");
        scanf("%d", &numGeneration);

        // Run the game for the specified number of generations
        for (generation = 0; generation < numGeneration; generation++) {
            updateMatrix(initial_matrix, new_matrix, row, column, &counter_alive);
            clearScreen();
            printf("Generation: %d\n", generation);
            printMatrix(initial_matrix, row, column);
            printf("Number of alive cells: %d\n", counter_alive);
            Sleep(250); // Pause for a short duration between generations
        }

        // Free the allocated memory
        freeMatrix(&initial_matrix, row);
        freeMatrix(&new_matrix, row);
        return 0;
    }
}
