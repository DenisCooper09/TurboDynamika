#include "rcc.h"
#include "flash.h"
#include "interrupts.h"

extern void main(void);
extern void _estack(void);
void _reset(void);

static inline void _init_flash()
{
    FLASH->ACR = 3UL | (FLASH->ACR & ~3UL);                         // 3WS (96MHz SYSCLK)
    FLASH->ACR |= (7UL << 8);                                       // Enable data cache, instruction cache and prefetch
}

static inline void _init_clock()                                    // 96MHz SYSCLK
{
    RCC->CR &= ~(1UL << 24);                                        // Disable PLL
    while (RCC->CR & (1UL << 25));
    
    RCC->CR |= (1UL << 16);                                         // Enable HSE clock
    while (!(RCC->CR & (1UL << 17)));
    
    RCC->PLLCFGR = 25UL | (192UL << 6) | (4UL << 24) | (1UL << 22); // PLLM = 25, PLLN = 192, PLLP = 2, PLLQ = 4, clock = HSE
    
    RCC->CR |= (1UL << 24);                                         // Enable PLL
    while (!(RCC->CR & (1UL << 25)));
    
    RCC->CFGR &= ~3UL;
    RCC->CFGR |= 2UL;                                               // Select PLL as system clock
    while ((RCC->CFGR & (3UL << 2)) != (2UL << 2));
}

static inline void _init_memories()
{
    extern u32 _sbss, _ebss, _sdata, _edata, _sidata;
    
    for (u32 *dst = &_sbss; dst < &_ebss; ++dst) *dst = 0UL;
    for (u32 *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;
}

static inline void _init_vector_table()
{
    extern void (*_svectors[])(void), (*_evectors[])(void);
    
    for (void (**dst)(void) = _svectors; dst < _evectors; ++dst) *dst = default_isr;

    _svectors[0] = _estack;
    _svectors[1] = _reset;
    
    *((volatile u32 *)(0xE000ED08)) = (u32)_svectors;               // Set vector table offset (VTOR)
}

__attribute__((naked, noreturn)) void _reset(void)
{
    cpsid();
    
    _init_flash();
    _init_clock();
    _init_memories();
    _init_vector_table();
    
    cpsie();
    
    main();
    
    while (1) (void) 0;
}

__attribute__((section(".rovectors"))) void (*const rovectors[2])(void) = 
{
    _estack,
    _reset
};
