#ifndef MAP_H
#define MAP_H

typedef enum { NORMAL, TREASURE, TRAP, TELEPORT } RoomType;

typedef struct {
    RoomType type;
    // Additional room properties
} Room;

void initializeMap();
Room getRoom(int x, int y);
// Other function declarations

#endif


void map_init()
{

}

