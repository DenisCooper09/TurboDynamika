#include "types.h"

int main(void)
{
    *((volatile u32 *)(0x40023800 + 0x30)) = (1UL << 2);
    
    *((volatile u32 *)(0x40020800 + 0x00)) |= (1UL << 26);
    *((volatile u32 *)(0x40020800 + 0x14)) &= ~(1UL << 13);
    
    while (1)
    {
        *((volatile u32 *)(0x40020800 + 0x14)) ^= (1UL << 13);    
        for (u32 i = 0; i < 1000000; ++i);
    }
    
    return 0;
}
