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

extern void eraseSRAM( int length );
extern void SaveInt( u16 offset, int value );
extern int LoadInt( u16 offset );

#endif