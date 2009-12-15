/**
 * Functions to set the game score and show it
 *
 * @date	11/12/09
 * @author	Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */


#include "../headers/gba.h"
#include "../headers/gba_sprites.h"
#include "../headers/interface.h"

int segment_1, segment_2, segment_3, segment_4, ship_health;
Sprite score_1, score_2, score_3, score_4;


/**
 * Load all score interface tiles into memory
 */
void initialize_interface() {

	// Load tiles on 50th-59th place
	int loop;

	for(loop = 25600; loop < 26112; loop++)
		OAMData[loop] = text_0Tiles[loop-25600];		
	  	
	for(loop = 26112; loop < 26624; loop++)
		OAMData[loop] = text_1Tiles[loop-26112];	
	  	
	for(loop = 26624; loop < 27136; loop++)
		OAMData[loop] = text_2Tiles[loop-26624];	
	  	
	for(loop = 27136; loop < 27648; loop++)
		OAMData[loop] = text_3Tiles[loop-27136];	
	  	
	for(loop = 27648; loop < 28160; loop++)
		OAMData[loop] = text_4Tiles[loop-27648];		
	  	
	for(loop = 28160; loop < 28672; loop++)
		OAMData[loop] = text_5Tiles[loop-28160];	
	  	
	for(loop = 28672; loop < 29184; loop++)
		OAMData[loop] = text_6Tiles[loop-28672];	
		
	for(loop = 29184; loop < 29696; loop++)
		OAMData[loop] = text_7Tiles[loop-29184];
		
	for(loop = 29696; loop < 30208; loop++)
		OAMData[loop] = text_8Tiles[loop-29696];
		
	for(loop = 30208; loop < 30720; loop++)
		OAMData[loop] = text_9Tiles[loop-30208];
	
	// Set current score on 0000
	set_score( 0000 );
	
	// Set current health on max
	set_health( 5 );

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
	
	score_1.OAMSpriteNum = 50;
	score_2.OAMSpriteNum = 51;
	score_3.OAMSpriteNum = 52;
	score_4.OAMSpriteNum = 53;
	
	sprites[score_1.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_1.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_1.OAMSpriteNum].attribute1 = SIZE_32 | score_1.x;							//size 32x32 and x-coord
	sprites[score_1.OAMSpriteNum].attribute2 = 1600 + (segment_1 * 32); 
	
	sprites[score_2.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_2.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_2.OAMSpriteNum].attribute1 = SIZE_32 | score_2.x;							//size 32x32 and x-coord
	sprites[score_2.OAMSpriteNum].attribute2 = 1600 + (segment_2 * 32);
	
	sprites[score_3.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_3.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_3.OAMSpriteNum].attribute1 = SIZE_32 | score_3.x;							//size 32x32 and x-coord
	sprites[score_3.OAMSpriteNum].attribute2 = 1600 + (segment_3 * 32);
	
	sprites[score_4.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | score_4.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[score_4.OAMSpriteNum].attribute1 = SIZE_32 | score_4.x;							//size 32x32 and x-coord
	sprites[score_4.OAMSpriteNum].attribute2 = 1600 + (segment_4 * 32);

} 


/**
 * Get the current score as an int
 */
int get_score() {

	return (segment_1 * 1000) + (segment_2 * 100) + (segment_3 * 10) + segment_4;

}

/**
 * Set healthbar on a specific health 
 */
 void set_health( int health ) {
 
	ship_health = health;
 
 }
 
 /**
  * Get current health (0-5)
  */
 int get_health() {
 
	return ship_health;
 
 }
 
 