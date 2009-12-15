#
# Makefile
#
# makefile for SpaceInvader game damo
#


PATH := $(DEVKITARM)/bin:$(PATH)

# --- Project details -------------------------------------------------

PROJ    := SpaceInvader
TITLE   := $(PROJ)

COBJS   := source/main.o source/gba_dma.o source/gba.o source/gba_bg.o source/gba_sprites.o source/gba_sram.o source/interface.o levels/level1/sprites/Ship.o levels/level1/sprites/UFO.o levels/level1/sprites/bullet.o interface/text_1.o interface/text_2.o interface/text_3.o interface/text_4.o interface/text_5.o interface/text_6.o interface/text_7.o interface/text_8.o interface/text_9.o interface/text_0.o levels/level1/map/Spacemap.o menus/Startscreen.o menus/Pausescreen.o

OBJS	:= $(COBJS)

# --- boot type (MB=0 : normal. MB=1 : multiboot) ---

MB = 0

ifeq ($(MB),1)

TARGET	:= $(PROJ).mb
SPECS	:= -specs=gba_mb.specs

else

TARGET	:= $(PROJ)
SPECS	:= -specs=gba.specs

endif

BUILD	:= build

# --- Compiling -------------------------------------------------------

CROSS	?= arm-eabi-
AS		:= $(CROSS)as
CC		:= $(CROSS)gcc
LD		:= $(CROSS)gcc
OBJCOPY	:= $(CROSS)objcopy


ARCH	:= -mthumb-interwork -mthumb

ASFLAGS	:= -mthumb-interwork
CFLAGS	:= $(ARCH) -O2 -Wall -fno-strict-aliasing
LDFLAGS	:= $(ARCH) $(SPECS)

.PHONY : build clean

# --- Build -----------------------------------------------------------

build : $(TARGET).gba


$(TARGET).gba : $(TARGET).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(TITLE)

$(TARGET).elf : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

$(COBJS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
# --- Clean -----------------------------------------------------------

clean : 
#	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv source/*.o
	@rm -fv menus/*.o
	@rm -fv *.sav

#EOF
