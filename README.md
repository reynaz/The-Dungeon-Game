# The-Dungeon-Game
İt is a command-line-base game written in c

My game begins at a dungeon room. A guard wait for the player in front of the dungeon room. If the players can defeat the guard they can exit the dungeon room and continue by changing room. Player encounters items and creatures in every room. In such a case player can pick up the items and attack to the creature.

How the winner determined while attacking? 

Player, guard and creatures have strength value in their struct 
The attack method compares their strength. The one who has bigger strength wins.
In the beginning, the player is guaranteed to have more strength value


> Game asks for command from the user, the input is then analyzed and processed
The valid commands:
Move up/down/right/left
Change room
Save
Load
exit
(Commands are analyzed with non-case sensitive comparator)

> attack and pickUp method calls within movePlayer method, movePlayer checks player’s coordinates(x,y) if they equal to any items, guard, creature’s coordinates(x,y) so, if player encounters with guards and creature player attack automatically; with items player pick up the item automatically also.
> Rooms are dynamically allocated in memory and every time the player changes rooms, the previous room is deleted from memory and space is allocated for the new room.

> Player, Creature, item are also allocated in memory in createMap method.

> User can save and load current game state. 
