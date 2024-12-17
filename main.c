#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"


int main(void)
{
    Player* player = malloc(sizeof(Player));
    Room* pl_room = malloc(sizeof(Room));
    memset(pl_room, 0, sizeof(Room));
    memset(player, 0, sizeof(*player));
    player->room = pl_room;
    player->x = ROWS / 2;
    player->y = COLS / 2;
    // Odaları oluştur

    startGame(player);

    displaySpecificRoom(player->room); // İlk odayı göster

    char command[30];
    while (1)
    {
        printf("Enter your command (move up/down/left/right, change room, save <file>, load <file"
               ", exit): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // \n karakterini kaldır

        if (strncmp(command, "move ", 5) == 0)
        {
            char* direction = command + 5; // "move " sonrası yön
            direction[strcspn(direction, "\n")] = 0;
            movePlayer(player, direction);
        }
        else if (strcasecmp(command, "change room") == 0)
        {
            changeRoom(player);
        }
        else if (strcasecmp(command, "exit") == 0)
        {
            exit(0);
        }
        else if (strcasecmp(command, "save") == 0)
        {
            char* filepath = "C:/Users/Reyyan Naz/CLionProjects/CGame/savingGames";
            saveGame(player, filepath);
        }
        else if (strcasecmp(command, "load") == 0)
        {
            char* filepath = "C:/Users/Reyyan Naz/CLionProjects/CGame/savingGames";
            loadGame(player, filepath);
            displaySpecificRoom(player->room);
        }
        else
        {
            printf("Invalid command!\n");
        }
    }
}
