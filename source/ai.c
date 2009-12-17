#include "../headers/gba.h"
#include "../headers/gba_sprites.h"
#include "../headers/ai.h"
#include "../headers/interface.h"
#include "../headers/maps.h"			// maps header file

Sprite  space_ship, UFO, bullet;
/**
 * Load all ai tiles into memory
 */
void initialize_ai() {
	// start of UFO
	UFO.x = 20;
	UFO.y = 20;
	
	UFO.OAMSpriteNum = 1;
	bullet.OAMSpriteNum = 2;
	
  	sprites[UFO.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | UFO.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[UFO.OAMSpriteNum].attribute1 = SIZE_32 | UFO.x;							//size 32x32 and x-coord
	sprites[UFO.OAMSpriteNum].attribute2 = 32;     									//pointer to tile where sprite starts
	
	u16 loop;

	
	for(loop = 512; loop < 1024; loop++)			//load 2st sprite image data
		OAMData[loop] = UFOTiles[loop-512];
		
	for(loop = 1024; loop < 1536; loop++)			//load 3st sprite image data
		OAMData[loop] = bulletTiles[loop-1024];

}
/**
 * this function starts bullet
 */
void fire_bullet(){
		if(bullet.y >= 138){
			bullet.y = -2;
			bullet.x = -2;
			
			sprites[bullet.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | bullet.y;
			sprites[bullet.OAMSpriteNum].attribute1 = SIZE_32 | bullet.x;
			sprites[bullet.OAMSpriteNum].attribute2 = 64; 	

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
	
	sprites[UFO.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | UFO.y;
    sprites[UFO.OAMSpriteNum].attribute1 = SIZE_32 | UFO.x;
    sprites[UFO.OAMSpriteNum].attribute2 = 32;   
}

/**
 * this function handles the bullet.
 */
void track_bullet() {
	if(bullet.y >= 0){
		bullet.y = bullet.y - 2;
		sprites[bullet.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | bullet.y;
		sprites[bullet.OAMSpriteNum].attribute1 = SIZE_32 | bullet.x;
		sprites[bullet.OAMSpriteNum].attribute2 = 64; 
	}
	if(bullet.x+10 >= UFO.x &&	bullet.x-10 <= UFO.x && bullet.y == UFO.y){
			bullet.y = -2;
			bullet.x = -2;
			
			sprites[bullet.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | bullet.y;
			sprites[bullet.OAMSpriteNum].attribute1 = SIZE_32 | bullet.x;
			sprites[bullet.OAMSpriteNum].attribute2 = 64; 	
	
			set_score( get_score() + 1 );
	}
}