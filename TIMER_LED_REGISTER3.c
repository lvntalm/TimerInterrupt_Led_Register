#include "TIMER_LED_REGISTER3.h"

void GPIO_Clock_Init()
{
    RCC -> AHB1ENR |= (1 << 3);   // GPIOD Clock Enable
}

void TIM2_Clock_Init()
{
    RCC -> APB1ENR |= (1 << 0);   // TIM2 Clock Enable
}

void GPIO_Init()
{
    GPIOD -> MODER &= ~((1 << 25) | (1 << 27) | (1 << 29) | (1 << 31));       // GPIO (General Output Mode)
    GPIOD -> MODER |= (1 << 24) | (1 << 26) | (1 << 28) | (1 << 30);            

    GPIOD -> OTYPER &= ~((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15));       

    GPIOD -> OSPEEDR |= (1 << 24) | (1 << 25) | (1 << 26) | (1 << 27) | (1 << 28) | (1 << 29) | (1 << 30) | (1 << 31);  

    GPIOD -> PUPDR &= ~((1 << 24) | (1 << 25) | (1 << 26) | (1 << 27) | (1 << 28) | (1 << 29) | (1 << 30) | (1 << 31));    
}

void TIM2_Init()
{
    TIM2 -> PSC = 41999;    // Prescaler = 41999 (1 kHz = 1 ms)
    TIM2 -> ARR = 1000;     // Auto-reload value for 1000 ms
}

void TIM2_ChannelSettings()

// Four different channels for every four LEDs
{
    TIM2 -> CCMR1 |= (1 << 4);    // OC1M for channel 1
    TIM2 -> CCER |= (1 << 0);     // Enable Capture/Compare for channel 1
    TIM2 -> CCR1 = 250;           // Compare value for channel 1

    TIM2 -> CCMR1 |= (1 << 12);   // OC2M for channel 2
    TIM2 -> CCER |= (1 << 4);     // Enable Capture/Compare for channel 2
    TIM2 -> CCR2 = 500;           // Compare value for channel 2

    TIM2 -> CCMR2 |= (1 << 4);    // OC3M for channel 3
    TIM2 -> CCER |= (1 << 8);     // Enable Capture/Compare for channel 3
    TIM2 -> CCR3 = 750;           // Compare value for channel 3

    TIM2 -> CCMR2 |= (1 << 12);   // OC4M for channel 4
    TIM2 -> CCER |= (1 << 12);    // Enable Capture/Compare for channel 4
    TIM2 -> CCR4 = 1000;          // Compare value for channel 4
}

void TIM2_CounterStart()
{
    TIM2 -> DIER |= (1 << 0);    // Enable interrupt
    TIM2 -> CR1 |= (1 << 0);     // Enable counter
}

void NVIC_Enable()
{
    NVIC -> ISER[0] |= (1 << 28);    // Enable TIM2 interrupt in NVIC
}

void NVIC_Priority()
{
    NVIC -> IP[7] = (0x00 << 24);    // Set priority for TIM2 interrupt
}

void TIM2_IRQHandler(void)
{
    if(TIM2 -> SR & (1 << 0))  // Check interrupt flag
    {
        // PD12, PD13, PD14 ve PD15 LED's toggling

        GPIOD -> ODR ^=(1 << 12);     // Toggle PD12

        GPIOD -> ODR ^=(1 << 13);     // Toggle PD13

        GPIOD -> ODR ^=(1 << 14);     // Toggle PD14

        GPIOD -> ODR ^=(1 << 15);     // Toggle PD15

        TIM2 -> SR &= ~(1 << 0);      // Clear interrupt flag
    }
}


