/**
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen, Wesley Hilhorst, Sebastiaan Seegers
 * @email	wouter@0xff.nl, wesley.hilhorst@gmail.com, Sseegers@gmail.com
 */

#include "../headers/gba.h"
#include "../headers/gba_sprites.h"
#include "../headers/ai.h"
#include "../headers/interface.h"
#include "../headers/maps.h"			// maps header file

Sprite  space_ship, UFO, UFO2, UFO3, UFO4, UFO5, UFO6, bullet;
Sprite enemies[30];
int current_way;


/**
 * Load all AI tiles into memory
 */
void initialize_ai() {

	// Load 256 colors in the palette memory
	u16 loop;
	for(loop = 0; loop < 256; loop++)
		OBJPaletteMem[loop] = PalletPal[loop];	

	// start of spaceship
	space_ship.x = 100;
	space_ship.y = 100;
	

	// specify offsets and index of sprite in OAM array.
	space_ship.OAMSpriteNum = 10;
	bullet.OAMSpriteNum = 11;

	update_sprite( space_ship, 352 );

	
	/**
	*Load Tiles
	*/
	
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
	if(UFO.y+20 >= space_ship.y && UFO.x+10 >= space_ship.x && UFO.x-10 <= space_ship.x){
		set_health( get_health() - 1 );
		UFO.y=20;
		UFO.x=20;
	}
	
	u16 loop;
	for( loop = 15; loop < 21; loop++ ) {
	
		enemies[loop].OAMSpriteNum = loop;
		
		if( !enemies[loop].x ) {
			enemies[loop].x = (loop-15) * 20;
			enemies[loop].y = 0;
		}
		
		// Choose which way to go
		if( enemies[loop].x > 220 )
			current_way = 1;
		if( enemies[loop].x == 0 )
			current_way = 2;
		
		if( (current_way % 2) == 1 )
			enemies[loop].x--;
		else
			enemies[loop].x++;

		// If the mob is hit by the plane
		if( enemies[loop].y+20 >= space_ship.y && enemies[loop].y-20 >= space_ship.y && enemies[loop].x+10 >= space_ship.x && enemies[loop].x-10 <= space_ship.x ) {
			set_health( get_health() - 1 );
			enemies[loop].x = -40;
			enemies[loop].y = -40;
		}
		
		update_sprite( enemies[loop], 416 );
	
	}
	
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


	
	



