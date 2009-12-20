/**
 * This file is the main source file for SpaceInvader.
 * It initializes the screen, reads keys and starts
 * the game loop.
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen, Wesley Hilhorst
 * @email	wouter@0xff.nl, wesley.hilhorst@gmail.com
 */

#include "../headers/gba.h"				// GBA register definitions
#include "../headers/dispcnt.h"			// REG_DISPCNT register #define
#include "../headers/gba_sprites.h"		// generic sprite header file
#include "../headers/gba_bg.h"			// generic background header file
#include "../headers/gba_dma.h"			// DMA register definitions
#include "../headers/gba_keypad.h"		// key header file
#include "../headers/gba_sram.h"		// sram header file
#include "../headers/maps.h"			// maps header file
#include "../headers/menus.h"			// menus header file
#include "../headers/interface.h"		// interface header file
#include "../headers/ai.h"				// interface header file


/**
 * Usefull game vars
 */
signed int space_ship_movespeed;  
Sprite space_ship, UFO, bullet;
Map map;
 
int start_status = 0;


/**
 * initializes the startmenu on screen
 */
void initialize_startscreen() {
	SET_MODE( MODE_3 | BG2_ENABLE ); 
	
	dma_fast_copy((void*)StartscreenBitmap, (void*)VideoBuffer, StartscreenBitmapLen / 2, DMA_16NOW); 
	
    while((*KEYS & KEY_START))
		wait_for_vsync();
		
	while(!(*KEYS & KEY_START))
		wait_for_vsync();

}
 

/**
 * initializes the background and sprites on screen.
 */
void initialize_game() {
    u32 charbase 	= 0;
	u32 screenbase 	= 28;	
	u16* bg2map = (unsigned short *)SCREENBASEBLOCK(screenbase);	
	
	// position the scroll of the background
	bg.x_scroll = 150;
	bg.y_scroll = 220;
	
	//configure background modi.
	SET_MODE( MODE_2 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D ); //set mode 2 and enable sprites and 1d mapping
	REG_BG2CNT = BG_COLOR256 | ROTBG_SIZE_512x512 |(charbase << CHAR_SHIFT) | (screenbase << SCREEN_SHIFT);

	// store pointers to import map information.
	map.level_palette = (void *)SpacemapPal;
	map.level_tiles = (void *)SpacemapTiles;
	map.level_map = (void *)SpacemapMap;
	

	//Copy background palette into memory
	dma_fast_copy((void*)SpacemapPal, (void*)BGPaletteMem, SpacemapPalLen / 2, DMA_16NOW);
	//set the tile images
	dma_fast_copy((void*)SpacemapTiles, (void*)CHARBASEBLOCK(charbase), SpacemapTilesLen / 2, DMA_32NOW);
	//copy the tile map into background 2
	dma_fast_copy((void*)SpacemapMap, (void*)bg2map, SpacemapMapLen / 2, DMA_32NOW);
	
	// start of spaceship
	space_ship.x = 100;
	space_ship.y = 100;
	
	// specify offsets and index of sprite in OAM array.
	space_ship.OAMSpriteNum = 0;

	
	u16 loop;
	for(loop = 0; loop < 256; loop++)          //load the palette into memory
		OBJPaletteMem[loop] = ShipPal[loop];					
	
	
	//initialize the sprites
	initialize_sprites();
	
	//initialize the userinterface for score and health
	initialize_interface();			
	
	initialize_ai();		
	
  	sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;	//setup sprite info, 256 colour, shape and y-coord
	sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;				//size 32x32 and x-coord
	sprites[space_ship.OAMSpriteNum].attribute2 = 0;                      				//pointer to tile where sprite starts
		
	for(loop = 0; loop < 512; loop++)				//load 1st sprite image data
		OAMData[loop] = ShipTiles[loop];		
		
}

