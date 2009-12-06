/**
 * This file contains functions to control the background image.
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen
 * @email	wouter@0xff.nl
 */

#include "../headers/gba.h"
#include "../headers/gba_bg.h"

Background bg;

/**
 * Function to scroll the background
 */
void update_background() {
	REG_BG2X = bg.x_scroll * 256;
	REG_BG2Y = bg.y_scroll * 256;
}