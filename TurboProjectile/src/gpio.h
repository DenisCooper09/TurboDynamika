#ifndef GPIO_H
#define GPIO_H

#include "types.h"

typedef struct
{
    u32 MODER;
    u32 OTYPER;
    u32 OSPEEDR;
    u32 PUPDR;
    u32 IDR;
    u32 ODR;
    u32 BSRR;
    u32 LCKR;
    u32 AFRL;
    u32 AFRH;
} GPIO_Registers;

#define GPIOA ((volatile GPIO_Registers *)(0x40020000))
#define GPIOB ((volatile GPIO_Registers *)(0x40020400))
#define GPIOC ((volatile GPIO_Registers *)(0x40020800))
#define GPIOD ((volatile GPIO_Registers *)(0x40020C00))
#define GPIOE ((volatile GPIO_Registers *)(0x40021000))
#define GPIOH ((volatile GPIO_Registers *)(0x40021C00))

#endif
