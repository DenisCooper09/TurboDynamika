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

    extern void (*_svectors[])(void), (*_evectors[])(void);
    
    for (void (**dst)(void) = _svectors; dst < _evectors; ++dst) *dst = default_isr;

    _svectors[0] = _estack;
    _svectors[1] = _reset;
    
    *((volatile u32 *)(0xE000ED08)) = (u32)_svectors;
    
    cpsie();
    
    main();
    
    while (1) (void) 0;
}

__attribute__((section(".rovectors"))) void (*const rovectors[2])(void) = 
{
    _estack,
    _reset
};
