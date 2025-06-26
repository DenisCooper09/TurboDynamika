#define F_CPU 16000000UL

#include "rcc.h"
#include "gpio.h"
#include "usart.h"

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
    
    while (1)
    {
        GPIOC->ODR ^= (1UL << 13);
        
        USART2->DR = 'A';
        while (!(USART2->SR & (1UL << 6)));
        
        for (u32 i = 0; i < 1000000; ++i);
    }
    
    return 0;
}
