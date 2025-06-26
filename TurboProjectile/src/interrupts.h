#ifndef INTERRUPTS_H
#define INTERRUPTS_H

static inline void cpsid(void)
{
    __asm volatile ("cpsid i" ::: "memory");
}

static inline void cpsie(void)
{
    __asm volatile ("cpsie i" ::: "memory");
}

#endif
