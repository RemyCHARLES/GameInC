#include "map.h"
#include <stdlib.h>

#define MAP_SIZE 10
Room map[MAP_SIZE][MAP_SIZE];

void initializeMap() {
    for (int x = 0; x < MAP_SIZE; x++) {
        for (int y = 0; y < MAP_SIZE; y++) {
            Room room;
            room.type = rand() % 4; // Random room type
            map[x][y] = room;
        }
    }
}

Room getRoom(int x, int y) {
    return map[x][y];
}

// Additional function implementations
