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

int segment_1, segment_2, segment_3, segment_4, ship_health, ship_maxhealth;
Sprite score_1, score_2, score_3, score_4;


/**
 * Load all score interface tiles into memory
 */
void initialize_interface() {

	// Set max health
	ship_maxhealth = 5;

	u16 loop;

	// Load score tiles on 50th-59th place
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
		
	
	// Load background tiles on 60th
	for(loop = 30720; loop < 31232; loop++)
		OAMData[loop] = interfacebgTiles[loop-30720];
		
	// Load healthbar tiles on 61th
	for(loop = 31232; loop < 31744; loop++)
		OAMData[loop] = healthbarTiles[loop-31232];
		
	// Score sprite numbers from 62 to 65
	score_1.OAMSpriteNum = 62;
	score_2.OAMSpriteNum = 63;
	score_3.OAMSpriteNum = 64;
	score_4.OAMSpriteNum = 65;
	
	// Interface background sprite numbers genereren
	int bg_sprites = 66 + ship_maxhealth;
	for( loop = bg_sprites; loop < (bg_sprites+8); loop++ )
		{
	
		sprites[loop].attribute0 = COLOR_256 | SQUARE | 128;
		sprites[loop].attribute1 = SIZE_32 | ((loop-bg_sprites) * 32);
		sprites[loop].attribute2 = 1920; 
		
	}
	
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
 * Set healthbar on a specific health (0-5)
 */
 void set_health( int hp ) {
	
	int x, y;	
	int shiftright = 5;
	
	if( hp > ship_maxhealth || hp < 0)
		hp = 1;	
	
	int loop;
	for( loop = 0; loop < ship_maxhealth; loop++ ) {
	
		y = 128;
		x = (loop * 17) + shiftright;
	
		if( hp < loop ) {
			y = -2;
			x = -2;
		}
	
		sprites[loop+66].attribute0 = COLOR_256 | SQUARE | y;
		sprites[loop+66].attribute1 = SIZE_32 | x;
		sprites[loop+66].attribute2 = 1952; 
		
	}
 
	ship_health = hp;
 
 }
 
 /**
  * Get current health
  */
 int get_health() {
 
	return ship_health;
 
 }
 
 