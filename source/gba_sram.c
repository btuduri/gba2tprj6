/**
 * SRAM functions to control saving on cartridge
 *
 * @date	11/12/09
 * @author	Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/gba.h"
#include "../headers/gba_sram.h"


/**
 * Function to save int on a specific offset
 */
void save_int( u16 offset, int value ) 
{
	int i;
	char string[10];
	sprintf(string, "%d", value);
	
	for(i=0; i < 32768; i++) {
	
		if(string[i] == 0)	{
			break;
		}
		
		*(u8 *)(SRAM + offset + i) = string[i];
		
	}
	
}


/**
 * Function to load int from a specific offset
 */
int load_int( u16 offset ) {

	int  i;
	char string[10];
	
	for(i = 0; i != 10; i++) {
	
		string[i] = *(u8 *)(SRAM + offset + i);
		
	}
	
	return atoi(string);
	
}


/**
 * Function to erase the first x lines in the save data
 */
void erase_SRAM( int length ) {

	int i;
	for(i=0; i < length; i++) {
			
		*(u8 *)(SRAM + i) = 0;
		
	}

}