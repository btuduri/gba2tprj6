#include "../headers/gba.h"				// GBA register definitions
#include "../headers/dispcnt.h"			// REG_DISPCNT register #define
#include "../headers/gba_sprites.h"		// generic sprite header file
#include "../headers/gba_bg.h"			// generic background header file
#include "../headers/gba_dma.h"			// DMA register definitions
#include "../headers/gba_keypad.h"
#include "../levels/level1/sprites/Ship.h" // spaceship sprite
#include "../levels/level1/Spacemap.h" // space map

// fast memory copy using dma
void DMAFastCopy(void* source, void* dest, unsigned int count,unsigned int mode) {
	if (mode == DMA_16NOW || mode == DMA_32NOW) {
		REG_DMA3SAD = (unsigned int)source;
		REG_DMA3DAD = (unsigned int)dest;
		REG_DMA3CNT = count | mode;
	}
}

//create an OAM variable and make it point to the address of OAM
u16* OAM = (u16*)0x7000000;

//create the array of sprites (128 is the maximum)
OAMEntry sprites[128];

u16 x_scroll=150, y_scroll=120;

//declare an instance of the background structure
Bg bg2;

//animated sprite structure required
typedef struct
{
	u16 x;			//x and y position on screen
	u16 y;
	u16 spriteFrame[3];     //animation frame storage
	int activeFrame;        //which frame is active
	u16 OAMSpriteNum;       //which sprite referring to
}Sprite;

Sprite spaceShip;

//Copy our sprite array to OAM
void CopyOAM()
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
void InitializeSprites()
{
	u16 loop;
	for(loop = 0; loop < 128; loop++)
	{
		sprites[loop].attribute0 = 160;  //y to > 159
		sprites[loop].attribute1 = 240;  //x to > 239
	}
}

void WaitForVsync()
{
	while((volatile u16)REG_VCOUNT != 160){}
}

void EnableBackground(Bg* bg)
{
	u16 temp;

	bg->tileData = (u16*)CharBaseBlock(bg->charBaseBlock);
	bg->mapData = (u16*)ScreenBaseBlock(bg->screenBaseBlock);
	temp = bg->size | (bg->charBaseBlock<<CHAR_SHIFT) | (bg->screenBaseBlock<<SCREEN_SHIFT)
		| bg->colorMode | bg->mosaic | bg->wraparound;

	switch(bg->number)
	{
	case 0:
		{
			REG_BG0CNT = temp;
			REG_DISPCNT |= BG0_ENABLE;
		}break;
	case 1:
		{
			REG_BG1CNT = temp;
			REG_DISPCNT |= BG1_ENABLE;
		}break;
	case 2:
		{
			REG_BG2CNT = temp;
			REG_DISPCNT |= BG2_ENABLE;
		}break;
	case 3:
		{
			REG_BG3CNT = temp;
			REG_DISPCNT |= BG3_ENABLE;
		}break;

	default:break;

	}
}

/*void UpdateBackground(Bg* bg)
{
	switch(bg->number)
	{
	case 0:
		REG_BG0HOFS = bg->x_scroll;
		REG_BG0VOFS = bg->y_scroll;
		break;
	case 1:
		REG_BG1HOFS = bg->x_scroll;
		REG_BG1VOFS = bg->y_scroll;
		break;
	case 2:
		if(!(REG_DISPCNT & MODE_0))//it is a rot background
		{
			REG_BG2X = bg->DX;
			REG_BG2Y = bg->DY;

			REG_BG2PA = bg->PA;
			REG_BG2PB = bg->PB;
			REG_BG2PC = bg->PC;
			REG_BG2PD = bg->PD;
		}
		else  //it is a text background
		{
			REG_BG2HOFS = bg->x_scroll;
			REG_BG2VOFS = bg->y_scroll;
		}
		break;
	case 3:
		if(!(REG_DISPCNT & MODE_0))//it is a rot background
		{
			REG_BG3X = bg->DX;
			REG_BG3Y = bg->DY;

			REG_BG3PA = bg->PA;
			REG_BG3PB = bg->PB;
			REG_BG3PC = bg->PC;
			REG_BG3PD = bg->PD;
		}
		else //it is a text background
		{
			REG_BG3HOFS = bg->x_scroll;
			REG_BG3VOFS = bg->y_scroll;
		}
		break;
	default: break;
	}
}*/

void UpdateBackground(u16 x,u16 y){
	REG_BG2X = x*256;
	REG_BG2Y = y*256;
}

