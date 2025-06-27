#ifndef FLASH_H
#define FLASH_H

#include "types.h"

typedef struct
{
    u32 ACR;
    u32 KEYR;
    u32 OPTKEYR;
    u32 SR;
    u32 CR;
    u32 OPTCR;
} FLASH_Registers;

#define FLASH ((volatile FLASH_Registers *)(0x40023C00))

#endif
