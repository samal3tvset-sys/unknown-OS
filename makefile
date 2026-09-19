CROSS_COMPILE = aarch64-linux-gnu-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AS = $(CROSS_COMPILE)as
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdinc -nostdlib
LDFLAGS = -nostdlib -Wl,-Ttext=0x40000000

OBJS = bootloader.o kernel.o de.o touchscreen.o

all: kernel.bin

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.asm
	$(AS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o kernel.elf kernel.bin
