#include "../headers/gba.h"
#include "../headers/gba_sprites.h"

u16* OAM = (u16*)0x7000000;
OAMEntry sprites[128];

//Copy our sprite array to OAM
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

//Set sprites to off screen
void initialize_sprites()
{
	u16 loop;
	for(loop = 0; loop < 128; loop++)
	{
		sprites[loop].attribute0 = 160;  //y to > 159
		sprites[loop].attribute1 = 240;  //x to > 239
	}
}