#include "../headers/gba.h"
#include "../headers/gba_bg.h"

void update_background(u16 x,u16 y) {
	REG_BG2X = x*256;
	REG_BG2Y = y*256;
}