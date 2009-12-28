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

#define UFOS_LEN 6
Sprite  space_ship, explosion, bullet;
Sprite UFOS[UFOS_LEN];
// keep track of important ufo information
u16 UFOS_on_scr = 0; // keeps track of amount of ufo's on screen.
u16 UFOS_expl_on_scr = 0; // keeps track of explosion, boolean value.

// keeping track of vsync is useful for removing explosions from screen.
u16 AI_vsync_count = 1;


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
	space_ship.sprite_index = 352;
	bullet.OAMSpriteNum = 11;
	bullet.sprite_index = 384;

	update_sprite( space_ship, space_ship.sprite_index );

	
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
	
	for(loop = 8192; loop < 8704; loop++)
		OAMData[loop] = UFO4Tiles[loop-8192];
		
	for(loop = 8704; loop < 9216; loop++)
		OAMData[loop] = UFO5Tiles[loop-8704];
	
	for(loop = 9216; loop < 9728; loop++)
		OAMData[loop] = UFO6Tiles[loop-9216];
		
	for(loop = 9728; loop < 10240; loop++)
		OAMData[loop] = BoomTiles[loop-9728];
		
	/**
	* Load UFOs and give them sprite numbers.
	*/
	UFOS[0].OAMSpriteNum   = 15; // sprite tile index: 416
	UFOS[0].sprite_index   = 416;
	UFOS[1].OAMSpriteNum   = 16; // sprite tile index: 448
	UFOS[1].sprite_index   = 448;
	UFOS[2].OAMSpriteNum   = 17; // sprite tile index: 480
	UFOS[2].sprite_index   = 480;
	UFOS[3].OAMSpriteNum   = 18; // sprite tile index: 512
	UFOS[3].sprite_index   = 512;
	UFOS[4].OAMSpriteNum   = 19; // sprite tile index: 544
	UFOS[4].sprite_index   = 544;
	UFOS[5].OAMSpriteNum   = 20; // sprite tile index: 576
	UFOS[5].sprite_index   = 576;
	/**
	 * load explosion sprite.
	 */
	explosion.OAMSpriteNum = 21; // sprite tile index: 608
	explosion.sprite_index = 608;
	/**
	 * put one ufo on screen.
	 */
	UFOS[0].x = 100;
	UFOS[0].y = 70;
	update_sprite(UFOS[0], UFOS[0].sprite_index);
}


/**
 * this function starts bullet
 */
void fire_bullet(){
		if(bullet.y >= 138){
			bullet.y = -2;
			bullet.x = -2;
			update_sprite( bullet, bullet.sprite_index );
			bullet.x = space_ship.x + 3;
			bullet.y = space_ship.y - 24;
		}
}


/**
 * this function handles the ai; spawning enemies, etc.
 */
void track_ai() {
	AI_vsync_count++;

	u16 loop;
	for(loop = 0;loop < UFOS_LEN; loop++) {
		// updating sprites is necessary if explosion is on screen.
		// we wait AI_vsync_count mod 15, because the explosion is visible
		// for an acceptable time if we wait 15 syncs.
		if (UFOS_expl_on_scr &&
			 AI_vsync_count % 30 == 0) {
			 update_sprite(UFOS[loop], UFOS[loop].sprite_index);
			 AI_vsync_count = 0;
			 UFOS_expl_on_scr = 0;
		}

		
	}
	track_bullet();
	/*if(UFO.y+20 >= space_ship.y && UFO.x+10 >= space_ship.x && UFO.x-10 <= space_ship.x){
		set_health( get_health() - 1 );
		UFO.y=20;
		UFO.x=20;
	}
	
	u16 loop;
	for( loop = 15; loop < 21; loop++ ) {
	
		enemies[loop].OAMSpriteNum = loop;
		
		//if( !enemies[loop].x ) {
		//	enemies[loop].x = (loop-15) * 20;
		//	enemies[loop].y = 0;
		//}
		
		// Choose which way to go
		if( enemies[loop].x > 220 )
			current_way = 1;
		if( enemies[loop].x == 0 )
			current_way = 2;
		
		if( (current_way % 2) == 1 ) {
			enemies[loop].x--;
			if (enemies[loop].y++ >= 240) enemies[loop].y = 0;
		} else {
			enemies[loop].x++;
			if (enemies[loop].y-- <= 0) enemies[loop].y = 0;
		}
		// If the mob is hit by the plane
		if( enemies[loop].y+20 >= space_ship.y && 
			enemies[loop].y-20 >= space_ship.y && 
			enemies[loop].x+10 >= space_ship.x && 
			enemies[loop].x-10 <= space_ship.x ) {
			set_health( get_health() - 1 );
		//	enemies[loop].x = -40;
		//	enemies[loop].y = -40;
		}
		
		update_sprite( enemies[loop], 416 );
	
	}*/	
}


/**
 * this function handles the bullet.
 */
void track_bullet() {
	
	if( bullet.y >= 0 ) {
		bullet.y = bullet.y - 2;
		update_sprite( bullet, 384 );
	}
	u16 loop;
	for(loop=0; loop<UFOS_LEN; loop++) {
		if (bullet.x+10 >= UFOS[loop].x &&
		    bullet.x-10 <= UFOS[loop].x &&
			bullet.y == UFOS[loop].y) {
				explosion.x = UFOS[loop].x;
				explosion.y = UFOS[loop].y;
				bullet.y = -2;
				bullet.x = -2;
				update_sprite(bullet, bullet.sprite_index );
				update_sprite(UFOS[loop], explosion.sprite_index);
				UFOS[loop].x = 240;
				UFOS[loop].y = 160;
				UFOS_expl_on_scr = 1;
				set_score( get_score() + 1 );
			}
	}
	
}


	
	


