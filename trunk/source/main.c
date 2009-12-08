/**
 * This file is the main source file for SpaceInvader.
 * It initializes the screen, reads keys and starts
 * the game loop.
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen
 * @email	wouter@0xff.nl
 */
 
#include "../headers/gba.h"				// GBA register definitions
#include "../headers/dispcnt.h"			// REG_DISPCNT register #define
#include "../headers/gba_sprites.h"		// generic sprite header file
#include "../headers/gba_bg.h"			// generic background header file
#include "../headers/gba_dma.h"			// DMA register definitions
#include "../headers/gba_keypad.h"		// key header file
#include "../headers/maps.h"			// maps header file

/**
 * space_ship is a struct that can be used to interact with
 * the sprite in the OAM.
 */
Sprite space_ship, UFO;

/**
 * initializes the background and sprites on screen.
 */
void initialize_game() {
    u32 charbase 	= 0;
	u32 screenbase 	= 28;	
	u16* bg2map = (unsigned short *)SCREENBASEBLOCK(screenbase);	
	
	// position the scroll of the background
	bg.x_scroll = 150;
	bg.y_scroll = 120;	
	
	// start of spaceship
	space_ship.x = 100;
	space_ship.y = 60;
	
	// start of UFO
	UFO.x = 180;
	UFO.y = 30;
	
	// specify offsets and index of sprite in OAM array.
	space_ship.OAMSpriteNum = 0;
	UFO.OAMSpriteNum = 1;

	//configure background modi.
	REG_BG2CNT = BG_COLOR256 | ROTBG_SIZE_512x512 |(charbase << CHAR_SHIFT) | (screenbase << SCREEN_SHIFT);
	SET_MODE(MODE_2 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //set mode 2 and enable sprites and 1d mapping

	//Copy background palette into memory
	dma_fast_copy((void*)SpacemapPal, (void*)BGPaletteMem, 256, DMA_16NOW);
	//set the tile images
	dma_fast_copy((void*)SpacemapTiles, (void*)CHARBASEBLOCK(charbase), 2592, DMA_32NOW);
	//copy the tile map into background 2
	dma_fast_copy((void*)SpacemapMap, (void*)bg2map, 64*64/2, DMA_32NOW);
	
	u16 loop;
	for(loop = 0; loop < 256; loop++)          //load the palette into memory
		OBJPaletteMem[loop] = ShipPal[loop];				

	initialize_sprites();
	
  	sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;	//setup sprite info, 256 colour, shape and y-coord
	sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;				//size 64x64 and x-coord
	sprites[space_ship.OAMSpriteNum].attribute2 = 0;                      	//pointer to tile where sprite starts
	
  	sprites[UFO.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | UFO.y;	//setup sprite info, 256 colour, shape and y-coord
	sprites[UFO.OAMSpriteNum].attribute1 = SIZE_32 | UFO.x;				//size 64x64 and x-coord
	sprites[UFO.OAMSpriteNum].attribute2 = 32;     	
	
	for(loop = 0; loop < 512; loop++)               	//load 1st sprite image data
		OAMData[loop] = ShipTiles[loop];	

	for(loop = 512; loop < 1024; loop++)               	//load 1st sprite image data
		OAMData[loop] = UFOTiles[loop-512];		
}

/**
 * Function for handling the keys.
 */
void get_input() {

	if(!(*KEYS & KEY_UP)) {
		//space_ship.active_frame = 0;
		space_ship.y--;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;		//size 64x64 and x-coord		
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		bg.y_scroll -= 4;

	}
	if(!(*KEYS & KEY_DOWN)) {
		space_ship.y++;
 		//space_ship.active_frame = 0;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;			
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		bg.y_scroll += 4;
	}	
	if(!(*KEYS & KEY_RIGHT)) {
		space_ship.x++;
 		//space_ship.active_frame = 0;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;	
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		bg.x_scroll += 4;
	}
	if(!(*KEYS & KEY_LEFT)) {
		space_ship.x--;
 		//space_ship.active_frame = 0;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;			
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		bg.x_scroll -= 4;
	}	
}


/**
 * The main game loop.
 *
 * @return the exit status.
 */
int main() {

	initialize_game();

	while(1) {
		get_input();
		wait_for_vsync();
		copy_oam();
		update_background();
	}

	return 0;
}
