#include "rcc.h"
#include "gpio.h"

int main(void)
{
    RCC->AHB1ENR |= (1UL << 2);
    
    GPIOC->MODER |= (1UL << 26);
    GPIOC->ODR   &= ~(1UL << 13);
    
    while (1)
    {
        GPIOC->ODR ^= (1UL << 13);    
        for (u32 i = 0; i < 1000000; ++i);
    }
    
    return 0;
}
