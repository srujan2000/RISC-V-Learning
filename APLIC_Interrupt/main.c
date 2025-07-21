/* Registers Memory Map*/
#define UART 0x10000000
#define UART_IRQ 10U

#define IER 1
#define FCR 2
#define LCR 3
#define LSR 5

#define HART_0 0

#define Reg(offset) *((volatile unsigned char *)(UART + offset))

#define WRITE_REG(ADDR) *((volatile unsigned int *)(ADDR))

#define APLIC 0x0C000000
#define DOMAIN_CFG (APLIC + 0x00)
#define SOURCE_CFG (APLIC + 0x28)  /* (0x00 + source*4)uart source is 10 */
#define SETIE      (APLIC + 0x1E00) /* source 10 is part of zero index of SETIE */
#define TARGET     (APLIC + 0x3004)

#define IMSIC 0x28000000
#define EIDELIVERY (IMSIC + 0x70)
#define EIE        (IMSIC + 0xC0)


int Plic_Claim_Id = 0;
void uart_init(void)
{
  Reg(IER) = 0x00; // Disable interrupts
  Reg(LCR) = 1<<7; // Set baud rate
  Reg(0x00) = 0x03; // LSB for baud rate of 38.4K.
  Reg(0x00) = 0x00; // MSB for baud rate of 38.4K.
  Reg(LCR)  = 0x03; // 8 bits, no parity, 1 stop bit
  Reg(FCR) = 0x07; // Enable FIFO, clear RX and TX FIFO
  Reg(IER) = 0x03; // Enable RX and TX interrupt
}

void aplic_init(void)
{
  WRITE_REG(DOMAIN_CFG) |= (1U<<8U) | (1U<<2U); // Set domain configuration with MSI delivery mode and interrupt enable
  WRITE_REG(SOURCE_CFG) |= (1U<<2U); // source mode is edge triggered and no delegation
  WRITE_REG(SETIE) = ( 1U << UART_IRQ); // Enable interrupt for UART source
  WRITE_REG(TARGET) = (1U <<10U); // set EIID as 10 and hartid as 0
}

void imsic_init(void)
{
  WRITE_REG(EIDELIVERY) = 0x40000000; // Set EIDELIVERY to 0
  WRITE_REG(EIE) = (1U << UART_IRQ); // Enable interrupt for EIE 10 i.e uart

}

void delay()
{
  volatile int i;
  for (i = 0; i < 100000; i++); // Simple delay loop
}

// void write_to_uart(void)
// {
//   Reg(0x00) = 'H'; // Write 'H' to UART
//   delay();
//   Reg(0x00) = 'e'; // Write 'e' to UART
//   delay();
//   Reg(0x00) = 'l'; // Write 'l' to UART
//   delay();
//   Reg(0x00) = 'l'; // Write 'l' to UART
//   delay();
//   Reg(0x00) = 'o'; // Write 'o' to UART
//   delay();
//   Reg(0x00) = '\n'; // Write newline to UART
//   delay();
// }

void interrupt_handler(void)
{ 
  // Plic_Claim_Id = *(unsigned int*)PLIC_CLAIM(HART_0); // Claim the interrupt

  if(Reg(LSR) & 0x01){
    char char_received = Reg(0x00); // Read the character from UART
    Reg(0x00) = char_received; // Print the character
  }
}

int main()
{
  imsic_init();
  aplic_init(); // Initialize PLIC
  uart_init(); // Initialize UART

  // write_to_uart();
}