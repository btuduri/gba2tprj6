#include "../headers/gba.h"
#include "../headers/gba_dma.h"

// fast memory copy using dma
void dma_fast_copy(void* source, void* dest, unsigned int count,unsigned int mode) {
	if (mode == DMA_16NOW || mode == DMA_32NOW) {
		REG_DMA3SAD = (unsigned int)source;
		REG_DMA3DAD = (unsigned int)dest;
		REG_DMA3CNT = count | mode;
	}
}