#include "main.h"
#define BOG 4
#define WATER 2

/*
--NOTE FOR CONVENTION:
----x is left/right (east west)
----y is up/down (north south)
*/

int move_player(char *query, Player *player, Map *map)
{
	int max = map->size - 1;
	int energymessage = 0;

	// Check which coordinate to update.
	if(strcmp(query, "N") == 0) {
		++player->y;
	}
	else if(strcmp(query, "S") == 0) {
		--player->y;
	}
	else if(strcmp(query, "E") == 0) {
		++player->x;
	}
	else if(strcmp(query, "W") == 0) {
		--player->x;
	}

	// Check x bounds
	if(player->x > max) {
		player->x = 0;
	}
	else if(player->x < 0) {
		player->x = max;
	}

	// Check y bounds
	if(player->y > max) {
		player->y = 0;
	}
	else if(player->y < 0) {
		player->y = max;
	}

	// Decrement energy due to movement

	//--player->energy;
	energymessage = decrementenergy(player,map);
	
	// Make the tile visible (Needs to be expanded to show player's vision

	map->tiles[player->x ][player->y ].visibility = 1;

	viewTiles(player, map);
	return energymessage;
}

int viewTiles(Player *player, Map *map)
{
	int viewRange = player->visibility;
	int map_range = map->size;
	
	for (int i = -viewRange; i <= viewRange; i++)
	{
		for (int j = -viewRange; j<= viewRange; j++)
		{
			if( (player->x)+i >= 0 && (player->y)+j >= 0 && (player->y)+j < map_range && (player->x)+i < map_range)
			{
				map->tiles[player->x + i][player->y + j ].visibility = 1;
			}
		}
	} 
	return 1;	
}
int decrementenergy(Player* player, Map* map)
{
	//going to add checks for water and treasure chests here. 
	if(map->tiles[player->x][player->y].terrain == BOG)
	{
		(player->energy) -= 2;
		return 2;
	}
	else
	{
		--player->energy;
		return 1;
	}
	
} 



