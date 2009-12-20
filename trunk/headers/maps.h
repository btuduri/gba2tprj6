/**
 * Keeper of the necessary level header/sources.
 *
 * @date	11/12/09
 * @author  Wouter van Teijlingen
 * @email	wouter@0xff.nl
 */

#ifndef MAPS_HEADER
#define MAPS_HEADER

#include "../levels/level1/sprites/bullet.h" 
#include "../levels/level1/sprites/Ship.h" 	// space_ship sprite
#include "../levels/level1/sprites/UFO.h"
#include "../levels/level1/map/Spacemap.h" 		// space map

typedef struct Map {
	void* level_palette;
	void* level_tiles;
	void* level_map;
	void* level_sprite_palette;
	void* level_sprites;
	u16 size_of_sprites;
	u32 score;
	u16 damage;
} Map;

#endif