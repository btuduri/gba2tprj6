#include "../headers/gba.h"
#include "../headers/gba_sprites.h"
#include "../headers/ai.h"
#include "../headers/interface.h"
#include "../headers/maps.h"			// maps header file

Sprite  space_ship, UFO, bullet;


/**
 * Load all AI tiles into memory
 */
void initialize_ai() {

	// Load 256 colors in the palette memory
	u16 loop;
	for(loop = 0; loop < 256; loop++)
		OBJPaletteMem[loop] = ShipPal[loop];	

	// start of spaceship
	space_ship.x = 100;
	space_ship.y = 100;

	// start of UFO
	UFO.x = 20;
	UFO.y = 20;
	
	// specify offsets and index of sprite in OAM array.
	space_ship.OAMSpriteNum = 10;
	UFO.OAMSpriteNum = 11;
	bullet.OAMSpriteNum = 12;
	
	update_sprite( UFO, 416 );
	update_sprite( space_ship, 352 );
	
	
	for(loop = 5632; loop < 6144; loop++)
		OAMData[loop] = ShipTiles[loop-5632];		
		
	for(loop = 6144; loop < 6656; loop++)
		OAMData[loop] = bulletTiles[loop-6144];
		
	for(loop = 6656; loop < 7168; loop++)
		OAMData[loop] = UFOTiles[loop-6656];

}


/**
 * Update specific sprite on the place
 */
void update_sprite( Sprite s, u16 tiles ) {

  	sprites[s.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | s.y;
	sprites[s.OAMSpriteNum].attribute1 = SIZE_32 | s.x;
	sprites[s.OAMSpriteNum].attribute2 = tiles;

}


/**
 * this function starts bullet
 */
void fire_bullet(){
		if(bullet.y >= 138){
			bullet.y = -2;
			bullet.x = -2;
			
			update_sprite( bullet, 384 );

			bullet.x = space_ship.x + 3;
			bullet.y = space_ship.y - 24;
		}
}


/**
 * this function handles the ai; spawning enemies, etc.
 */
void track_ai() {
	if(UFO.x >= 200){
		UFO.x = 10;
		UFO.y = UFO.y+20;
	}
	if(get_score()%20==0 && UFO.y!=20){
		UFO.y=20;
		UFO.x=20;
	
	}
	if(UFO.y+20 >= space_ship.y && UFO.x+10 >= space_ship.x && UFO.x-10 <= space_ship.x){
		set_health( get_health() - 1 );
		UFO.y=20;
		UFO.x=20;
	}
	UFO.x++;
	update_sprite( UFO, 416 );
}


/**
 * this function handles the bullet.
 */
void track_bullet() {
	if( bullet.y >= 0 ) {
		bullet.y = bullet.y - 2;
		update_sprite( bullet, 384 );
	}
	if( bullet.x+10 >= UFO.x &&	bullet.x-10 <= UFO.x && bullet.y == UFO.y ) {
			bullet.y = -2;
			bullet.x = -2;
			
			update_sprite( bullet, 384 );
			
			set_score( get_score() + 1 );
	}
}