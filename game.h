#ifndef GAME_H
#define GAME_H

#define  ROWS (6)
#define  COLS (12)

typedef struct
{
    int x, y;
    int strenght;
} Guard;

typedef struct
{
    int x, y;
} Item;

typedef struct
{
    int x, y;
    int strentgh;
    int health;
} Creature;

typedef struct
{
    int row;
    int col;
    Item *item;
    Creature *creature;
    Guard *guard;
    char map[ROWS][COLS];
    char* description;
    int creatureCount;

    char name[50];
} Room;

typedef struct
{
    int x;
    int y;
    int health;
    int strength;
    Item *inventory;
    int inventoryCount;
    int lastInventoryIndex;
    Room *room;
} Player;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Directions;



void startGame(Player* player);
void fillRooms(Room* room);
void createDungeonRoom(Player* player);
void displayDungeonRoom(Room* room);
void displayRooms(Room* rooms[], int roomCount);
void createMap(Room* room);
void displaySpecificRoom(Room* room);
void putCreatureandItems(Room* room);
void movePlayer(Player* player, const char* direction);
void changeRoom(Player* player);
void pickupItem(Player* player);
void attack(Player *player);
void erase(Room* room, int row, int col);
void updateCell(int x, int y, char symbol);
void takeMoveCommand(Player* player, Room* room);
void saveGame(Player* player, const char* filepath);
void loadGame(Player* player, const char* filepath);





#endif
