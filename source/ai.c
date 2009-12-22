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

Sprite  space_ship, UFO, bullet, UFO2, UFO3;


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

	// start of UFO
	UFO.x = 20;
	UFO.y = 20;
	
	// start of UFO2
	
	
	// start of UFO3
	UFO3.x = 240;
	UFO3.y = 10;
	
	
	
	
	// specify offsets and index of sprite in OAM array.
	space_ship.OAMSpriteNum = 10;
	UFO.OAMSpriteNum = 11;
	bullet.OAMSpriteNum = 12;
	UFO2.OAMSpriteNum = 13;
	UFO3.OAMSpriteNum = 14;


	
	update_sprite( space_ship, 352 );
	update_sprite( UFO, 416 );      	//13 x 32 = 416 waarom?? klopt niet met de UFO.OAMSpriteNum 
	//update_sprite(UFO2, 448 );
	update_sprite( UFO3, 480 );
	
	/**
	*Load Tiles
	*/
	
	for(loop = 5632; loop < 6144; loop++)
		OAMData[loop] = ShipTiles[loop-5632];		
		
	for(loop = 6144; loop < 6656; loop++)
		OAMData[loop] = bulletTiles[loop-6144];
		
	for(loop = 6656; loop < 7168; loop++)
		OAMData[loop] = UFOTiles[loop-6656];
		
	for(loop = 7168; loop < 7680; loop++)
		OAMData[loop] = UFO2Tiles[loop-7168];
	
	for(loop = 7680; loop < 8192; loop++)
		OAMData[loop] = UFO3Tiles[loop-7680];
	
		

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
	if(UFO.x >= 240){
		UFO.x = 10;
		UFO.y = UFO.y+5;
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
	
	if(UFO3.x <= 0){
		UFO3.x = 240;
		UFO3.y = UFO3.y+5;
	}
	UFO3.x--;
	update_sprite( UFO3, 480 );
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

