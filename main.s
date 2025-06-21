.section .text,"ax"
.globl main
main:
  add  x2,x0,x0
  add  x1,x0,x0
  addi x2, x2, 5
  addi x1, x2, 5
  csrr t0, mcause


