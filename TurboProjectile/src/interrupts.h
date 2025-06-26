#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "types.h"

#define IRQ_NMI               -14L
#define IRQ_HardFault         -13L
#define IRQ_MemManage         -12L
#define IRQ_BusFault          -11L
#define IRQ_UsageFault        -10L
#define IRQ_SVCall            -5L
#define IRQ_DebugMonitor      -4L
#define IRQ_PendSV            -2L
#define IRQ_Systick           -1L
#define IRQ_WWDG               0L
#define IRQ_PVD                1L
#define IRQ_TAMP_STAMP         2L
#define IRQ_RTC_WKUP           3L
#define IRQ_FLASH              4L
#define IRQ_RCC                5L
#define IRQ_EXTI0              6L
#define IRQ_EXTI1              7L
#define IRQ_EXTI2              8L
#define IRQ_EXTI3              9L
#define IRQ_EXTI4              10L
#define IRQ_DMA1_Stream0       11L
#define IRQ_DMA1_Stream1       12L
#define IRQ_DMA1_Stream2       13L
#define IRQ_DMA1_Stream3       14L
#define IRQ_DMA1_Stream4       15L
#define IRQ_DMA1_Stream5       16L
#define IRQ_DMA1_Stream6       17L
#define IRQ_ADC                18L
#define IRQ_EXTI9_5            23L
#define IRQ_TIM1_BRK_TIM9      24L
#define IRQ_TIM1_UP_TIM10      25L
#define IRQ_TIM1_TRG_COM_TIM11 26L
#define IRQ_TIM1_CC            27L
#define IRQ_TIM2               28L
#define IRQ_TIM3               29L
#define IRQ_TIM4               30L
#define IRQ_I2C1_EV            31L
#define IRQ_I2C1_ER            32L
#define IRQ_I2C2_EV            33L
#define IRQ_I2C2_ER            34L
#define IRQ_SPI1               35L
#define IRQ_SPI2               36L
#define IRQ_USART1             37L
#define IRQ_USART2             38L
#define IRQ_EXTI15_10          40L
#define IRQ_EXTI17_RTC_Alarm   41L
#define IRQ_EXTI18_OTG_FS_WKUP 42L
#define IRQ_DMA1_Stream7       47L
#define IRQ_SDIO               49L
#define IRQ_TIM5               50L
#define IRQ_SPI3               51L
#define IRQ_DMA2_Stream0       56L
#define IRQ_DMA2_Stream1       57L
#define IRQ_DMA2_Stream2       58L
#define IRQ_DMA2_Stream3       59L
#define IRQ_DMA2_Stream4       60L
#define IRQ_OTG_FS             67L
#define IRQ_DMA2_Stream5       68L
#define IRQ_DMA2_Stream6       69L
#define IRQ_DMA2_Stream7       70L
#define IRQ_USART6             71L
#define IRQ_I2C3_EV            72L
#define IRQ_I2C3_ER            73L
#define IRQ_FPU                81L
#define IRQ_SPI4               84L
#define IRQ_SPI5               85L

#define NVIC_ISER ((volatile u32 *)(0xE000E100))
#define NVIC_ICER ((volatile u32 *)(0xE000E180))
#define NVIC_ISPR ((volatile u32 *)(0xE000E200))
#define NVIC_ICPR ((volatile u32 *)(0xE000E280))
#define NVIC_IABR ((volatile u32 *)(0xE000E300))
#define NVIC_IPR  ((volatile u32 *)(0xE000E400))
#define STIR      ((volatile u32 *)(0xE000EF00))

static inline void cpsid(void)
{
    __asm volatile ("cpsid i" ::: "memory");
}

static inline void cpsie(void)
{
    __asm volatile ("cpsie i" ::: "memory");
}

static inline void irq_enable(u32 irq)
{
    NVIC_ISER[irq >> 5] |= (1UL << (irq & 0x1FUL));
}

static inline void irq_disable(u32 irq)
{
    NVIC_ICER[irq >> 5] |= (1UL << (irq & 0x1FUL));
}

static inline u8 irq_enabled(u32 irq)
{
    return (NVIC_ISER[irq >> 5] & (1UL << (irq & 0x1FUL))) != 0;
}

static inline u8 irq_pending(u32 irq)
{
    return (NVIC_ISPR[irq >> 5] & (1UL << (irq & 0x1FUL))) != 0;
}

static inline u8 irq_active(u32 irq)
{
    return (NVIC_IABR[irq >> 5] & (1UL << (irq & 0x1FUL))) != 0;
}

static inline void irq_register_isr(i32 irq, void (*isr)(void))
{
    extern void (*_svectors[])(void);
    _svectors[16L + irq] = isr;
}

void default_isr(void);

#endif
