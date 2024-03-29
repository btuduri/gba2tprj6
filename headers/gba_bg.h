/**
 * Contains all the relevant defines for the background.
 *
 * @date	11/12/09
 * @author	unkown
 * @author  Wouter van Teijlingen
 * @email	wouter@0xff.nl
 */

#ifndef BG_H
#define BG_H

#define BG_COLOR256 			0x80
#define CHAR_SHIFT 				2
#define SCREEN_SHIFT 			8
#define WRAPAROUND 				0x1

/**
 * background tile bitmap sizes
 */
#define TEXTBG_SIZE_256x256 	0x0
#define TEXTBG_SIZE_256x512 	0x8000
#define TEXTBG_SIZE_512x256 	0x4000
#define TEXTBG_SIZE_512x512 	0xC000


/**
 * background setup registers and data
 */
#define BG_COLOR256 			0x80
#define CHAR_SHIFT 				2
#define SCREEN_SHIFT 			8
#define WRAPAROUND 				0x1

/**
 * background tile bitmap sizes
 */
#define TEXTBG_SIZE_256x256 	0x0
#define TEXTBG_SIZE_256x512 	0x8000
#define TEXTBG_SIZE_512x256 	0x4000
#define TEXTBG_SIZE_512x512 	0xC000

/**
 * background memory offset macros
 */
#define CHARBASEBLOCK(n) 		(((n)*0x4000)+0x6000000)
#define SCREENBASEBLOCK(n) 		(((n)*0x800)+0x6000000)

/**
 * Rotate background 
 */
#define ROTBG_SIZE_128x128 		0x0
#define ROTBG_SIZE_256x256 		0x4000
#define ROTBG_SIZE_512x512 		0x8000
#define ROTBG_SIZE_1024x1024 	0xC000

/**
 * Struct for background, can be used to keep track of the scrolling and more.
 */
typedef struct Background
{
	u8 mosaic;
	u8 colorMode;
	u8 number;
	u16 size;
	u8 charBaseBlock;
	u8 screenBaseBlock;
	s16 x_scroll,y_scroll;
}Background;

extern void update_background();
extern void reset_background();
extern void rotate_background();

/**
 * declaration of struct to communicate with the background.
 */
extern Background bg;

#endif