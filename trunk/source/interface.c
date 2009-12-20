/**
 * Functions to set the game score and show it
 *
 * @date	11/12/09
 * @author	Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */


#include <stdio.h>
#include <stdlib.h>
#include "../headers/gba.h"
#include "../headers/gba_sprites.h"
#include "../headers/gba_sram.h"
#include "../headers/interface.h"

int segment_1, segment_2, segment_3, segment_4, ship_health, ship_maxhealth;
int highscores[11] = {0,0,0,0,0,0,0,0,0,0,0};

Sprite score_1, score_2, score_3, score_4;


/**
 * Load all score interface tiles into memory
 */
void initialize_interface() {

	// Set max health
	ship_maxhealth = 5;

	u16 loop;

	// Load score tiles on 0th-9th place
	for(loop = 0; loop < 512; loop++)
		OAMData[loop] = text_0Tiles[loop];		
	  	
	for(loop = 512; loop < 1024; loop++)
		OAMData[loop] = text_1Tiles[loop-512];	
	  	
	for(loop = 1024; loop < 1536; loop++)
		OAMData[loop] = text_2Tiles[loop-1024];	
	  	
	for(loop = 1536; loop < 2048; loop++)
		OAMData[loop] = text_3Tiles[loop-1536];	
	  	
	for(loop = 2048; loop < 2560; loop++)
		OAMData[loop] = text_4Tiles[loop-2048];		
	  	
	for(loop = 2560; loop < 3072; loop++)
		OAMData[loop] = text_5Tiles[loop-2560];	
	  	
	for(loop = 3072; loop < 3584; loop++)
		OAMData[loop] = text_6Tiles[loop-3072];	
		
	for(loop = 3584; loop < 4096; loop++)
		OAMData[loop] = text_7Tiles[loop-3584];
		
	for(loop = 4096; loop < 4608; loop++)
		OAMData[loop] = text_8Tiles[loop-4096];
		
	for(loop = 4608; loop < 5120; loop++)
		OAMData[loop] = text_9Tiles[loop-4608];
	
	// Load healthbar tiles on 10th
	for(loop = 5120; loop < 5632; loop++)
		OAMData[loop] = healthbarTiles[loop-5120];
		
		
	// Score sprite numbers from 0-3th place
	score_1.OAMSpriteNum = 0;
	score_2.OAMSpriteNum = 1;
	score_3.OAMSpriteNum = 2;
	score_4.OAMSpriteNum = 3;
	
	// Load highscores
	load_highscores();

}


/**
 * Set a particular score
 */
void set_score( int score ) {

	// Dont go over 9999
	if( score > 9999 )
		score -= 9999;

	segment_1 = ( score / 1000 ) % 10;
	segment_2 = ( score / 100 ) % 10;
	segment_3 = ( score / 10 ) % 10;
	segment_4 = score % 10;
	
	// Set score position
	score_1.x = 190;
	score_1.y = 135;
	score_2.x = 198;
	score_2.y = 135;
	score_3.x = 206;
	score_3.y = 135;
	score_4.x = 214;
	score_4.y = 135;
	
	sprites[score_1.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_1.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_1.OAMSpriteNum].attribute1 = SIZE_32 | score_1.x;							//size 32x32 and x-coord
	sprites[score_1.OAMSpriteNum].attribute2 = (segment_1 * 32); 
	
	sprites[score_2.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_2.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_2.OAMSpriteNum].attribute1 = SIZE_32 | score_2.x;							//size 32x32 and x-coord
	sprites[score_2.OAMSpriteNum].attribute2 = (segment_2 * 32);
	
	sprites[score_3.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_3.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_3.OAMSpriteNum].attribute1 = SIZE_32 | score_3.x;							//size 32x32 and x-coord
	sprites[score_3.OAMSpriteNum].attribute2 = (segment_3 * 32);
	
	sprites[score_4.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_4.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_4.OAMSpriteNum].attribute1 = SIZE_32 | score_4.x;							//size 32x32 and x-coord
	sprites[score_4.OAMSpriteNum].attribute2 = (segment_4 * 32);

} 


/**
 * Get the current score as an int
 */
int get_score() {

	return (segment_1 * 1000) + (segment_2 * 100) + (segment_3 * 10) + segment_4;

}


/**
 * Set healthbar on a specific health (0-5)
 */
void set_health( int hp ) {
	
	int x, y;	
	int shiftright = 5;
	
	if( hp > ship_maxhealth || hp < 0)
		hp = 4;	
	
	int loop;
	for( loop = 0; loop < ship_maxhealth; loop++ ) {
	
		y = 128;
		x = (loop * 17) + shiftright;
	
		if( hp < loop ) {
			y = -2;
			x = -2;
		}
	
		sprites[loop+4].attribute0 = COLOR_256 | SQUARE | y;
		sprites[loop+4].attribute1 = SIZE_32 | x;
		sprites[loop+4].attribute2 = 320; 
		
	}
 
	ship_health = hp;
 
}
 
 
/**
 * Get current health
 */
int get_health() {
 
	return ship_health;
 
}
 
 
int compare( const void * a, const void * b ) {
    
  return ( *(int*)a - *(int*)b );
  
}
 
 
/**
 * Load current scores
 */
void load_highscores() {
 
	int i;
	for( i = 0; i < 11; i++ ) {
	
		highscores[i] = load_int( i * 10 );
	
	}
	
	qsort( highscores, 11, sizeof(int), compare );
	
}
 
 
/**
 * Save current score
 */
  
 void save_highscore() {
 
	highscores[0] = get_score();
	qsort( highscores, 11, sizeof(int), compare );
	
	erase_SRAM( 220 );
	
	int i;
	for( i = 1; i < 11; i++ ) {
	
		save_int( 10 * (i-1), highscores[i] );
		
	}
 
 }