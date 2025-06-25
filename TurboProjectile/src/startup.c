#include "types.h"

extern void main(void);
extern void _estack(void);

__attribute__((naked, noreturn)) void _reset(void)
{
    extern u32 _sbss, _ebss, _sdata, _edata, _sidata;
    
    for (u32 *dst = &_sbss; dst < &_ebss; ++dst) *dst = 0UL;
    for (u32 *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;
    
    main();
    
    while (1) (void) 0;
}

__attribute__((section(".vectors"))) void (*const vectors[16 + 85 + 1])(void) = 
{
    _estack,
    _reset
};
