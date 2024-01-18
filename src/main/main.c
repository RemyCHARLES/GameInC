#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

#define ROWS 10
#define COLS 10

// Enum for different cell types
typedef enum {
    WALL, PATH, TREASURE, MONSTER, PLAYER
} CellType;

// Structure for a maze cell
typedef struct {
    CellType type;
    char display; // Character to display in the maze
} Cell;

// Structure for the player
typedef struct {
    int x, y; // Position
    int health;
} Player;

// Function prototypes
void initializeMaze(Cell maze[ROWS][COLS]);
void printMaze(const Cell maze[ROWS][COLS]);
void movePlayer(Cell maze[ROWS][COLS], Player *player, int dx, int dy);
void gameLoop(Cell maze[ROWS][COLS], Player *player);

int main() {
    Cell maze[ROWS][COLS];
    Player player = { .health = 100, .x = 0, .y = 0 };

    initializeMaze(maze);
    gameLoop(maze, &player);

    return 0;
}

void initializeMaze(Cell maze[ROWS][COLS]) {
    // Example initialization - replace with your maze design or generation logic
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            maze[i][j].type = PATH;
            maze[i][j].display = ' '; // Space for paths
        }
    }

    // Set walls, treasures, monsters, and player
    maze[0][0].type = PLAYER;
    maze[0][0].display = '@';
    // ... Set other cells accordingly
}

void printMaze(const Cell maze[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            putchar(maze[i][j].display);
        }
        putchar('\n');
    }
}

void movePlayer(Cell maze[ROWS][COLS], Player *player, int dx, int dy) {
    // Check if the new position is within the maze bounds and not a wall
    int newX = player->x + dx;
    int newY = player->y + dy;

    if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS && maze[newY][newX].type != WALL) {
        // Update player position in the maze
        maze[player->y][player->x].display = ' '; // Clear old position
        player->x = newX;
        player->y = newY;
        maze[newY][newX].display = '@'; // Update new position
    }
}

void gameLoop(Cell maze[ROWS][COLS], Player *player) {
    char input;
    int isGameOver = 0;

    while (!isGameOver) {
        system("cls"); // Clear the console
        printMaze(maze);

        input = _getch(); // Get user input

        switch (input) {
            case 'w':
            case 'W':
                movePlayer(maze, player, 0, -1);
                break;
            case 's':
            case 'S':
                movePlayer(maze, player, 0, 1);
                break;
            case 'a':
            case 'A':
                movePlayer(maze, player, -1, 0);
                break;
            case 'd':
            case 'D':
                movePlayer(maze, player, 1, 0);
                break;
            case 'q':
            case 'Q':
                isGameOver = 1;
                break;
            // Add more cases as needed
        }

        // Check for game win/lose conditions
        // ...
    }
}
