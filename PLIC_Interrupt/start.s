.section .text,"ax"
.globl start
start:
  li   t0, 0x1802 # interrupt enable and previous privilege mode as m-mode
  csrs mstatus, t0
  li   t0, 0x800   # machine external interrupt enable
  csrs mie, t0
  la   t0, interrupt_handler #load interrupt handler address in mtvec
  csrw mtvec, t0 
  li   t0, 0x2000 # set mtime to 0x10000000
  li   t1, 0x80000000
  add  sp, t0,t1  //setting up stack pointer
  call    main

loop:
  j loop
