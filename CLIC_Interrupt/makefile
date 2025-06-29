COMPILER = riscv64-unknown-elf
CC = $(COMPILER)-gcc
OBJDUMP = $(COMPILER)-objdump
CFLAGS = -O0 -g -mabi=ilp32 -march=rv32i -std=gnu11
LFLAGS = -nostdlib -Wl,-Map=output.map -T linker.ld

all:
	$(CC) $(CFLAGS) $(LFLAGS) main.s -o main.elf

objdump:
	$(OBJDUMP) -h main.elf >> objdump.txt

qemu:
	qemu-system-riscv32 -S -nographic -machine virt -bios none -kernel main.elf -gdb tcp::1234

debug:
	gdb-multiarch main.elf -ex "target remote localhost:1234" -ex "break main"

.PHONY:clean
clean:
	rm *.elf *.map .gdb_history