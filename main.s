.section .text,"ax"
.globl main
main:
  add  x2,x0,x0
  add  x1,x0,x0
  addi x2, x2, 5
  addi x1, x2, 5
  csrr t0, mcause
  addi a0, x0, 0x41
	li a1, 0x10000000
	sb a0, (a1) # 'a'
  addi a0, x0, 0x42
	li a1, 0x10000000
	sb a0, (a1) # 'b'
  addi a0, x0, 0x43
	li a1, 0x10000000
	sb a0, (a1) # 'c'
  addi a0, x0, 0x44
	li a1, 0x10000000
	sb a0, (a1) # 'd'
  addi a0, x0, 0x45
	li a1, 0x10000000
	sb a0, (a1) # 'e'

loop: j loop


