//
// Include dma.h
//

#ifndef DMA_H
#define DMA_H


#define DMA_ENABLE 				0x80000000
#define DMA_TIMING_IMMEDIATE 	0x00000000
#define DMA_16 					0x00000000
#define DMA_32 					0x04000000
#define DMA_32NOW 				(DMA_ENABLE | DMA_TIMING_IMMEDIATE | DMA_32)
#define DMA_16NOW 				(DMA_ENABLE | DMA_TIMING_IMMEDIATE | DMA_16)

//#define REG_DMA1SAD     *(u32*)0x40000BC	//DMA1 Source Address
#define REG_DMA1SAD_L   *(u16*)0x40000BC	//DMA1 Source Address Low Value
#define REG_DMA1SAD_H   *(u16*)0x40000BE	//DMA1 Source Address High Value
//#define REG_DMA1DAD     *(u32*)0x40000C0	//DMA1 Desination Address
#define REG_DMA1DAD_L   *(u16*)0x40000C0	//DMA1 Destination Address Low Value
#define REG_DMA1DAD_H   *(u16*)0x40000C2	//DMA1 Destination Address High Value
//#define REG_DMA1CNT     *(u32*)0x40000C4	//DMA1 Control (Amount)
#define REG_DMA1CNT_L   *(u16*)0x40000C4	//DMA1 Control Low Value
#define REG_DMA1CNT_H   *(u16*)0x40000C6	//DMA1 Control High Value

//#define REG_DMA2SAD     *(u32*)0x40000c8	//DMA2 Source Address
#define REG_DMA2SAD_L   *(u16*)0x40000C8	//DMA2 Source Address Low Value
#define REG_DMA2SAD_H   *(u16*)0x40000CA	//DMA2 Source Address High Value
//#define REG_DMA2DAD     *(u32*)0x40000CC	//DMA2 Desination Address
#define REG_DMA2DAD_L   *(u16*)0x40000CC	//DMA2 Destination Address Low Value
#define REG_DMA2DAD_H   *(u16*)0x40000CE	//DMA2 Destination Address High Value
//#define REG_DMA2CNT     *(u32*)0x40000D0	//DMA2 Control (Amount)
#define REG_DMA2CNT_L   *(u16*)0x40000D0	//DMA2 Control Low Value
#define REG_DMA2CNT_H   *(u16*)0x40000D2	//DMA2 Control High Value

#define REG_DMA0SAD			*(vu32*)(REG_BASE+0x00B0)	//!< DMA 0 Source address
#define REG_DMA0DAD			*(vu32*)(REG_BASE+0x00B4)	//!< DMA 0 Destination address
#define REG_DMA0CNT			*(vu32*)(REG_BASE+0x00B8)	//!< DMA 0 Control
#define REG_DMA1SAD			*(vu32*)(REG_BASE+0x00BC)	//!< DMA 1 Source address
#define REG_DMA1DAD			*(vu32*)(REG_BASE+0x00C0)	//!< DMA 1 Destination address
#define REG_DMA1CNT			*(vu32*)(REG_BASE+0x00C4)	//!< DMA 1 Control
#define REG_DMA2SAD			*(vu32*)(REG_BASE+0x00C8)	//!< DMA 2 Source address
#define REG_DMA2DAD			*(vu32*)(REG_BASE+0x00CC)	//!< DMA 2 Destination address
#define REG_DMA2CNT			*(vu32*)(REG_BASE+0x00D0)	//!< DMA 2 Control
#define REG_DMA3SAD			*(vu32*)(REG_BASE+0x00D4)	//!< DMA 3 Source address
#define REG_DMA3DAD			*(vu32*)(REG_BASE+0x00D8)	//!< DMA 3 Destination address
#define REG_DMA3CNT			*(vu32*)(REG_BASE+0x00DC)	//!< DMA 3 Control
 
// Controls how the destination address is changed on subsequent copies.  Normally we'll
// increment it, but in some cases, like for DirectSound we'll want it to do other things..
#define DMA_DST_INC		0		//!< Incrementing destination address
#define DMA_DST_DEC		0x00200000	//!< Decrementing destination
#define DMA_DST_FIX		0x00400000	//!< Fixed destination 
#define DMA_DST_RESET		0x00600000	//!< Increment destination, reset after full run
 
// Controls how the source address is changed on subsequent copies.  Notice that RESET is not 
// available for source. 
#define DMA_SRC_INC		0		//!< Incrementing source address
#define DMA_SRC_DEC		0x00800000	//!< Decrementing source address
#define DMA_SRC_FIX		0x01000000	//!< Fixed source address
#define DMA_REPEAT		0x02000000	//!< Repeat transfer at next start condition 
 
// Controls when we should start the next subsequent copy.  Notice that SPEC, FIFO and REFRESH
// are the same bit.  The behavior of this bit changes depending on the DMA channel.
#define DMA_AT_NOW		0		//!< Start transfer now
#define DMA_AT_VBLANK		0x10000000	//!< Start transfer at VBlank
#define DMA_AT_HBLANK		0x20000000	//!< Start transfer at HBlank
#define DMA_AT_SPEC		0x30000000	//!< Start copy at 'special' condition. Channel dependent
#define DMA_AT_FIFO		0x30000000	//!< Start at FIFO empty (DMA0/DMA1)
#define DMA_AT_REFRESH		0x30000000	//!< VRAM special; start at VCount=2 (DMA3)
#define DMA_IRQ			0x40000000	//!< Enable DMA irq
#define DMA_ON			0x80000000	//!< Enable DMA

#endif

