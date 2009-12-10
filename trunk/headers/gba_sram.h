/**
 * Defines for saving in the SRAM of the cartridge
 *
 * @date	11/12/09
 * @author  Wesley Hilhorst
 * @email	wesley.hilhorst@gmail.com
 */

#ifndef SRAM_HEADER
#define SRAM_HEADER

#define SRAM 0xe000000	//32k SRAM = 0x0e000000 - 0x0e00ffff

void SaveInt(u16 offset, int value) 
{
	int i;
	char string[7];
	sprintf(string, "%d", value);
	
	for(i=0; i < 32768; i++) {
	
		if(string[i] == 0)	{
			break;
		}
		
		*(u8 *)(SRAM + offset + i) = string[i];
		
	}
	
}

int LoadInt(u16 offset) {

	int  i;
	char string[7];
	
	for(i = 0; i != 7; i++) {
	
		string[i] = *(u8 *)(SRAM + offset + i);
		
	}
	
	return atoi(string);
	
}


#endif