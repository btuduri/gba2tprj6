/**
 * DMA functions necessary to copy images to the screen.
 *
 * @date	11/12/09
 * @author	Wouter van Teijlingen
 * @email	wouter@0xff.nl
 */

#include "../headers/gba.h"
#include "../headers/gba_dma.h"

/**
 * This function can be used to copy information directly to memory using DMA.
 * See the header file for parameters that can be used to call this function. 
 *
 * @param source source address
 * @param dest destination adress
 * @param count how much data to copy
 * @param mode specify dma mode
 */
void dma_fast_copy(void* source, void* dest, unsigned int count,unsigned int mode) {
	if (mode == DMA_16NOW || mode == DMA_32NOW) {
		REG_DMA3SAD = (unsigned int)source;
		REG_DMA3DAD = (unsigned int)dest;
		REG_DMA3CNT = count | mode;
	}
}