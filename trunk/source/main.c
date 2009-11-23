
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
	int keys_d, keys_u;

	irqInit();
	irqEnable(IRQ_VBLANK);
	
	consoleDemoInit();

	while (1) {
	
		VBlankIntrWait();
		scanKeys();
		
		keys_d = keysDown();
		keys_u = keysUp();
		
		// Handle button A
		if( keys_d & KEY_A ) {
		
			iprintf("\x1b[8;9HA: Ingedrukt \n");
		
		}
		
		if( keys_u & KEY_A ) {
		
			iprintf("\x1b[8;9HA: Losgelaten\n");
			
		}
		
		// Handle button B
		if( keys_d & KEY_B ) {
		
			iprintf("\x1b[10;9HB: Ingedrukt \n");
		
		}
		
		if( keys_u & KEY_B ) {
		
			iprintf("\x1b[10;9HB: Losgelaten\n");
			
		}
		
		
	}
}
