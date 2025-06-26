#include "types.h"
#include "interrupts.h"

extern void main(void);
extern void _estack(void);

__attribute__((naked, noreturn)) void _reset(void)
{
    cpsid();
    
    extern u32 _sbss, _ebss, _sdata, _edata, _sidata;
    
    for (u32 *dst = &_sbss; dst < &_ebss; ++dst) *dst = 0UL;
    for (u32 *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;
    
    main();
    
    while (1) (void) 0;
}

__attribute__((section(".vectors"))) void (*const vectors[2])(void) = 
{
    _estack,
    _reset
};
