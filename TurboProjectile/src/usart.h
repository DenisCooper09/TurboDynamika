#ifndef USART_H
#define USART_H

#include "types.h"

typedef struct
{
    u32 SR;
    u32 DR;
    u32 BRR;
    u32 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;
} USART_Registers;

#define USART2 ((volatile USART_Registers *)(0x40004400))
#define USART1 ((volatile USART_Registers *)(0x40011000))
#define USART6 ((volatile USART_Registers *)(0x40011400))

static inline void usart_write(volatile USART_Registers *usart, u8 data)
{
    usart->DR = data;
    while (!(usart->SR & (1UL << 6)));
}

static inline void usart_write_buffer(volatile USART_Registers *usart, const u8 *buffer, u32 size)
{
    while (size--) usart_write(usart, *buffer++);
}

#endif
