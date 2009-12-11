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

extern void erase_SRAM( int length );
extern void save_int( u16 offset, int value );
extern int load_int( u16 offset );

#endif