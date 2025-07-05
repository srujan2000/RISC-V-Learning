/* Registers Memory Map*/
#define UART 0x10000000
#define UART_IRQ 0x10

#define IER 1
#define FCR 2
#define LCR 3

#define HART_0 0

#define Reg(offset) *((volatile unsigned char *)(UART + offset))

#define PLIC 0x0C000000
#define PLIC_PRIORITY_SOURCE (PLIC + 0x0)
#define PLIC_PENDING (PLIC + 0x1000)
#define PLIC_ENABLE(hart) (PLIC + 0x2000 + (hart) * 0x100)
#define PLIC_PRIORITY_CONTEXT(hart) (PLIC + 0x200000 + (hart) * 0x100)
#define PLIC_CLAIM(hart) (PLIC + 0x200004 + (hart) * 0x100)


int Plic_Claim_Id = 0;
void uart_init(void)
{
  Reg(IER) = 0x00; // Disable interrupts
  Reg(LCR) = 1<<7; // Set baud rate
  Reg(0x00) = 0x03; // LSB for baud rate of 38.4K.
  Reg(0x00) = 0x00; // MSB for baud rate of 38.4K.
  Reg(LCR)  = 0x03; // 8 bits, no parity, 1 stop bit
  Reg(FCR) = 0x07; // Enable FIFO, clear RX and TX FIFO
  Reg(IER) = 0x03; // Enable RX interrupt
}

void plic_init(void)
{
  *(unsigned int*)(PLIC + UART_IRQ*4) = 1;  
  *(unsigned int*)PLIC_ENABLE(HART_0) = (1 << UART_IRQ);

  // set this hart's S-mode priority threshold to 0.
  *(unsigned int*)PLIC_PRIORITY_CONTEXT(HART_0) = 0;
}

void delay()
{
  volatile int i;
  for (i = 0; i < 100000; i++); // Simple delay loop
}

void write_to_uart(void)
{
  Reg(0x00) = 'H'; // Write 'H' to UART
  delay();
  Reg(0x00) = 'e'; // Write 'e' to UART
  delay();
  Reg(0x00) = 'l'; // Write 'l' to UART
  delay();
  Reg(0x00) = 'l'; // Write 'l' to UART
  delay();
  Reg(0x00) = 'o'; // Write 'o' to UART
  delay();
  Reg(0x00) = '\n'; // Write newline to UART
  delay();
}

void interrupt_handler(void)
{ 
  Plic_Claim_Id = *(unsigned int*)PLIC_CLAIM(HART_0); // Claim the interrupt
  Reg(0x00) = 'I'; // Write 'H' to UART
  Reg(0x00) = 'N'; // Write 'H' to UART
  Reg(0x00) = 'T'; // Write 'H' to UART
}

int main()
{
  plic_init(); // Initialize PLIC
  uart_init(); // Initialize UART

  // write_to_uart();
}