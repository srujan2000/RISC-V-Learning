.section .text,"ax"
.globl main
main:
  add  x2,x0,x0
  add  x1,x0,x0
  addi x2, x2, 5
  addi x1, x2, 5
  li   t0, 0x1802 # interrupt enable and previous privilege mode as m-mode
  csrs mstatus, t0
  li   t0, 0x80   # timer interrupt enable
  csrs mie, t0
  la      t0, interrupt_handler #load interrupt handler address in mtvec
  csrw    mtvec, t0 
  call    set_timer

set_timer:
  li      t0, 5000000
  li      t1, 0x2004000
  sw      t0, 0(t1)
  csrr t0, mcause

interrupt_handler:
  addi t0, x0,0  # timer interrupt enable
  csrw mip, t0
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
  addi a0, x0, 0x0A
	li a1, 0x10000000
	sb a0, (a1) # 'e'
  # call set_timer
  mret