void GetInput()
{
	if(!(*KEYS & KEY_UP))                   //if the up key is pressed
	{
		spaceShip.activeFrame = 0;
		spaceShip.y--;
		sprites[spaceShip.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | spaceShip.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[spaceShip.OAMSpriteNum].attribute1 = SIZE_64 | spaceShip.x;		//size 64x64 and x-coord		
		y_scroll -= 4;

	}
	if(!(*KEYS & KEY_DOWN))                 //if the up down is pressed
	{
		spaceShip.y++;
 		spaceShip.activeFrame = 0;
		sprites[spaceShip.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | spaceShip.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[spaceShip.OAMSpriteNum].attribute1 = SIZE_64 | spaceShip.x;			
		y_scroll += 4;
	}	
	if(!(*KEYS & KEY_RIGHT))                 //if the up down is pressed
	{
		spaceShip.x++;
 		spaceShip.activeFrame = 0;
		sprites[spaceShip.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | spaceShip.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[spaceShip.OAMSpriteNum].attribute1 = SIZE_64 | spaceShip.x;	
		x_scroll += 4;
	}
	if(!(*KEYS & KEY_LEFT))                 //if the up down is pressed
	{
		spaceShip.x--;
 		spaceShip.activeFrame = 0;
		sprites[spaceShip.OAMSpriteNum].attribute0 = COLOR_256 | SQUARE | spaceShip.y;	//setup sprite info, 256 colour, shape and y-coord
		sprites[spaceShip.OAMSpriteNum].attribute1 = SIZE_64 | spaceShip.x;			
		x_scroll -= 4;
	}	
}

int main(void) {
	u16 loop; 
    s16 x = 100;
	s16 y = 60;

	spaceShip.x = x;
	spaceShip.y = y;
	
	u16* temp; 
    u32 charbase 	= 0;
	u32 screenbase 	= 28;	
	u16* bg2map = (unsigned short *)ScreenBaseBlock(screenbase);
	REG_BG2CNT = BG_COLOR256 | ROTBG_SIZE_512x512 |(charbase << CHAR_SHIFT) | (screenbase << SCREEN_SHIFT);
	
	SetMode(MODE_2 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //set mode 2 and enable sprites and 1d mapping

	//Copy background palette into memory
	DMAFastCopy((void*)SpacemapPal, (void*)BGPaletteMem, 256, DMA_16NOW);
	//set the tile images
	DMAFastCopy((void*)SpacemapTiles, (void*)CharBaseBlock(charbase), 2048, DMA_32NOW);
	//copy the tile map into background 2
	DMAFastCopy((void*)SpacemapMap, (void*)bg2map, 64*64/2, DMA_32NOW);
	
	/*bg2.number = 2;				//background number 0-3
	bg2.charBaseBlock = 0;                  //tile data position (right at the start of the available memory on 16Kb boundary)
	bg2.screenBaseBlock = 28;		//map data position on 2Kb boundary
	bg2.colorMode = BG_COLOR256;           //256-colour background
	bg2.size = ROTBG_SIZE_256x256;          //size of map
	bg2.mosaic = 0;                         //not enabled
	
	//Point to correct tile and map data, update the Background and Display registers accordingly
    EnableBackground(&bg2);	
	
	for(loop = 0; loop < 256; loop++)
		BGPaletteMem[loop] = SpacemapPal[loop];     //load the background palette into memory

	for(loop = 0; loop < 576 /2; loop++)  //load tile image data
		bg2.tileData[loop] = SpacemapTiles[loop];

	//load the map image data
	temp = (u16*)SpacemapMap;
	for(loop = 0; loop < 32*32/2; loop++) //32x32 tiles /2 because 16 bit copy
		bg2.mapData[loop] = temp[loop];	
	*/
	
	for(loop = 0; loop < 256; loop++)          //load the palette into memory
		OBJPaletteMem[loop] = ShipPal[loop];	
	
	InitializeSprites();
	
  	sprites[0].attribute0 = COLOR_256 | SQUARE | spaceShip.y;	//setup sprite info, 256 colour, shape and y-coord
	sprites[0].attribute1 = SIZE_64 | spaceShip.x;				//size 64x64 and x-coord
	sprites[0].attribute2 = 0;                      	//pointer to tile where sprite starts

	spaceShip.OAMSpriteNum = 0;
	spaceShip.spriteFrame[0] = 0;
	spaceShip.spriteFrame[1] = 8;
	spaceShip.spriteFrame[2] = 64;

	for(loop = 0; loop < 2048; loop++)               	//load 1st sprite image data
		OAMData[loop] = ShipTiles[loop];
	
	while(1)
	{
		GetInput();
		WaitForVsync();
		CopyOAM();
		UpdateBackground(x_scroll, y_scroll);
	}

	return 0;
}