void restore_from_pause() {
    u32 charbase 	= 0;
	u32 screenbase 	= 28;	
	u16* bg2map = (unsigned short *)SCREENBASEBLOCK(screenbase);	

	//configure background modi.
	SET_MODE( MODE_2 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D ); //set mode 2 and enable sprites and 1d mapping
	REG_BG2CNT = BG_COLOR256 | ROTBG_SIZE_512x512 |(charbase << CHAR_SHIFT) | (screenbase << SCREEN_SHIFT);

	//Copy background palette into memory
	dma_fast_copy((void*)SpacemapPal, (void*)BGPaletteMem, SpacemapPalLen / 2, DMA_16NOW);
	//set the tile images
	dma_fast_copy((void*)SpacemapTiles, (void*)CHARBASEBLOCK(charbase), SpacemapTilesLen / 2, DMA_32NOW);
	//copy the tile map into background 2
	dma_fast_copy((void*)SpacemapMap, (void*)bg2map, SpacemapMapLen / 2, DMA_32NOW);
	
	
	u16 loop;
	for(loop = 0; loop < 256; loop++)          //load the palette into memory
		OBJPaletteMem[loop] = ShipPal[loop];				
	
  	sprites[UFO.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | UFO.y;					//setup sprite info, 256 colour, shape and y-coord
	sprites[UFO.OAMSpriteNum].attribute1 = SIZE_32 | UFO.x;							//size 32x32 and x-coord
	sprites[UFO.OAMSpriteNum].attribute2 = 32;     									//pointer to tile where sprite starts

	
	for(loop = 512; loop < 1024; loop++)			//load 2st sprite image data
		OAMData[loop] = UFOTiles[loop-512];	
	
	for(loop = 1024; loop < 1536; loop++)			//load 3st sprite image data
		OAMData[loop] = bulletTiles[loop-1024];
	
	
	//initialize the sprites
	initialize_sprites();
	
	//initialize_ai();
	
	//initialize the userinterface for score and health
	initialize_interface();
	
  	sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;	//setup sprite info, 256 colour, shape and y-coord
	sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;				//size 32x32 and x-coord
	sprites[space_ship.OAMSpriteNum].attribute2 = 0;                      				//pointer to tile where sprite starts
		
	for(loop = 0; loop < 512; loop++)				//load 1st sprite image data
		OAMData[loop] = ShipTiles[loop];
		
	set_score(map.score);
	set_health(map.damage);
	
	update_background();
}

/**
 * initializes the pause mode
 */
void initialize_pause() {
	u32 pause = 1;
	int x = bg.x_scroll;
	int y = bg.y_scroll;
	reset_background();
 	SET_MODE( MODE_3 | BG2_ENABLE ); 
	dma_fast_copy((void*)PausescreenBitmap, (void*)VideoBuffer, PausescreenBitmapLen / 2, DMA_16NOW); 

	// save important information 
	map.score = get_score();
	map.damage = get_health();

	while(pause) {
		if (KEYDOWN(KEY_A)) {
			u8 release = 0;
			while(!release) {
				if (!KEYDOWN(KEY_A)) {
					release = 1;
					pause = 0;
				}
			}
		}
	}
	// restore background information
	bg.x_scroll = x;
	bg.y_scroll = y;	
	restore_from_pause();
}


/**
 * Function for handling the keys.
 */
void get_input() {


    ///////////////////////////////
    // LETOP: save_highscore() werkt, echter kan je deze niet zomaar onder een button koppelen
	//        dan wordt save_highscore() namelijk vaker aangeroepen, dus meer gesaved!
	//
	// Wouter, kun jij hier wellicht een functie voor maken die we eventueel kunnen aanroepen.
	// De manier die ik hieronder heb toegepast is iets mooier dan die van 2 while lussen!
	///////////////////////////////
	if(!(*KEYS & KEY_START) && start_status == 0 ) {

		start_status = 1;
		
	}
	if((*KEYS & KEY_START) && start_status == 1) {

		start_status = 2;
		
	}
	if( start_status == 2 ) {
	
		save_highscore();
		start_status = 0;
		
	}

	
	if(KEYDOWN(KEY_A)) { u8 release = 0; while(!release) { if (!KEYDOWN(KEY_A)) { release = 1; } }
		//set_score( get_score() + 1 );
		//space_ship_movespeed = 2;
		initialize_pause();
	}
	if((*KEYS & KEY_A)) {
		space_ship_movespeed = 1;
	}
	if(!(*KEYS & KEY_UP)) {	
		if( ( space_ship.y -= space_ship_movespeed ) <= 0 || space_ship.y > ( 160 - 32 ) )
			space_ship.y = 0;
		
		//space_ship.active_frame = 0;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;
		sprites[space_ship.OAMSpriteNum].attribute2 = 0;
		
		if (bg.y_scroll >= 5)
			bg.y_scroll -= (space_ship_movespeed * 4);

	}
	if(!(*KEYS & KEY_DOWN)) {
		if( ( space_ship.y += space_ship_movespeed ) > ( 160 - 53 ) )
			space_ship.y = ( 160 - 53 );
		
 		//space_ship.active_frame = 0;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;			
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		
		if (bg.y_scroll <= 350)
			bg.y_scroll += (space_ship_movespeed * 4);
	}	
	if(!(*KEYS & KEY_RIGHT)) {
		if( ( space_ship.x += space_ship_movespeed ) > ( 240 - 32 ) )
			space_ship.x = ( 240 - 32 );
		
 		//space_ship.active_frame = 0;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;	
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		if (bg.x_scroll <= 260)
			bg.x_scroll += (space_ship_movespeed * 4);
	}
	if(!(*KEYS & KEY_LEFT)) {
		if( ( space_ship.x -= space_ship_movespeed ) < 0 || space_ship.x > ( 240 - 32 ) )
			space_ship.x = 0;
			
 		//space_ship.active_frame = 0;
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;			
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		
		if (bg.x_scroll >= 5)
			bg.x_scroll -= (space_ship_movespeed * 4);
	}
	if(!(*KEYS & KEY_B)) {
		fire_bullet();
	}
	

	/////////////////////////////////
	// Save/Load on SRAM testing   //
	/////////////////////////////////
	
	if(!(*KEYS & KEY_L)) {
		erase_SRAM( 40 ); 				// Erase 40 chars
	
		save_int(0,space_ship.x);		// Save Ship X
		save_int(10,space_ship.y);		// Save Ship Y
		save_int(20,bg.x_scroll);		// Save BG X
		save_int(30,bg.y_scroll);		// Save BG Y
	}
	if(!(*KEYS & KEY_R)) {
		space_ship.x = load_int(0);		// Load Ship X
		space_ship.y = load_int(10);	// Load Ship Y
		
		sprites[space_ship.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | space_ship.y;
		sprites[space_ship.OAMSpriteNum].attribute1 = SIZE_32 | space_ship.x;			
		sprites[space_ship.OAMSpriteNum].attribute2 = 0; 
		
		bg.x_scroll = load_int(20);		// Load BG X
		bg.y_scroll = load_int(30);		// Load BG Y
	}
	
}


/*
 * The main game loop.
 *
 * @return the exit status.
 */
int main() {
	initialize_startscreen();
	initialize_game();

	// Main game loop
	while(1) {
		get_input();
		track_ai();
		track_bullet();
		wait_for_vsync();
		copy_oam();
		update_background();
	}
	return 0;
}
