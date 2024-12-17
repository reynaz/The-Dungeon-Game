#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"


#define BORDERS '_'
#define SPACE ' '
#define GUARD 'G'
#define CREATURE '&'
#define PLAYER 'P'
#define DIAMOND '*'
#define STRENGTH '%'


void startGame(Player* player)
{
    printf("Starting game ...\n");
    printf("YOU ARE IN THE DUNGEON ROOM\n");
    printf("IF YOU DEFEAT THE GUARD YOU CAN EXIT THE DUNGEON\n\n");
    player->room->guard = (Guard*)malloc(sizeof(Guard));
    player->room->guard->strenght = 9;
    player->room->creature = (Creature*)malloc(sizeof(Creature));
    player->room->item = (Item*)malloc(sizeof(Item));
    player->strength = 10;
    player->health = 10;
    createDungeonRoom(player);
    //createMap(player->room);
}

void createMap(Room* room)
{
    if (room == NULL)
    {
        printf("Memory allocation is failed!!");
        exit(EXIT_FAILURE);
    }
    room->guard = (Guard*)malloc(sizeof(Guard));
    room->item = (Item*)malloc(sizeof(Item));
    room->creature = (Creature*)malloc(sizeof(Creature));
    memset(room->name, 0, sizeof(room->name));
    memset(room->item, 0, sizeof(&room->item));
    memset(room->creature, 0, sizeof(&room->creature));
    fillRooms(room);
    putCreatureandItems(room);
    room->map[ROWS / 2][COLS / 2] = PLAYER;

}

void createDungeonRoom(Player* player)
{
    if (player->room->guard == NULL)
    {
        printf("Memory allocation for guard failed!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
            {
                player->room->map[i][j] = BORDERS;
            }
            else
            {
                player->room->map[i][j] = SPACE; // Emptys
            }
        }
    }
    player->room->guard->x = 2;
    player->room->guard->y = COLS - 2;
    player->room->map[player->room->guard->x][player->room->guard->y] = GUARD;

    player->x = ROWS / 2;
    player->y = COLS / 2;
    player->room->map[player->x][player->y] = PLAYER;
}

void fillRooms(Room* room)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
            {
                room->map[i][j] = BORDERS;
            }

            else
            {
                room->map[i][j] = SPACE; // Emptys
            }
        }
    }
}

