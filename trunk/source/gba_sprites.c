/**
 * This file contains functions and definitions for
 * controlling the on screen sprites.
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen
 * @email	wouter@0xff.nl
 */


#include "../headers/gba.h"
#include "../headers/gba_sprites.h"

// pointer to the object array memory.
u16* OAM = (u16*)0x7000000;
// OAMEntry array of 128, maximum of sprites on screen.
OAMEntry sprites[128];

/**
 * Copy sprites to OAM.
 */
void copy_oam()
{
	u16 loop;
	u16* temp;
	temp = (u16*)sprites;
	for(loop = 0; loop < 128*4; loop++)
	{
		OAM[loop] = temp[loop];
	}
}

/**
 * According to an article written by GBAJunkie you have to
 * initialize sprites off screen, otherwise sprite positions fails.
 * This function does so accordingly.
 */
void initialize_sprites()
{
	u16 loop;
	for(loop = 0; loop < 128; loop++)
	{
		sprites[loop].attribute0 = 160;  //y to > 159
		sprites[loop].attribute1 = 240;  //x to > 239
	}
}