COMPILER = riscv64-unknown-elf
CC = $(COMPILER)-gcc
OBJDUMP = $(COMPILER)-objdump
CFLAGS = -O0 -mabi=ilp32 -march=rv32i -std=gnu11
LFLAGS = -nostdlib -Wl,-Map=output.map -T linker.ld

all:
	$(CC) $(CFLAGS) $(LFLAGS) main.c -o main.elf

objdump:
	$(OBJDUMP) -h main.elf >> objdump.txt

.PHONY:clean
clean:
	rm main.elf