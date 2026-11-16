// ============================================================
// Project: toggle the user LED on the board
// Board:   Nucleo-F446RE (STM32F446RE microcontroller)
// The user LED (LD2) is connected to:
//   port: A  -> GPIOA
//   pin:  5  -> PA5
// ============================================================

// Addresses: RM0390, section 2.2.2, table 1.

#include <stdint.h>

#define PERIPH_BASE         (0x40000000UL)
#define AHB1PERIPH_OFFSET   (0x00020000UL)
#define AHB1PERIPH_BASE     (PERIPH_BASE + AHB1PERIPH_OFFSET)   // 0x40020000

#define GPIOA_OFFSET        (0x0000UL)
#define GPIOA_BASE          (AHB1PERIPH_BASE + GPIOA_OFFSET)    // 0x40020000

#define RCC_OFFSET          (0x3800UL)
#define RCC_BASE            (AHB1PERIPH_BASE + RCC_OFFSET)      // 0x40023800

// RCC_AHB1ENR
#define AHB1EN_R_OFFSET     (0x30UL)
#define RCC_AHB1EN_R        (*(volatile uint32_t *)(RCC_BASE + AHB1EN_R_OFFSET))

// GPIOx_MODER
#define MODE_R_OFFSET       (0x00UL)
#define GPIOA_MODE_R        (*(volatile uint32_t *)(GPIOA_BASE + MODE_R_OFFSET))

// GPIOx_ODR
#define OD_R_OFFSET         (0x14UL)
#define GPIOA_OD_R          (*(volatile uint32_t *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN             (1U << 0)   // RCC_AHB1ENR bit 0

// MODER: 2 bits per pin, pin 5 -> bits 10-11
#define MODER5_BIT0         (1U << 10)
#define MODER5_BIT1         (1U << 11)

#define PIN5                (1U << 5)
#define LED_PIN             PIN5

int main(void)
{
    RCC_AHB1EN_R |= GPIOAEN;   // GPIOA clock is off after reset

    // PA5 as general-purpose output (MODER5 = 01)
    GPIOA_MODE_R &= ~MODER5_BIT1;
    GPIOA_MODE_R |=  MODER5_BIT0;

    while (1)
    {
        GPIOA_OD_R ^= LED_PIN;
        for (volatile uint32_t i = 0; i < 50000; i++) {}   // delay
    }
}
