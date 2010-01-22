/**
 * This file is the main source file for SpaceInvader.
 * It initializes the screen, reads keys and starts
 * the game loop.
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen, Wesley Hilhorst, Sebastiaan Seegers
 * @email	wouter@0xff.nl, wesley.hilhorst@gmail.com, Sseegers@gmail.com
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
int main(void);
signed int space_ship_movespeed;  
Sprite space_ship, UFO, bullet, UFO2, UFO3, UFO4, UFO5, UFO6;
 
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
	
	// Copy the BG into the memory
	dma_fast_copy((void*)SpacemapPal, (void*)BGPaletteMem, SpacemapPalLen / 2, DMA_16NOW);
	dma_fast_copy((void*)SpacemapTiles, (void*)CHARBASEBLOCK(charbase), SpacemapTilesLen / 2, DMA_32NOW);
	dma_fast_copy((void*)SpacemapMap, (void*)bg2map, SpacemapMapLen / 2, DMA_32NOW);
						
	
	// Initialize functions
	initialize_sprites();
	initialize_interface();			
	initialize_ai();

	// Set interface info for the start
	set_score( 0000 );
	set_health( 5 );		
		
}

void uninitialize_pause() {
    u32 charbase 	= 0;
	u32 screenbase 	= 28;	
	u16* bg2map = (unsigned short *)SCREENBASEBLOCK(screenbase);	

	//configure background modi.
	SET_MODE( MODE_2 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D ); //set mode 2 and enable sprites and 1d mapping
	REG_BG2CNT = BG_COLOR256 | ROTBG_SIZE_512x512 |(charbase << CHAR_SHIFT) | (screenbase << SCREEN_SHIFT);

	// Copy the BG into the memory
	dma_fast_copy((void*)SpacemapPal, (void*)BGPaletteMem, SpacemapPalLen / 2, DMA_16NOW);
	dma_fast_copy((void*)SpacemapTiles, (void*)CHARBASEBLOCK(charbase), SpacemapTilesLen / 2, DMA_32NOW);
	dma_fast_copy((void*)SpacemapMap, (void*)bg2map, SpacemapMapLen / 2, DMA_32NOW);
	
	// Initialize functions
	initialize_sprites();
	initialize_interface();
	
	// set sprites back at orginal position
	update_sprite( space_ship, 352 );
	update_sprite( UFO, 416 );

	
	// Set interface info for the restore
	set_score( get_score() );
	set_health( get_health() );
	
}

/**
 * initializes the pause mode
 */
void initialize_pause() {
	int x = bg.x_scroll;
	int y = bg.y_scroll;
	reset_background();
	
	// Set the PauseScreen bitmap on screen
	//	SET_MODE( MODE_3 | BG2_ENABLE ); 
	//	dma_fast_copy((void*)PausescreenBitmap, (void*)VideoBuffer, PausescreenBitmapLen / 2, DMA_16NOW); 


	show_highscore( 115 , 15 );
	copy_oam();

	u32 pause = 1;
	while(pause) {
		if (KEYDOWN(KEY_START)) {
			u8 release = 0;
			while(!release) {
				if (!KEYDOWN(KEY_START)) {
					release = 1;
					pause = 0;
				}
			}
		}
	}
	
	// restore background information
	bg.x_scroll = x;
	bg.y_scroll = y;	
	
	uninitialize_pause();
	
}

/**
 * initializes the game over screen
 */
void initialize_gameover(){
	if(get_health() == 0){
		reset_background();
		save_highscore();

		// Set the Gameover bitmap on screen
		SET_MODE( MODE_3 | BG2_ENABLE ); 	
		dma_fast_copy((void*)GameoverBitmap, (void*)VideoBuffer, GameoverBitmapLen / 2, DMA_16NOW);
		
		u32 key = 1;
		while(key) {
			if(KEYDOWN(KEY_START)) {
				u8 release = 0;
				while(!release) {
					if(!KEYDOWN(KEY_START)) {
						release = 1;
						key = 0;
					}
				}
			}
		}	
		// restart the game
		main();
	}
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

	
	if(KEYDOWN(KEY_START)) { u8 release = 0; while(!release) { if (!KEYDOWN(KEY_START)) { release = 1; } }
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
		
		update_sprite( space_ship, 352 );
		
		if (bg.y_scroll >= 5)
			bg.y_scroll -= (space_ship_movespeed * 4);

	}
	if(!(*KEYS & KEY_DOWN)) {
		if( ( space_ship.y += space_ship_movespeed ) > ( 160 - 53 ) )
			space_ship.y = ( 160 - 53 );
		
		update_sprite( space_ship, 352 );
		
		if (bg.y_scroll <= 350)
			bg.y_scroll += (space_ship_movespeed * 4);
	}	
	if(!(*KEYS & KEY_RIGHT)) {
		if( ( space_ship.x += space_ship_movespeed ) > ( 240 - 32 ) )
			space_ship.x = ( 240 - 32 );
		
		update_sprite( space_ship, 352 );
		
		if (bg.x_scroll <= 260)
			bg.x_scroll += (space_ship_movespeed * 4);
	}
	if(!(*KEYS & KEY_LEFT)) {
		if( ( space_ship.x -= space_ship_movespeed ) < 0 || space_ship.x > ( 240 - 32 ) )
			space_ship.x = 0;
			
		update_sprite( space_ship, 352 );
		
		if (bg.x_scroll >= 5)
			bg.x_scroll -= (space_ship_movespeed * 4);
	}
	if(!(*KEYS & KEY_B)) {
		fire_bullet();
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

	// x 150
	// y 220
	// Main game loop
	while(1) {
		get_input();
		track_ai();
		wait_for_vsync();
		copy_oam();
		rotate_background();
		initialize_gameover();
	}
	return 0;
}


