#ifndef RCC_H
#define RCC_H

#include "types.h"

typedef struct
{
    u32 CR;
    u32 PLLCFGR;
    u32 CFGR;
    u32 CIR;
    u32 AHB1RSTR;
    u32 AHB2RSTR;
    u32 _RESERVED1[2];
    u32 APB1RSTR;
    u32 APB2RSTR;
    u32 _RESERVED2[2];
    u32 AHB1ENR;
    u32 AHB2ENR;
    u32 _RESERVED3[2];
    u32 APB1ENR;
    u32 APB2ENR;
    u32 _RESERVED4[2];
    u32 AHB1LPENR;
    u32 AHB2LPENR;
    u32 _RESERVED5[2];
    u32 APB1LPENR;
    u32 APB2LPENR;
    u32 _RESERVED6[2];
    u32 BDCR;
    u32 CSR;
    u32 _RESERVED7[2];
    u32 SSCGR;
    u32 PLLI2SCFGR;
    u32 _RESERVED8;
    u32 DCKCFGR;
} RCC_Registers;

#define RCC ((volatile RCC_Registers *)(0x40023800))

#endif