void displayDungeonRoom(Room* room)
{
    printf("Dungeon Room:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%c", room->map[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void displayRooms(Room* rooms[], int roomCount)
{
    for (int a = 1; a < roomCount; a++)
    {
        printf("Room %d:\n", a);

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                printf("%c", rooms[a]->map[i][j]);
            }
            printf("\n");
        }

        printf("\n");
    }
}

void displaySpecificRoom(Room* room)
{
    if (room == NULL)
    {
        printf("Room is NULL!\n");
        return;
    }

    printf("Room: %s\n", room->name);
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%c", room->map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void putCreatureandItems(Room* room)
{
    int creatureCount = 0, diamondCount = 0;

    while (creatureCount < 1)
    {
        // 1 yaratık ekle
        int cX = rand() % ROWS;
        int cY = rand() % COLS;

        if (room->map[cX][cY] == SPACE)
        {
            room->creature->x = cX;
            room->creature->y = cY;
            room->map[cX][cY] = CREATURE;
            creatureCount++;
        }
    }

    while (diamondCount < 1)
    {
        int iX = rand() % ROWS;
        int iY = rand() % COLS;

        if (room->map[iX][iY] == SPACE)
        {
            room->item->x = iX;
            room->item->y = iY;
            room->map[iX][iY] = '*'; // Diamond
            diamondCount++;
        }
    }
}

void movePlayer(Player* player, const char* direction)
{
    int newX = player->x;
    int newY = player->y;


    if (strcmp(direction, "up") == 0)
    {
        newX--;
    }
    else if (strcmp(direction, "down") == 0)
    {
        newX++;
    }
    else if (strcmp(direction, "left") == 0)
    {
        newY--;
    }
    else if (strcmp(direction, "right") == 0)
    {
        newY++;
    }
    else
    {
        printf("Invalid direction\n");
    }

    if (newX <= 0 || newX >= COLS || newY <= 0 || newY >= ROWS)
    {
        printf("it is a wall, you can not go further.\n");
        if (newX <= 0)
        {
            newX++;
        } else if (newX == ROWS)
        {
            newX--;
        }
        if (newY <= 0)
        {
            newY++;
        } else if (newY == COLS - 1)
        {
            newY--;
        }
    }


    player->room->map[player->x][player->y] = SPACE;
    player->x = newX;
    player->y = newY;
    player->room->map[player->x][player->y] = PLAYER;
    if (player->room->guard->x == newX && player->room->guard->y == newY)
    {
        attack(player);
        printf("You are now in different room, you can fight with creatures, pick up items or change room");
    }
    if (player->room->creature->x == player->x && player->room->creature->y == player->y)
    {
        attack(player);

    }
    if (player->room->item != NULL)
    {
        if (newX == player->room->item->x && newY == player->room->item->y)
        {
            pickupItem(player);
        }
    }

   displaySpecificRoom(player->room);
}

void changeRoom(Player* player)
{
    Room* pl_room = malloc(sizeof(Room));
    memset(pl_room, 0, sizeof(Room));
    free(player->room);
    player->room = pl_room;

        printf("You have entered different room.\n");

        // to take place in the middle of the new room
        player->x = ROWS / 2;
        player->y = COLS / 2;
        createMap(player->room);

        displaySpecificRoom(player->room);
}

void pickupItem(Player* player)
{
    if (player->x == player->room->item->x && player->y ==  player->room->item->y)
    {
        Item* temp = realloc(player->inventory, (player->inventoryCount + 1) * sizeof(Item));
        if (temp == NULL)
        {
            fprintf(stderr, "Memory allocation is failed!\n");
            exit(EXIT_FAILURE);
        }

        player->inventory = temp;
        player->inventory[player->inventoryCount] = *( player->room->item);
        player->inventoryCount++;
    }
}

void attack(Player* player)
{
    if (player->room->guard->x == player->x && player->room->guard->y == player->y)
    {
        if (player->strength > player->room->guard->strenght)
        {
            printf("\nYOU SUCCESSED TO DEFEAT THE GUARD!!! \n You can exit the dungeon room\n");
            changeRoom(player);
        }
    }
    if (player->room->creature->x == player->x && player->room->creature->y == player->y)
    {
        if (player->strength > player->room->creature->strentgh)
        {
            player->strength--;
            printf("You successed to defeat the creature!!! \n");
            printf("But you got tired, you should change room to pick up some strength\n");
        }
    }
}

void erase(Room* room, int row, int col)
{
    room->map[row][col] = ' ';
}

void updateCell(int x, int y, char symbol)
{
    printf("\033[%d;%dH", y + 1, x + 1);
    printf("%c", symbol);
    fflush(stdout);
}

void takeMoveCommand(Player* player, Room* room)
{
    char command[30];
    printf("Enter the direction (move up, move down, move left, move right): ");
    fgets(command, sizeof(command), stdin);


    if (strncmp(command, "move ", 5) == 0)
    {
        char* direction = command + 5;
        printf(direction);
        direction[strcspn(direction, "\n")] = 0;
        movePlayer(player, direction);
    }
}

void saveGame(Player* player, const char* filepath)
{
    FILE* file = fopen(filepath, "w");
    if (file == NULL)
    {
        fprintf(stderr, "File could not be opened\n");

    }
    fprintf(file, "Player:\n");
    fprintf(file, " %d %d %d\n", player->strength, player->health,player->inventoryCount);

    fprintf(file, "Room:\n");
    fprintf(file, "%d %d\n", ROWS, COLS);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(file, "%c", player->room->map[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Game saved successfully to %s\n", filepath);

}

void loadGame(Player* player, const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File could not be opened\n");
    }
    fscanf(file, "Player:\n");
    fscanf(file, "%d %d %d\n", &player->strength, &player->health, &player->inventoryCount);

    fclose(file);
    printf("Game loaded successfully from %s\n", filepath);

}

