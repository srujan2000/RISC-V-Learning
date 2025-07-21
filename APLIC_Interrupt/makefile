COMPILER = riscv64-unknown-elf
CC = $(COMPILER)-gcc
OBJDUMP = $(COMPILER)-objdump
CFLAGS = -O0 -g -mabi=ilp32 -march=rv32i_zicsr -std=gnu11 -g
LFLAGS = -nostdlib -Wl,-Map=output.map -T linker.ld

all:
	$(CC) $(CFLAGS) $(LFLAGS) start.s main.c -o main.elf

objdump:
	$(OBJDUMP) -h main.elf >> objdump.txt

qemu:
	qemu-system-riscv32 -S -nographic -machine virt,aia=aplic-imsic -bios none -kernel main.elf -gdb tcp::1234

debug:
	gdb-multiarch main.elf -ex "target remote localhost:1234" -ex "break start"

.PHONY:clean
clean:
	rm *.elf *.map .gdb_history