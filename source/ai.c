/**
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen, Wesley Hilhorst, Sebastiaan Seegers, Jeroen Visser
 * @email	wouter@0xff.nl, wesley.hilhorst@gmail.com, Sseegers@gmail.com
 */

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "../headers/gba.h"
#include "../headers/gba_sprites.h"
#include "../headers/ai.h"
#include "../headers/interface.h"
#include "../headers/maps.h"			// maps header file

#define UFOS_LEN 6
#define EXPLOSION_LEN 20
Sprite  space_ship, explosion, bullet;
Sprite UFOS[UFOS_LEN];
// keep track of important ufo information
u16 UFOS_on_scr = 0; // keeps track of amount of ufo's on screen.
u16 UFOS_expl_on_scr = 0; // keeps track of explosion, boolean value.
u16 Explosion_len = EXPLOSION_LEN; //Duration of explosion of a UFO

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
	
	if (UFOS_on_scr < 1) {
		// Random Spawn of first UFO
		UFOS[0].x = random();
		UFOS[0].y = 20;
		update_sprite(UFOS[0], UFOS[0].sprite_index);
		UFOS_on_scr++;
	}
	if (UFOS_on_scr < 2 && get_score() > 10) {
		// Random Spawn of UFO
		UFOS[1].x = random();
		UFOS[1].y = 20;
		update_sprite(UFOS[1], UFOS[1].sprite_index);
		UFOS_on_scr++;
	}
	if (UFOS_on_scr < 3 && get_score() > 15) {
		// Random Spawn of UFO
		UFOS[2].x = random();
		UFOS[2].y = 20;
		update_sprite(UFOS[2], UFOS[2].sprite_index);
		UFOS_on_scr++;
	}
	if (UFOS_on_scr < 4 && get_score() > 20) {
		// Random Spawn of UFO
		UFOS[3].x = random();
		UFOS[3].y = 20;
		update_sprite(UFOS[3], UFOS[3].sprite_index);
		UFOS_on_scr++;
	}
	if (UFOS_on_scr < 5 && get_score() > 25) {
		// Random Spawn of UFO
		UFOS[4].x = random();
		UFOS[4].y = 20;
		update_sprite(UFOS[4], UFOS[4].sprite_index);
		UFOS_on_scr++;
	}
	
	//Moving the UFO's
	if(AI_vsync_count%10==0){
		UFOS[0].x += (space_ship.x - UFOS[0].x)/(space_ship.y - UFOS[0].y);
		UFOS[0].y++;
		update_sprite(UFOS[0], UFOS[0].sprite_index);
	}
	if(get_score() > 10 && AI_vsync_count%9==0){
		UFOS[1].x += (space_ship.x - UFOS[1].x)/(space_ship.y - UFOS[1].y);
		UFOS[1].y++;
		update_sprite(UFOS[1], UFOS[1].sprite_index);
	}
	if(get_score() > 15 && AI_vsync_count%8==0){
		UFOS[2].x += (space_ship.x - UFOS[2].x)/(space_ship.y - UFOS[2].y);
		UFOS[2].y++;
		update_sprite(UFOS[2], UFOS[2].sprite_index);
	}
	if(get_score() > 20 && AI_vsync_count%7==0){
		UFOS[3].x += (space_ship.x - UFOS[3].x)/(space_ship.y - UFOS[3].y);
		UFOS[3].y++;
		update_sprite(UFOS[3], UFOS[3].sprite_index);
	}
	if(get_score() > 25 && AI_vsync_count%6==0){
		UFOS[4].x += (space_ship.x - UFOS[4].x)/(space_ship.y - UFOS[4].y);
		UFOS[4].y++;
		update_sprite(UFOS[4], UFOS[4].sprite_index);
	}
	
	
	// the following things should be added:
	// 1) spawn more UFOS if certain scores are met.
	// 2) randomize the position of UFOS with intelligence.
	//    let them search for the space_ship, by creating a range of
	//    x and y coordinates that are in the neighborhood of the space_ship.
	// 3) if health is zero; game over.
	// 4) if score of n points is reached, level completed.

	u16 loop;
	for(loop = 0;loop < UFOS_LEN; loop++) {
		// check if ufo is hit by a plane
		if( (UFOS[loop].y+10 >= space_ship.y && 
			UFOS[loop].y-10 <= space_ship.y && 
			UFOS[loop].x+10 >= space_ship.x && 
			UFOS[loop].x-10 <= space_ship.x) ||
			UFOS[loop].y >= space_ship.y+2) {
				set_health( get_health() - 1 );
				UFOS[loop].x = random();
				UFOS[loop].y = 20;
				update_sprite(UFOS[loop], UFOS[loop].sprite_index);
		}		
	}
	track_bullet();
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
			bullet.y-2 <= UFOS[loop].y && 
			UFOS[loop].y > 0) {
				//Start Explosion
				if(!UFOS_expl_on_scr){
					explosion.x = UFOS[loop].x - 10;
					explosion.y = UFOS[loop].y - 10;
					update_sprite(explosion, explosion.sprite_index);
					UFOS_expl_on_scr = 1;
					Explosion_len = EXPLOSION_LEN;

				}
				//Respawn UFO
				UFOS[loop].x = (AI_vsync_count%200)+10;
				UFOS[loop].y = 20;
				update_sprite(UFOS[loop], UFOS[loop].sprite_index);

				//Hide Bullet
				bullet.y = -2;
				bullet.x = -2;
				update_sprite(bullet, bullet.sprite_index );
				
				set_score( get_score() + 1 );
			}
	}
	//Stop Explosion if needed
	if(UFOS_expl_on_scr && Explosion_len > 1){
		Explosion_len--;
	}else{
		explosion.x = -2;
		explosion.y = -2;
		update_sprite(explosion, explosion.sprite_index);
		UFOS_expl_on_scr = 0;
	}
	
}


int random(void) {
	
	int i = 1 + rand() % 140;
	return i;
}

	
	



