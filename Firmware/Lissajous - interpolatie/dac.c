#include "stm32f091xc.h"

// PA4 is DAC OUT 1.
// PA5 is DAC OUT 2.
// Let op: bij een Nucleo-bord is PA5 verbonden met de on board LED... Verwijden SB21 indien gewenst.

void InitDAC(void)
{
	// Clock voor GPIOA inschakelen.
	RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOAEN;
	
	// PA4 = DAC OUT 1 als analoog zetten.
	GPIOA->MODER |= GPIO_MODER_MODER4;
	
	// DAC van klok voorzien.
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	// DAC uitgang 1 inschakelen.
	DAC->CR |= DAC_CR_EN1;
	
	// 0 Volt op die uitgang zetten.
	DAC->DHR12R1 = 0;
	
	// PA5 = DAC OUT 2 als analoog zetten.
	// Let op: bij een Nucleo-bord is PA5 verbonden met de on board LED... Verwijden SB21 indien gewenst.
	GPIOA->MODER |= GPIO_MODER_MODER5;
	
	// DAC van klok voorzien.
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	// DAC uitgang 2 inschakelen.
	DAC->CR |= DAC_CR_EN2;
	
	// 0 Volt op die uitgang zetten.
	DAC->DHR12R2 = 0;
}

void SetDacX(uint16_t dacValue)
{
	// Waarde wegschrijven om zo de DAC-spanning in te stellen.
	DAC->DHR12R1 = dacValue;
}

void SetDacY(uint16_t dacValue)
{
	// Waarde wegschrijven om zo de DAC-spanning in te stellen.
	DAC->DHR12R2 = dacValue;
}
