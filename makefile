CROSS_COMPILE = aarch64-linux-gnu-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdinc -nostdlib
LDFLAGS = -nostdlib -T linker.ld

OBJS = startup.o kernel.o de.o touchscreen.o

all: kernel.bin

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o kernel.elf kernel.bin
