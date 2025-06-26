#define F_CPU 16000000UL

#include "rcc.h"
#include "gpio.h"
#include "usart.h"
#include "interrupts.h"

void usart2_rx_isr(void)
{
    if (USART2->SR & (1 << 5))
    {
        volatile u8 data = (u8)USART2->DR;
        
        usart_write(USART2, data);
        
        GPIOC->ODR ^= (1UL << 13);
    }
}

int main(void)
{
    RCC->AHB1ENR |= 1UL | (1UL << 2);                       // Enable GPIOA and GPIOC clocks
    RCC->APB1ENR |= (1UL << 17);                            // Enable USART2 clock
    
    GPIOC->MODER |= (1UL << 26);
    GPIOC->ODR   &= ~(1UL << 13);
    
    // USART2 test
    GPIOA->MODER |= (1UL << 5) | (1UL << 7);                // Set A2-3 to alternate function mode
    GPIOA->AFRL  |= (7UL << 8) | (7UL << 12);               // Set A2-3 AF to AF7 (USART2)
    
    USART2->BRR  = F_CPU / 9600;                            // Set baud rate to 9600 baud
    USART2->CR1  |= (1UL << 2) | (1UL << 3) | (1UL << 13);  // Enable TX, RX, USART
    
    cpsid();
    irq_register_isr(IRQ_USART2, usart2_rx_isr);
    irq_enable(IRQ_USART2);
    USART2->CR1 |= (1UL << 5);                              // Enable RXNE interrupt
    cpsie();
    
    while (1) (void) 0;
    
    return 0;
}
