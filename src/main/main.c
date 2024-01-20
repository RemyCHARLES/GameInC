#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAZE_SIZE 15

// Define ASCII Symbols for maze
#define PLAYER_ASCII 'P'
#define KEY_ASCII "K "
#define LOCKED_DOOR_ASCII "- " 
#define TELEPORTER_ASCII "T "
#define SPAWN_ASCII "  "
#define WALL_ASCII "# "
#define PATH_ASCII "  "
#define TRIGGER_DOOR_ASCII "  "
#define TRIGGER_KEY_ASCII "# "

// Define maze symbols
#define KEY 4
#define LOCKED_DOOR 5
#define TELEPORTER 3
#define SPAWN 2
#define WALL 0
#define PATH 1
#define TRIGGER_DOOR 7
#define TRIGGER_KEY 6


// 0 represents a wall, 1 represents a path, 2 for spawn, 3 for teleporter, 4 for treasure, 5 for locked door, 6 trigger to pick up key, 7 trigger to unlock door
int maze[MAZE_SIZE][MAZE_SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 1, 1, 0, 1, 1, 1, 0, 1, 7, 1, 1, 3, 0},
    {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {6, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// Player's initial position
int playerX = 1; // Adjust these values to place the player at the desired starting position
int playerY = 1;
// Variables to track if the player has the key
int hasKey = 0;

char lockedDoorAscii[] = "- "; // ASCII for locked door

void printMaze(int x, int y);
void clearScreen();
int unlockDoor(int x, int y);
int modifyMaze(int x, int y, int oldCharacter);

int main(void)
{
    int x, y;
    char move;
    
    // Set the player's initial position in the maze
    maze[playerX][playerY] = PLAYER_ASCII;
    
    while (1) // Infinite loop to keep the game running
    {
        clearScreen(); // Clear the screen before printing the maze
        printf("\n");
        printMaze(x, y);

        // Get player input for movement
        printf("\nCommands:\n'z' to move up\n's' to move down\n'q' to move left\n'd' to move right\n'x' to exit\n\nWhat is your next move? ");
        scanf(" %c", &move);

        // Clear the player's current position
        maze[playerX][playerY] = 1;

        // Update player's position based on input
        switch (move)
        {
        case 'z': // Move up
            if ((maze[playerX - 1][playerY] != WALL) && (maze[playerX - 1][playerY] != KEY) && (maze[playerX - 1][playerY] != 5)) 
                    playerX--;
            break;
        case 's': // Move down
            if ((maze[playerX + 1][playerY] != WALL) && (maze[playerX + 1][playerY] != KEY) && (maze[playerX + 1][playerY] != 5)) 
                    playerX++;
            break;
        case 'q': // Move left
            if ((maze[playerX][playerY - 1] != WALL) && (maze[playerX][playerY - 1] != KEY) && (maze[playerX][playerY - 1] != 5)) 
                    playerY--;
            break;
        case 'd': // Move right
            if ((maze[playerX][playerY + 1] != WALL) && (maze[playerX][playerY + 1] != KEY) && (maze[playerX][playerY + 1] != 5)) 
                    playerY++;
            break;
        case 'x': // Quit the game
            printf("Game over!\n");
            return 0;
        }

        // Update player's position in the maze
        maze[playerX][playerY] = PLAYER_ASCII;

        // New: Check if the player is on a key
        if ((maze[playerX - 1][playerY] == KEY) || (maze[playerX + 1][playerY] == KEY) || (maze[playerX][playerY - 1] == KEY) || (maze[playerX][playerY + 1] == KEY)) {
            char pickUp;
            printf("You have found a key! Do you want to pick it up? (y/n): ");
            scanf(" %c", &pickUp);
            if (pickUp == 'y' || pickUp == 'Y') {
                hasKey = 1;
                modifyMaze(playerX, playerY, KEY);
                printf("You picked up the key!\n");
                maze[playerX][playerY] = PATH; // Change key cell to a path
            }
        }

        // New: Check if the player is at a locked door and has a key
        if (((maze[playerX + 1][playerY] == LOCKED_DOOR) || (maze[playerX - 1][playerY] == LOCKED_DOOR) || (maze[playerX][playerY - 1] == LOCKED_DOOR) || (maze[playerX][playerY + 1] == LOCKED_DOOR)) && (hasKey == 1)) {
            char openDoor;
            printf("You are in front of a locked door and you have a key. Do you want to unlock it? (y/n): ");
            scanf(" %c", &openDoor);
            if (openDoor == 'y' || openDoor == 'Y') {
                hasKey = 0;
                modifyMaze(playerX, playerY, LOCKED_DOOR);
                printf("You unlocked the door!\n");
            }
        }
    }

    return EXIT_SUCCESS;
}

void printMaze(int playerX, int playerY)
{
    int x, y;
    for (x = 0; x < MAZE_SIZE; x++)
    {
        for (y = 0; y < MAZE_SIZE; y++)
        {
            if (maze[x][y] == PLAYER_ASCII)
            {
                printf("%c ", PLAYER_ASCII);
            }
            else if (maze[x][y] == KEY)
            {
                printf("%s", KEY_ASCII);
            }
            else if (maze[x][y] == LOCKED_DOOR)
            {
                printf("%s", lockedDoorAscii);
            }
            else if (maze[x][y] == TELEPORTER)
            {
                printf("%s", TELEPORTER_ASCII);
            }
            else if (maze[x][y] == SPAWN)
            {
                printf("%s", SPAWN_ASCII);
            }
            else if (maze[x][y] == WALL)
            {
                printf("%s", WALL_ASCII);
            }
            else if (maze[x][y] == PATH)
            {
                printf("%s", PATH_ASCII);
            }
            else if (maze[x][y] == TRIGGER_DOOR)
            {
                printf("%s", TRIGGER_DOOR_ASCII);
            }
            else if (maze[x][y] == TRIGGER_KEY)
            {
                printf("%s", TRIGGER_KEY_ASCII);
            }
        }
        printf("\n");
    }
}


int modifyMaze(int x, int y, int oldCharacter)
{
    for(x = 0; x < MAZE_SIZE; x++)
    {
        for(y = 0; y < MAZE_SIZE; y++)
        {
            if(maze[x][y] == oldCharacter)
            {
                maze[x][y] = 1;
            }
        }
    }
    return 0;
}



void clearScreen()
{
    printf("\033[H\033[J"); // ANSI escape code to clear the screen
}

